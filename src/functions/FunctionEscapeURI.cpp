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
#include <xqilla/functions/FunctionEscapeURI.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/util/XMLUni.hpp>

const XMLCh FunctionEscapeURI::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionEscapeURI::minArgs = 2;
const unsigned int FunctionEscapeURI::maxArgs = 2;

/**
 * fn:escape-uri($uri-part as xs:string?, $escape-reserved as xs:boolean) as xs:string
 **/

FunctionEscapeURI::FunctionEscapeURI(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?, boolean", args, memMgr) 
{
}

Sequence FunctionEscapeURI::collapseTreeInternal(DynamicContext* context, int flags) const
{
  Sequence string=getParamNumber(1, context);
  if(string.isEmpty())
    return Sequence(context->getXQillaFactory()->createString(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString, context),
                    context->getMemoryManager());
  
  const XMLCh* str = string.first()->asString(context);
  
  const ATBooleanOrDerived::Ptr escapeRes = (const ATBooleanOrDerived::Ptr )getParamNumber(2,context).next(context);

  const XMLCh* escapedURI = XPath2Utils::escapeURI(str, ((const ATBooleanOrDerived*)escapeRes)->isTrue(), context->getMemoryManager());
  if(!escapedURI) {
    escapedURI = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
  }
  
  return Sequence(context->getXQillaFactory()->createString(escapedURI, context),
                  context->getMemoryManager());
}
