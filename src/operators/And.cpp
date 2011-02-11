/*
 * Copyright (c) 2001, 2008,
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004, 2010,
 *     Oracle and/or its affiliates. All rights reserved.
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
 */

#include "../config/xqilla_config.h"
#include <sstream>

#include <xqilla/operators/And.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/ast/StaticAnalysis.hpp>
#include <xqilla/ast/XQLiteral.hpp>
#include <xqilla/context/ItemFactory.hpp>
#include <xqilla/context/ContextHelpers.hpp>
#include <xqilla/exceptions/StaticErrorException.hpp>
#include <xqilla/ast/XQEffectiveBooleanValue.hpp>
#include <xqilla/runtime/ClosureResult.hpp>

XERCES_CPP_NAMESPACE_USE;

/*static*/ const XMLCh And::name[]={ chLatin_A, chLatin_n, chLatin_d, chNull };

And::And(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQOperator(AND, name, args, memMgr)
{
}

ASTNode* And::staticResolution(StaticContext *context)
{
  XPath2MemoryManager *mm = context->getMemoryManager();

  for(VectorOfASTNodes::iterator i = _args.begin(); i != _args.end(); ++i) {
    *i = new (mm) XQEffectiveBooleanValue(*i, mm);
    (*i)->setLocationInfo(this);
    *i = (*i)->staticResolution(context);
  }
  return this;
}

ASTNode *And::staticTypingImpl(StaticContext *context)
{
  _src.clear();

  VectorOfASTNodes::iterator i;
  for(i = _args.begin(); i != _args.end(); ++i) {
    _src.add((*i)->getStaticAnalysis());

    if((*i)->getStaticAnalysis().isUpdating()) {
      XQThrow(StaticErrorException,X("And::staticTyping"),
              X("It is a static error for an operand of an operator "
                "to be an updating expression [err:XUST0001]"));
    }
  }

  _src.getStaticType() = StaticType::BOOLEAN;
  return this;
}

class AndResult : public ResultImpl
{
public:
  AndResult(const And *ast)
    : ResultImpl(ast),
      ast_(ast)
  {
  }

  virtual Item::Ptr nextOrTail(Result &tail, DynamicContext *context)
  {
    VectorOfASTNodes::const_iterator i = ast_->getArguments().begin();
    while(i != ast_->getArguments().end()) {
      const ASTNode *arg = *i;
      ++i;

      if(i == ast_->getArguments().end()) {
        // Tail call optimisation
        tail = ClosureResult::create(arg, context);
        return 0;
      }

      if(!((ATBooleanOrDerived*)arg->createResult(context)->next(context).get())->isTrue()) {
        Item::Ptr result = context->getItemFactory()->createBoolean(false, context);
        tail = 0;
        return result;
      }
    }

    Item::Ptr result = context->getItemFactory()->createBoolean(true, context);
    tail = 0;
    return result;
  }

private:
  const And *ast_;
};

Result And::createResult(DynamicContext* context, int flags) const
{
  if(_args.empty())
    return (Item::Ptr)context->getItemFactory()->createBoolean(true, context);
  return new AndResult(this);
}

