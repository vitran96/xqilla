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

#include "../config/pathan_config.h"
#include <xqilla/functions/FunctionPrefixFromQName.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/ATQNameOrDerived.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>

const XMLCh FunctionPrefixFromQName::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_f, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_x, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_f, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chDash, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_Q, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_N, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionPrefixFromQName::minArgs = 1;
const unsigned int FunctionPrefixFromQName::maxArgs = 1;

/**
 * fn:prefix-from-QName($arg as xs:QName?) as xs:NCNAME?
**/

FunctionPrefixFromQName::FunctionPrefixFromQName(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "QName?", args, memMgr)
{
}

Sequence FunctionPrefixFromQName::collapseTreeInternal(DynamicContext* context, int flags) const
{
  Sequence arg=getParamNumber(1,context);
  if(arg.isEmpty())
    return Sequence(context->getMemoryManager());
  return Sequence(context->getPathanFactory()->createStringOrDerived(XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA,
                                                                     XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_NCNAME,
                                                                     ((const ATQNameOrDerived*)(const Item*)arg.first())->getPrefix(), 
                                                                     context),
                  context->getMemoryManager());
}
