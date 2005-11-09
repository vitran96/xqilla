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

#ifndef _ATFLOATORDERIVEDIMPL_HPP
#define _ATFLOATORDERIVEDIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/items/ATFloatOrDerived.hpp>
#include <xqilla/mapm/m_apm.h>

#include <xqilla/framework/XQillaExport.hpp>

#define FLOAT_MAX_DIGITS 25

class XQILLA_API ATFloatOrDerivedImpl : public ATFloatOrDerived 
{

public:

  /* constructor */
  ATFloatOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const XMLCh* value, const StaticContext* context);

  /* constructor */
  ATFloatOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const MAPM value, const StaticContext* context);

  /** destructor -- do nothing*/
  virtual ~ATFloatOrDerivedImpl() { };
  
  virtual void *getInterface(const XMLCh *name) const;

  /* Get the name of the primitive type (basic type) of this type
   * (ie "decimal" for xs:decimal) */
  virtual const XMLCh* getPrimitiveTypeName() const;

  /* Get the namespace URI for this type */
  virtual const XMLCh* getTypeURI() const;

  /* Get the name of this type  (ie "integer" for xs:integer) */
  virtual const XMLCh* getTypeName() const;

  /* returns the XMLCh* (canonical) representation of this type */
  virtual const XMLCh* asString(const DynamicContext* context) const;

  /* Promote this to the given type, if possible */
  virtual Numeric::Ptr promoteTypeIfApplicable(const XMLCh* typeURI, const XMLCh* typeName, const DynamicContext* context) const;
  
  /* returns true if the two objects' decimal values are equal
   * false otherwise */
  virtual bool equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const;

  /** Returns true if this is less than other, false otherwise */
  virtual bool lessThan(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns true if this is greater than other, false otherwise */
  virtual bool greaterThan(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns a Numeric object which is the sum of this and other */
  virtual Numeric::Ptr add(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns a Numeric object which is the difference of this and
   * other */
  virtual Numeric::Ptr subtract(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns a Numeric object which is the product of this and other */
  virtual Numeric::Ptr multiply(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns a Numeric object which is the quotient of this and other */
  virtual Numeric::Ptr divide(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns the arithmetic product of its operands as a Numeric */
  virtual Numeric::Ptr mod(const Numeric::Ptr &other, const DynamicContext* context) const;

  /** Returns the floor of this Numeric */
  virtual Numeric::Ptr floor(const DynamicContext* context) const;

  /** Returns the ceiling of this Numeric */
  virtual Numeric::Ptr ceiling(const DynamicContext* context) const;

  /** Rounds this Numeric */
  virtual Numeric::Ptr round(const DynamicContext* context) const;

  /** Rounds this Numeric to the given precision, and rounds a half to even */
  virtual Numeric::Ptr roundHalfToEven(const Numeric::Ptr &precision, const DynamicContext* context) const;
 
  /** Returns the Additive inverse of this Numeric */
  virtual Numeric::Ptr invert(const DynamicContext* context) const;
  
  /** Does this Numeric have value 0? */
  virtual bool isZero() const;
  
  /** Is this Numeric negative? */
  virtual bool isNegative() const;

  /** Is this Numeric positive? */
  virtual bool isPositive() const;  
  
  /* Is this xs:float not a number */
  virtual bool isNaN() const;

  /* Is this xs:float infinite? */
  virtual bool isInfinite() const;

  /* Get the primitive index associated with this type */
  static AnyAtomicType::AtomicObjectType getTypeIndex(); 

  /* Get the primitive type name */
  static const XMLCh* getPrimitiveName();

  /* Get the primitive index associated with this type */
  virtual AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex() const;

  enum state {NUM, NaN, INF, NEG_INF};

protected:
  
  /* If possible, cast this type to the target type */
  virtual AnyAtomicType::Ptr castAsInternal(AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const;

private:

  /* set the value of this decimal */
  void setFloat(const XMLCh* const value, const StaticContext *context);

  /* check if the value is a valid xs:float */
  void checkLimits();

  /* returns a new infinity ATFloatOrDerived*/
  ATFloatOrDerived::Ptr infinity(const DynamicContext* context) const;

  /* returns a new negative infinity ATFloatOrDerived*/
  ATFloatOrDerived::Ptr negInfinity(const DynamicContext* context) const;

  /* returns a NaN ATFloatOrDerived*/
  ATFloatOrDerived::Ptr notANumber(const DynamicContext* context) const;

  /* returns a -0 ATFloatOrDerived*/
  ATFloatOrDerived::Ptr negZero(const DynamicContext* context) const;
  
  /*returns a ATFloatOrDerived of value value*/
  ATFloatOrDerived::Ptr newFloat(MAPM value, const DynamicContext* context) const;

  /*The value of this float*/
  MAPM _float;

  /* is it NaN, INF, NegINF, or just a float (NUM) */
  state _state;

  /* whether or not this value is negative */
  bool _isNegative;

  /* the name of this type */
  const XMLCh* _typeName;

  /* the uri of this type */
  const XMLCh* _typeURI;
 
};

#endif // _ATFLOATORDERIVEDIMPL_HPP
