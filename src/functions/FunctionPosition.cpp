/*
 * Copyright (c) 2001-2008
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2008
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

#include "../config/xqilla_config.h"
#include <xqilla/functions/FunctionPosition.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/ast/StaticAnalysis.hpp>
#include <xqilla/runtime/ResultImpl.hpp>

const XMLCh FunctionPosition::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionPosition::minArgs = 0;
const unsigned int FunctionPosition::maxArgs = 0;

/**
 * fn:position() as xs:integer
 */

FunctionPosition::FunctionPosition(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "empty()", args, memMgr)
{
}

ASTNode* FunctionPosition::staticResolution(StaticContext *context) {
  return resolveArguments(context);
}

ASTNode *FunctionPosition::staticTyping(StaticContext *context)
{
  _src.clear();

  _src.getStaticType() = StaticType::DECIMAL_TYPE;
  _src.contextPositionUsed(true);
  return calculateSRCForArguments(context);
}

class FunctionPositionResult : public ResultImpl
{
public:
  FunctionPositionResult(const LocationInfo *o)
    : ResultImpl(o) {}

  virtual Item::Ptr nextOrTail(Result &tail, DynamicContext *context)
  {
    if(context->getContextItem().isNull())
      XQThrow(FunctionException,X("FunctionPosition::createSequence"),
              X("Undefined context item in fn:position [err:XPDY0002]"));

    tail = 0;
    return context->getItemFactory()->createInteger((long)context->getContextPosition(), context);
  }
};

Result FunctionPosition::createResult(DynamicContext* context, int flags) const
{
  return new FunctionPositionResult(this);
}
