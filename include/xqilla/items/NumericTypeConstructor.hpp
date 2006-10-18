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

#ifndef _NUMERICTYPECONSTUCTOR_HPP
#define _NUMERICTYPECONSTUCTOR_HPP

#include <xqilla/items/ItemConstructor.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/ast/StaticType.hpp>
#include <xqilla/mapm/m_apm.h>

class XQILLA_API NumericTypeConstructor : public ItemConstructor {
public:
  NumericTypeConstructor(const XMLCh* typeURI,
                         const XMLCh* typeName,
                         const MAPM& value,
                         AnyAtomicType::AtomicObjectType primitiveType);
  virtual ~NumericTypeConstructor() {}

  virtual const StaticType &getStaticType() const { return _sType; }

  virtual Item::Ptr createItem(const DynamicContext* context) const;
  virtual std::string asString(const DynamicContext* context) const;

  virtual const XMLCh* getTypeURI() const { return _typeURI; }
  virtual const XMLCh* getTypeName() const { return _typeName; }

private:
  const XMLCh *_typeURI;
  const XMLCh *_typeName;
  MAPM _value;
  AnyAtomicType::AtomicObjectType _primitiveType;
  StaticType _sType;
};

#endif
