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
#include <xqilla/functions/FunctionStringJoin.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/framework/XMLBuffer.hpp>

const XMLCh FunctionStringJoin::name[] = { 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_g, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_j, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionStringJoin::minArgs = 2;
const unsigned int FunctionStringJoin::maxArgs = 2;

/**
 * fn:string-join($arg1 as xs:string*, $arg2 as xs:string) as xs:string
**/

FunctionStringJoin::FunctionStringJoin(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string*, string", args, memMgr)
{
  // Nothing to do
}

Sequence FunctionStringJoin::collapseTreeInternal(DynamicContext* context, int flags) const {
	XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer result(1023, context->getMemoryManager());
  XPath2MemoryManager* memMgr = context->getMemoryManager();
  Sequence strSeq = getParamNumber(1, context);
  const XMLCh* strSep = getParamNumber(2,context).next(context)->asString(context);

  //if the sequence is non-empty, append the 1st string to the result
  if(!strSeq.isEmpty()) {
    Sequence::iterator end = strSeq.end();
    Sequence::iterator i = strSeq.begin();

    result.append((*i)->asString(context));

    //join the last length - 1 strings each prefixed by the separator
    for(++i; i != end; ++i) {
      result.append(strSep);
      result.append((*i)->asString(context));
    }
  }
  
  const ATStringOrDerived::Ptr strResult = context->getItemFactory()->createString(result.getRawBuffer(), context);
  return Sequence(strResult, memMgr);
}