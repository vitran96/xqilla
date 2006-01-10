/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#include "../../config/xqilla_config.h"
#include "ATUntypedAtomicImpl.hpp"
#include <xqilla/items/ATDoubleOrDerived.hpp>
#include <xqilla/items/ATFloatOrDerived.hpp>
#include <xqilla/exceptions/IllegalArgumentException.hpp>
#include <xqilla/exceptions/XPath2TypeCastException.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/functions/FunctionConstructor.hpp>
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xercesc/util/XMLString.hpp>

// We ignore the type URI and typeName passed in, since they are always xdt:untypedAtomic
// (you cannot derived from it)
ATUntypedAtomicImpl::
ATUntypedAtomicImpl(const XMLCh*, const XMLCh*, const XMLCh* value, const StaticContext* context): 
    ATUntypedAtomic() {
    
  _value = context->getMemoryManager()->getPooledString(value);
      
}

void *ATUntypedAtomicImpl::getInterface(const XMLCh *name) const
{
  if(name == Item::gXQilla) {
    return (void*)this;
  }
  return 0;
}

/* Get the name of the primitive type (basic type) of this type
 * (ie "decimal" for xs:decimal) */
const XMLCh* ATUntypedAtomicImpl::getPrimitiveTypeName() const {
  return this->getPrimitiveName();
}

const XMLCh* ATUntypedAtomicImpl::getPrimitiveName()  {
  return ATUntypedAtomic::fgDT_UNTYPEDATOMIC;
}

/* Get the namespace uri of the primitive type (basic type) of this type */
const XMLCh* ATUntypedAtomicImpl::getPrimitiveTypeURI() const{
  return FunctionConstructor::XMLChXPath2DatatypesURI;
}

/* Get the name of this type  (ie "integer" for xs:integer)-- 
 * same as the primitive type name. UntypedAtomic cannot be 
 * extended */
const XMLCh* ATUntypedAtomicImpl::getTypeName() const {
  return getPrimitiveTypeName();
}

/* Get the namespace URI for this type -- same as the primitive uri
 * UntypedAtomic cannot be extended */
const XMLCh* ATUntypedAtomicImpl::getTypeURI() const {
  return getPrimitiveTypeURI(); 
}

AnyAtomicType::AtomicObjectType ATUntypedAtomicImpl::getTypeIndex() {
  return AnyAtomicType::UNTYPED_ATOMIC;
} 

AnyAtomicType::Ptr ATUntypedAtomicImpl::castAsInternal(AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const {
  switch (targetIndex) {
    case DOUBLE: {
      const XMLCh* upCase = XPath2Utils::toUpper(_value, context->getMemoryManager());
      return (const AnyAtomicType::Ptr)context->getItemFactory()->createDoubleOrDerived(targetURI, targetType, upCase, context);
    }
    case FLOAT: {
      const XMLCh* upCase = XPath2Utils::toUpper(_value, context->getMemoryManager());
      return (const AnyAtomicType::Ptr)context->getItemFactory()->createFloatOrDerived(targetURI, targetType, upCase, context);
    }
    default: return AnyAtomicType::castAsInternal(targetIndex, targetURI, targetType, context);
  }
}

/* returns the XMLCh* (canonical) representation of this type */
const XMLCh* ATUntypedAtomicImpl::asString(const DynamicContext* context) const {
  return _value;
}

/* returns true if the two objects' URI are equal (string comparison)
   * false otherwise */
bool ATUntypedAtomicImpl::equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const {
  if(this->getPrimitiveTypeIndex() != target->getPrimitiveTypeIndex()) {
    XQThrow(IllegalArgumentException,X("ATUntypedAtomicImpl::equals"), X("Equality operator for given types not supported"));
  }
  return XPath2Utils::equals(target->asString(context), _value);
}

AnyAtomicType::AtomicObjectType ATUntypedAtomicImpl::getPrimitiveTypeIndex() const {
  return this->getTypeIndex();
}
