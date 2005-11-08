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

#ifndef _ATQNAMEORDERIVEDIMPL_HPP
#define _ATQNAMEORDERIVEDIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/items/ATQNameOrDerived.hpp>

#include <xqilla/framework/XQillaExport.hpp>

class XQILLA_API ATQNameOrDerivedImpl : public ATQNameOrDerived 
{

public:

  /* constructor */
  ATQNameOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const XMLCh* value, const StaticContext* context);

  ATQNameOrDerivedImpl(const XMLCh* typeURI, const XMLCh* typeName, const XMLCh* uri, const XMLCh* prefix, const XMLCh* name, const StaticContext* context);
  
  virtual void *getInterface(const XMLCh *name) const;

  /* Get the name of the primitive type (basic type) of this type
   * (ie "decimal" for xs:decimal) */
  virtual const XMLCh* getPrimitiveTypeName() const;

  /* Get the namespace URI for this type */
  virtual const XMLCh* getTypeURI() const;

  /* Get the name of this type  (ie "integer" for xs:integer) */
  virtual const XMLCh* getTypeName() const;

  /* returns the URI */
	virtual const XMLCh* getURI(void) const;

	/* returns the prefix */
	virtual const XMLCh* getPrefix(void) const;

	/* returns the name */
	virtual const XMLCh* getName(void) const;

  /* returns the XMLCh* (canonical) representation of this type */
  virtual const XMLCh* asString(const DynamicContext* context) const;

  /* returns the XMLCh* (lexical := prefix:localname) representation of this type */
  const XMLCh* asLexicalString(const DynamicContext* context) const;

  /* returns true if the two objects' URI are equal (string comparison)
   * false otherwise */
  virtual bool equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const;
  
  /* Get the primitive index associated with this type */
  static AnyAtomicType::AtomicObjectType getTypeIndex(); 

  /* Get the primitive type name */
  static const XMLCh* getPrimitiveName();

  /* Get the primitive index associated with this type */
  virtual AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex() const;

protected:
  
  /* If possible, cast this type to the target type */
  virtual AnyAtomicType::Ptr castAsInternal(AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const;

private:

  /*The uri value of this QName*/
  const XMLCh* _uri;

  /*The prefix of this QName */
  const XMLCh* _prefix;

  /*The local name value of this QName */
  const XMLCh* _name;

  /* the name of this type */
  const XMLCh* _typeName;

  /* the uri of this type */
  const XMLCh* _typeURI;
 
};

#endif // _ATQNAMEORDERIVEDIMPL_HPP