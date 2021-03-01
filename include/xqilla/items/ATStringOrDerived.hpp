/*
 * Copyright (c) 2001, 2008,
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004, 2018 Oracle and/or its affiliates. All rights reserved.
 *     
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

#ifndef _ATSTRINGORDERIVED_HPP
#define _ATSTRINGORDERIVED_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/items/AnyAtomicType.hpp>
#include <xqilla/items/Numeric.hpp>

class Collation;
class Result;
class DynamicContext;

class XQILLA_API ATStringOrDerived : public AnyAtomicType
{
public:
  typedef RefCountPointer<const ATStringOrDerived> Ptr;

  /* Get the name of the primitive type (basic type) of this type
   * (ie "decimal" for xs:decimal) */
  virtual const XMLCh* getPrimitiveTypeName() const = 0;

  /* Get the namespace URI for this type */
  virtual const XMLCh* getTypeURI() const = 0;

  /* Get the name of this type  (ie "integer" for xs:integer) */
  virtual const XMLCh* getTypeName() const = 0;

  /* returns the XMLCh* (canonical) representation of this type */
  virtual const XMLCh* asString(const DynamicContext* context) const = 0;

  /* returns this string as a set of codepoints */
  virtual Result asCodepoints(const DynamicContext* context) const = 0;

  /* returns the length of this string */
  virtual unsigned int getLength() const = 0;

  /* returns the substring starting at startingLoc of given length */
  virtual ATStringOrDerived::Ptr substring(const Numeric::Ptr &startingLoc, const Numeric::Ptr &length, const DynamicContext* context) const = 0;

  /* returns the substring that occurs after the first occurence of pattern */
  virtual ATStringOrDerived::Ptr substringAfter(const ATStringOrDerived::Ptr &pattern, Collation* collation, const DynamicContext* context) const = 0;

  /* returns the substring that occurs before the first occurence of pattern */
  virtual ATStringOrDerived::Ptr substringBefore(const ATStringOrDerived::Ptr &pattern, Collation* collation, const DynamicContext* context) const = 0;

  /* returns true if the two objects' URI are equal (string comparison)
   * false otherwise */
  virtual bool equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const = 0;

  virtual AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex() const = 0;
};

#endif //  _ATSTRINGORDERIVED_HPP
