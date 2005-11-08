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

#include "../../config/xqilla_config.h"
#include "ATBase64BinaryOrDerivedImpl.hpp"
#include "ATHexBinaryOrDerivedImpl.hpp"
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/exceptions/IllegalArgumentException.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/Base64.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/ItemFactory.hpp>

ATBase64BinaryOrDerivedImpl::
ATBase64BinaryOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const XMLCh* value, const StaticContext* context): 
    _typeName(typeName),
    _typeURI(typeURI){ 
    
  _base64Data = context->getMemoryManager()->getPooledString(value);
}

void *ATBase64BinaryOrDerivedImpl::getInterface(const XMLCh *name) const
{
  if(name == Item::gXQilla) {
    return (void*)this;
  }
  return 0;
}

/* Get the name of the primitive type (basic type) of this type (ie "decimal" for xs:decimal) */
const XMLCh* ATBase64BinaryOrDerivedImpl::getPrimitiveTypeName() const {
  return this->getPrimitiveName();
}

const XMLCh* ATBase64BinaryOrDerivedImpl::getPrimitiveName()  {
  return XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_BASE64BINARY;
}

/* Get the name of this type  (ie "integer" for xs:integer) */
const XMLCh* ATBase64BinaryOrDerivedImpl::getTypeName() const {
  return _typeName;
}

/* Get the namespace URI for this type */
const XMLCh* ATBase64BinaryOrDerivedImpl::getTypeURI() const {
  return _typeURI; 
}

AnyAtomicType::AtomicObjectType ATBase64BinaryOrDerivedImpl::getTypeIndex() {
  return AnyAtomicType::BASE_64_BINARY;
} 

/* If possible, cast this type to the target type */
AnyAtomicType::Ptr ATBase64BinaryOrDerivedImpl::castAsInternal(AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const
{
  switch(targetIndex) {
    case HEX_BINARY: {
      unsigned int srcLen = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(_base64Data);
      XMLByte *dataInByte = (XMLByte*) context->getMemoryManager()->allocate((srcLen+1) * sizeof(XMLByte));
      XERCES_CPP_NAMESPACE_QUALIFIER ArrayJanitor<XMLByte> janFill(dataInByte, context->getMemoryManager());

      unsigned int i;
      for (i = 0; i < srcLen; i++)
        dataInByte[i] = (XMLByte)_base64Data[i];

	  dataInByte[srcLen] = 0;

      unsigned int length=0;
      XMLByte* decodedBinary=XERCES_CPP_NAMESPACE_QUALIFIER Base64::decode(dataInByte, 
                                                                           &length, 
                                                                           context->getMemoryManager(), 
                                                                           XERCES_CPP_NAMESPACE_QUALIFIER Base64::Conf_Schema); 
      XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer buf(length*2, context->getMemoryManager());
      XMLCh hexDigits[]={ XERCES_CPP_NAMESPACE_QUALIFIER chDigit_0, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_1,
                          XERCES_CPP_NAMESPACE_QUALIFIER chDigit_2, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_3,
                          XERCES_CPP_NAMESPACE_QUALIFIER chDigit_4, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_5,
                          XERCES_CPP_NAMESPACE_QUALIFIER chDigit_6, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_7,
                          XERCES_CPP_NAMESPACE_QUALIFIER chDigit_8, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_9,
                          XERCES_CPP_NAMESPACE_QUALIFIER chLatin_A, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_B,
                          XERCES_CPP_NAMESPACE_QUALIFIER chLatin_C, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_D,
                          XERCES_CPP_NAMESPACE_QUALIFIER chLatin_E, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_F
      }                 ;
      for(i=0;i<length;i++)
      {
          buf.append(hexDigits[decodedBinary[i]/16]);
          buf.append(hexDigits[decodedBinary[i]%16]);
      }
      context->getMemoryManager()->deallocate(decodedBinary);
      return new ATHexBinaryOrDerivedImpl(targetURI, targetType, buf.getRawBuffer(), context);
    }
    default: {
      return AnyAtomicType::castAsInternal(targetIndex, targetURI, targetType, context);
    }
  }
}

/* returns the XMLCh* (canonical) representation of this type */
const XMLCh* ATBase64BinaryOrDerivedImpl::asString(const DynamicContext* context) const {
  return _base64Data;
}

bool ATBase64BinaryOrDerivedImpl::equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const {
  if(this->getPrimitiveTypeIndex() != target->getPrimitiveTypeIndex()) {
    XQThrow(IllegalArgumentException,X("ATBase64BinaryOrDerivedImpl::equals"), X("Equality operator for given types not supported"));
  }
  return XPath2Utils::equals(target->asString(context), _base64Data);  
}

AnyAtomicType::AtomicObjectType ATBase64BinaryOrDerivedImpl::getPrimitiveTypeIndex() const {
  return this->getTypeIndex();
}
