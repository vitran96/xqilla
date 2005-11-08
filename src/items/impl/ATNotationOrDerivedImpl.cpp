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

#include "../../config/xqilla_config.h"
#include "ATNotationOrDerivedImpl.hpp"
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/exceptions/IllegalArgumentException.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xqilla/utils/XStr.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xqilla/context/DynamicContext.hpp>

ATNotationOrDerivedImpl::
ATNotationOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const XMLCh* value, const StaticContext* context): 
    ATNotationOrDerived(),
    _typeName(typeName),
    _typeURI(typeURI) { 
    
  _notation = context->getMemoryManager()->getPooledString(value);
      
}

void *ATNotationOrDerivedImpl::getInterface(const XMLCh *name) const
{
  if(name == Item::gXQilla) {
    return (void*)this;
  }
  return 0;
}

/* Get the name of the primitive type (basic type) of this type
 * (ie "decimal" for xs:decimal) */
const XMLCh* ATNotationOrDerivedImpl::getPrimitiveTypeName() const {
  return this->getPrimitiveName();
}

const XMLCh* ATNotationOrDerivedImpl::getPrimitiveName()  {
  return XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgNotationString;
}

/* Get the name of this type  (ie "integer" for xs:integer) */
const XMLCh* ATNotationOrDerivedImpl::getTypeName() const {
  return _typeName;
}

/* Get the namespace URI for this type */
const XMLCh* ATNotationOrDerivedImpl::getTypeURI() const {
  return _typeURI; 
}

AnyAtomicType::AtomicObjectType ATNotationOrDerivedImpl::getTypeIndex() {
  return AnyAtomicType::NOTATION;
} 

/* returns the XMLCh* (canonical) representation of this type */
const XMLCh* ATNotationOrDerivedImpl::asString(const DynamicContext* context) const {
  return _notation;
}

/* returns true if the two objects are equal (string comparison)
   * false otherwise */
bool ATNotationOrDerivedImpl::equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const {
  if(this->getPrimitiveTypeIndex() != target->getPrimitiveTypeIndex()) {
    DSLthrow(IllegalArgumentException,X("ATNotationOrDerivedImpl::equals"), X("Equality operator for given types not supported"));
  }
  return XPath2Utils::equals(target->asString(context), _notation);  
}

AnyAtomicType::AtomicObjectType ATNotationOrDerivedImpl::getPrimitiveTypeIndex() const {
  return this->getTypeIndex();
}