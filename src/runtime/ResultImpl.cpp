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
#include <sstream>

#include <xqilla/runtime/ResultImpl.hpp>
#include <xqilla/runtime/SequenceResult.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/ATFloatOrDerived.hpp>
#include <xqilla/items/ATDoubleOrDerived.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/exceptions/XPath2TypeMatchException.hpp>

ResultImpl::ResultImpl(DynamicContext *context)
  : ReferenceCounted(),
    context_(context)
{
  // Do nothing
}

ResultImpl::~ResultImpl()
{
  // Do nothing
}

void ResultImpl::skip()
{
  // Does nothing by default
}

static inline bool getEffectiveBooleanValueInternal(const Item::Ptr &first, const Item::Ptr &second, DynamicContext* context)
{
  // If its operand is a singleton value ...
  if(second == NULLRCP && first->isAtomicValue()) {
      const AnyAtomicType* atom=(const AnyAtomicType*)(const Item*)first;
    // ... of type xs:boolean or derived from xs:boolean, fn:boolean returns the value of its operand unchanged.
    if(atom->getPrimitiveTypeIndex() == AnyAtomicType::BOOLEAN)
      return ((const ATBooleanOrDerived*)atom)->isTrue();

    // ... of type xs:string, xdt:untypedAtomic, or a type derived from one of these, fn:boolean returns false 
    // if the operand value has zero length; otherwise it returns true.
    if((atom->getPrimitiveTypeIndex() == AnyAtomicType::STRING || atom->getPrimitiveTypeIndex() == AnyAtomicType::UNTYPED_ATOMIC))
      return !XPath2Utils::equals(atom->asString(context), XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString);

    // ... of any numeric type or derived from a numeric type, fn:boolean returns false if the operand value is 
    // NaN or is numerically equal to zero; otherwise it returns true.
    if(atom->isNumericValue()) {
      if(((const Numeric*)atom)->isZero())
        return false;

      // The singleton xs:float or xs:double value NaN.
      if(atom->getPrimitiveTypeIndex() == AnyAtomicType::FLOAT && ((const ATFloatOrDerived*)atom)->isNaN())
        return false;

      if(atom->getPrimitiveTypeIndex() == AnyAtomicType::DOUBLE && ((const ATDoubleOrDerived*)atom)->isNaN())
        return false;

      return true;
    }
  }

  // In all other cases, fn:boolean raises a type error. 
  DSLthrow(XPath2TypeMatchException,X("ResultImpl::getEffectiveBooleanValue"), X("Effective Boolean Value cannot be extracted from this type [err:FORG0006]"));
  return true;
}

bool ResultImpl::getEffectiveBooleanValue(DynamicContext* context)
{
  const Item::Ptr first = next(context);
  if(first == NULLRCP) return false;
  if(first->isNode()) return true;
  return getEffectiveBooleanValueInternal(first, next(context), context);
}

bool ResultImpl::getEffectiveBooleanValue(const Item::Ptr &first, const Item::Ptr &second, DynamicContext* context)
{
  // From $ 15.1.4 of the F&O specs:
  // The effective boolean value of an operand is defined as follows:
  //
  // If its operand is an empty sequence, fn:boolean returns false.
  if(first == NULLRCP) {
    return false;
  }

  // If its operand is a sequence whose first item is a node, fn:boolean returns true.
  if(first->isNode())
    return true;

  return getEffectiveBooleanValueInternal(first, second, context);
}

Sequence ResultImpl::toSequence(DynamicContext *context)
{
  if(context == 0) context = context_;

  Sequence result(context->getMemoryManager());

  Item::Ptr item = 0;
  while((item = next(context)) != NULLRCP) {
    result.addItem(item);
  }

  return result;
}

std::string ResultImpl::getIndent(int indent)
{
  std::ostringstream oss;

  for(int i = 0; i < indent; ++i) {
    oss << "  ";
  }

  return oss.str();
}