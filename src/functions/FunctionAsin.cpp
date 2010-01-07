/*
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
#include <xqilla/functions/FunctionAsin.hpp>

#include <xqilla/items/Numeric.hpp>
#include <xqilla/context/DynamicContext.hpp>

const XMLCh FunctionAsin::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n,  XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionAsin::minArgs = 1;
const unsigned int FunctionAsin::maxArgs = 1;

/*
 * math:asin($arg as numeric?) as numeric?
 */
FunctionAsin::FunctionAsin(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : EXSLTMathFunction(name, minArgs, maxArgs, "anyAtomicType?", args, memMgr)
{
}

ASTNode *FunctionAsin::staticTypingImpl(StaticContext *context)
{
  _src.clear();
  _src.getStaticType() = StaticType(StaticType::NUMERIC_TYPE, 0, 1);
  return NumericFunction::staticTypingImpl(context);
}

Result FunctionAsin::createResult(DynamicContext* context, int flags) const
{
  Numeric::Ptr num = getNumericParam(1, context);
  if(num.isNull()) return 0;
  return (Item::Ptr)num->asin(context);
}
