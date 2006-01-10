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

#include <sstream>

#include "../config/xqilla_config.h"
#include <xqilla/items/AnyAtomicTypeConstructor.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/ItemFactory.hpp>
#include <xqilla/utils/UTF8Str.hpp>

AnyAtomicTypeConstructor::AnyAtomicTypeConstructor(const XMLCh* typeURI,
                                                   const XMLCh* typeName,
                                                   const XMLCh* value,
                                                   bool numeric)
  : _typeURI(typeURI),
    _typeName(typeName),
    _value(value),
    _numeric(numeric)
{
}

bool AnyAtomicTypeConstructor::isNumeric() const
{
  return _numeric;
}

Item::Ptr AnyAtomicTypeConstructor::createItem(const DynamicContext* context) const
{
  return context->getItemFactory()->createDerivedFromAtomicType(_typeURI, _typeName, _value, context);
}

std::string AnyAtomicTypeConstructor::asString(const DynamicContext* context) const
{
  std::ostringstream s;

  s << "<AnyAtomicTypeConstructor";
  s << " value=\"" << UTF8(_value);
  s << "\" typeuri=\"" << UTF8(_typeURI);
  s << "\" typename=\"" << UTF8(_typeName);
  s << "\"/>";

  return s.str();
}
