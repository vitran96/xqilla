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
#include <assert.h>
#include <xqilla/functions/FunctionNamespaceUri.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>

const XMLCh FunctionNamespaceUri::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionNamespaceUri::minArgs = 0;
const unsigned int FunctionNamespaceUri::maxArgs = 1;

/**
 * fn:namespace-uri() as xs:anyURI
 * fn:namespace-uri($arg as node()?) as xs:anyURI
**/

FunctionNamespaceUri::FunctionNamespaceUri(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "node()?", args, memMgr)
{
}

ASTNode* FunctionNamespaceUri::staticResolution(StaticContext *context) {
  if(_args.empty()) {
    _src.contextItemUsed(true);
  }
  return resolveASTNodes(_args, context, !_args.empty());
}

Sequence FunctionNamespaceUri::collapseTreeInternal(DynamicContext* context, int flags) const
{
  XPath2MemoryManager* memMgr = context->getMemoryManager();

  Node::Ptr ctxNode;
  if(getNumArgs() == 1)
  {
    Sequence arg=getParamNumber(1,context);
    if(arg.isEmpty())
      return Sequence(context->getItemFactory()->createAnyURI(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString, context), memMgr);
    ctxNode=arg.first();
  }
  else
  {
    const Item::Ptr item = context->getContextItem();
    if(item==NULLRCP)
      DSLthrow(FunctionException, X("FunctionNamespaceUri::collapseTreeInternal"),X("Undefined context item in fn:namespace-uri [err:FONC0001]"));
    if(!item->isNode())
      DSLthrow(FunctionException, X("FunctionNamespaceUri::collapseTreeInternal"),X("The context item is not a node [err:XPTY0006]"));
    ctxNode=item;
  }

  ATQNameOrDerived::Ptr name = ctxNode->dmNodeName(context);
  if(name.notNull())
    return Sequence(context->getItemFactory()->createAnyURI(((const ATQNameOrDerived*)name.get())->getURI(), context), memMgr);
  
  return Sequence(context->getItemFactory()->createAnyURI(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString, context), memMgr);
}