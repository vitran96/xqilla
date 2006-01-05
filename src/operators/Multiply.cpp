/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 * Copyright (c) 2004-2006
 *     Parthenon Computing Ltd. All rights reserved.
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
#include <assert.h>
#include <xqilla/operators/Multiply.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/Numeric.hpp>
#include <xqilla/items/ATDurationOrDerived.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/items/AnyAtomicType.hpp>

/*static*/ const XMLCh Multiply::name[]={ XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_l, XERCES_CPP_NAMESPACE_QUALIFIER chNull };

Multiply::Multiply(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ArithmeticOperator(name, args, memMgr)
{
  // Nothing to do
}

Item::Ptr Multiply::execute(const AnyAtomicType::Ptr &atom1, const AnyAtomicType::Ptr &atom2, DynamicContext *context) const
{
  if(atom1 == NULLRCP || atom2 == NULLRCP) return 0;

  // xs:double * xs:duration (only xdt:dayTimeDuration and xdt:yearMonthDuration)
  if(atom1->isNumericValue() &&
     atom2->getPrimitiveTypeIndex() == AnyAtomicType::DURATION) {
      return (const Item::Ptr)((const ATDurationOrDerived*)(const AnyAtomicType*)atom2)->multiply((const Numeric::Ptr)atom1, context);
  }
  // xs:duration * xs:double (only xdt:dayTimeDuration and xdt:yearMonthDuration)
  if(atom1->getPrimitiveTypeIndex() == AnyAtomicType::DURATION &&
     atom2->isNumericValue()) {
    return (const Item::Ptr)((const ATDurationOrDerived*)(const AnyAtomicType*)atom1)->multiply((const Numeric::Ptr)atom2, context);
  }

  // numeric * numeric
  if(atom1->isNumericValue()) {
    if(atom2->isNumericValue()) {
      return (const Item::Ptr)((Numeric*)(const AnyAtomicType*)atom1)->multiply((const Numeric::Ptr )atom2, context);
    }
    else {
      XQThrow(XPath2ErrorException,X("Multiply::collapseTreeInternal"), X("An attempt to multiply a non numeric type to a numeric type has occurred [err:XPTY0004]"));
    }
  }

  XQThrow(XPath2ErrorException,X("Multiply::collapseTreeInternal"), X("The operator * has been called on invalid operand types [err:XPTY0004]"));

}

