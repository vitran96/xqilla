/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Oracle. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#ifndef _ATDECIMALORDERIVEDIMPL_HPP
#define _ATDECIMALORDERIVEDIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/mapm/m_apm.h>

#include <xqilla/framework/XQillaExport.hpp>

class StaticContext;

class XQILLA_API ATDecimalOrDerivedImpl : public ATDecimalOrDerived 
{

public:

  /* constructor */
  ATDecimalOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const XMLCh* value, const StaticContext* context);

  /* constructor */
  ATDecimalOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const MAPM value, const StaticContext* context);

  /* constructor */
  ATDecimalOrDerivedImpl(int value);

  /** destructor -- do nothing*/
  virtual ~ATDecimalOrDerivedImpl() { };
  
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
  virtual Numeric::Ptr promoteTypeIfApplicable(AnyAtomicType::AtomicObjectType typeIndex,
                                               const DynamicContext* context) const;
  
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

  /** Returns the absolute value of this Numeric */
  virtual Numeric::Ptr abs(const DynamicContext* context) const;

  /** Does this Numeric have value 0? */
  virtual bool isZero() const;

  /** Is this Numeric negative? */
  virtual bool isNegative() const;

  /** Is this Numeric positive? */
  virtual bool isPositive() const;

  /** Treat this decimal (must be integer) as a codepoint **/
  virtual XMLInt32 treatAsCodepoint(const DynamicContext* context) const;

  /* Get the primitive index associated with this type */
  virtual AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex() const;

  /* Get the primitive index associated with this type */
  static AnyAtomicType::AtomicObjectType getTypeIndex(); 

  /* Get the primitive type name */
  static const XMLCh* getPrimitiveName();
  
  virtual const MAPM &asMAPM() const { return _decimal; }

  virtual State getState() const { return isNegative()? NEG_NUM : NUM; }

  /* The significant digits */
  static unsigned int g_nSignificantDigits;

  static MAPM parseDecimal(const XMLCh* const value);

private:

  /* set the value of this decimal */
  void setDecimal(const XMLCh* const value);

  /* flag to note that we are an Integer -- to avoid many calls to
   * isInstanceOfType */
  bool _isInteger;

  /*The value of this decimal*/
  MAPM _decimal;

  /* the name of this type */
  const XMLCh* _typeName;

  /* the uri of this type */
  const XMLCh* _typeURI;
};

#endif // _ATDECIMALORDERIVEDIMPL_HPP
