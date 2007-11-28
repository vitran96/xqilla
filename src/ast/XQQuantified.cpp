/*
 * Copyright (c) 2001-2007
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2007
 *     Oracle. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Id$
 */

#include <xqilla/ast/XQQuantified.hpp>
#include <xqilla/ast/XQSequence.hpp>
#include <xqilla/ast/TupleNode.hpp>
#include <xqilla/runtime/SingleResult.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/ItemFactory.hpp>
#include <xqilla/context/ContextHelpers.hpp>

XQQuantified::XQQuantified(Type qtype, TupleNode *parent, ASTNode *expr, XPath2MemoryManager *mm)
  : ASTNodeImpl(mm),
    qtype_(qtype),
    parent_(parent),
    expr_(expr)
{
  setType(QUANTIFIED);
}

ASTNode *XQQuantified::staticResolution(StaticContext *context)
{
  parent_ = parent_->staticResolution(context);
  expr_ = expr_->staticResolution(context);

  return this;
}

ASTNode *XQQuantified::staticTyping(StaticContext *context)
{
  _src.clear();

  parent_ = parent_->staticTypingSetup(context);

  expr_ = expr_->staticTyping(context);
  _src.add(expr_->getStaticAnalysis());
  _src.getStaticType().flags = StaticType::BOOLEAN_TYPE;

  parent_ = parent_->staticTypingTeardown(context, _src);

  if(!_src.isUsed()) {
    return constantFold(context);
  }

  if(expr_->isConstant()) {
    AutoDelete<DynamicContext> dContext(context->createDynamicContext());
    dContext->setMemoryManager(context->getMemoryManager());
    bool value = expr_->createResult(dContext)->getEffectiveBooleanValue(dContext, this);
    ASTNode *result = new (getMemoryManager())
      XQSequence(dContext->getItemFactory()->createBoolean(value, dContext),
                 dContext, getMemoryManager());
    result->setLocationInfo(this);
    return result->staticTyping(context);
  }

  return this;
}

class QuantifiedResult : public SingleResult
{
public:
  QuantifiedResult(const XQQuantified *ast)
    : SingleResult(ast),
      ast_(ast)
  {
  }

  virtual Item::Ptr getSingleResult(DynamicContext *context) const
  {
    bool defaultResult = (ast_->getQuantifierType() == XQQuantified::SOME) ? false : true;

    AutoVariableStoreReset reset(context);

    TupleResult::Ptr tuples = ast_->getParent()->createResult(context);
    while(tuples->next(context)) {
      context->setVariableStore(tuples);

      bool result = ast_->getExpression()->createResult(context)->getEffectiveBooleanValue(context, this);
      if(defaultResult != result) {
        defaultResult = result;
        break;
      }

      reset.reset();
    }

    return context->getItemFactory()->createBoolean(defaultResult, context);
  }

  virtual std::string asString(DynamicContext *context, int indent) const { return ""; }

private:
  const XQQuantified *ast_;
};

Result XQQuantified::createResult(DynamicContext* context, int flags) const
{
  return new QuantifiedResult(this);
}

