/*
 * Copyright (c) 2001-2005
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2005
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2005
 *     Sleepycat Software. All rights reserved.
 * Copyright (c) 2004-2005
 *     Parthenon Computing Ltd. All rights reserved.
 *
 * Please see the file LICENSE for more information.
 *
 * $Id$
 */

#include "../config/xqilla_config.h"
#include <assert.h>
#include <xqilla/operators/Divide.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/items/Numeric.hpp>
#include <xqilla/items/ATDurationOrDerived.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/items/AnyAtomicType.hpp>
#include <xqilla/context/DynamicContext.hpp>

/*static*/ const XMLCh Divide::name[]={ XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_v, XERCES_CPP_NAMESPACE_QUALIFIER chNull };

Divide::Divide(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ArithmeticOperator(name, args, memMgr)
{
  // Nothing to do
}

Item::Ptr Divide::execute(const AnyAtomicType::Ptr &atom1, const AnyAtomicType::Ptr &atom2, DynamicContext *context) const
{
  if(atom1 == NULLRCP || atom2 == NULLRCP) return 0;
  
  if(atom1->isNumericValue()) {
    if(atom2->isNumericValue()) {
      return (const Item::Ptr)((Numeric*)(const AnyAtomicType*)atom1)->divide((const Numeric::Ptr )atom2, context);
    }
    else {
      DSLthrow(XPath2ErrorException,X("Divide::collapseTreeInternal"), X("An attempt to divide a non numeric type to a numeric type has occurred [err:XPTY0004]"));
    }
  }
  
  if(atom1->getPrimitiveTypeIndex() == AnyAtomicType::DURATION) {
    const ATDurationOrDerived* duration = (const ATDurationOrDerived*)(const AnyAtomicType*)atom1;
    if(atom2->isNumericValue()) {
      const Numeric::Ptr num = (const Numeric::Ptr )atom2;
      if(duration->isDayTimeDuration() || duration->isYearMonthDuration()) {
        return (const Item::Ptr)duration->divide(num, context);
      } else {
        DSLthrow(XPath2ErrorException,X("Divide::collapseTreeInternal"), X("An invalid attempt to divide an xs:duration by a decimal type has occurred [err:XPTY0004]"));
      }
    } else if(atom2->getPrimitiveTypeIndex() == AnyAtomicType::DURATION) {
      const ATDurationOrDerived* divisor = (const ATDurationOrDerived*)(const AnyAtomicType*)atom2;
      if((duration->isDayTimeDuration() && divisor->isDayTimeDuration()) || 
         (duration->isYearMonthDuration() && divisor->isYearMonthDuration())) {
          return (const Item::Ptr)duration->divide(divisor, context);
      } else {
        DSLthrow(XPath2ErrorException,X("Divide::collapseTreeInternal"), X("An invalid attempt to divide an xs:duration by a duration type has occurred [err:XPTY0004]"));
      }
    } else {
      DSLthrow(XPath2ErrorException,X("Divide::collapseTreeInternal"), X("An invalid attempt to divide an xs:duration by a non-decimal type has occured [err:XPTY0004]"));
    }
  } else {
      DSLthrow(XPath2ErrorException,X("Divide::collapseTreeInternal"), X("The operator div has been called on invalid operand types [err:XPTY0004]"));
  }

  return 0;
}
