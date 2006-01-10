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

#include "../config/xqilla_config.h"
#include <assert.h>
#include <xqilla/functions/FunctionRoot.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xqilla/items/DatatypeFactory.hpp>

const XMLCh FunctionRoot::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionRoot::minArgs = 0;
const unsigned int FunctionRoot::maxArgs = 1;

/**
 * fn:root() as node()
 * fn:root($arg as node()?) as node()?
**/

FunctionRoot::FunctionRoot(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "node()?", args, memMgr)
{
  _src.setProperties(StaticResolutionContext::DOCORDER | StaticResolutionContext::GROUPED | StaticResolutionContext::PEER | StaticResolutionContext::SAMEDOC | StaticResolutionContext::ONENODE);
  _src.getStaticType().flags = StaticType::NODE_TYPE;
}

/*static*/ Node::Ptr FunctionRoot::root(const Node::Ptr &node, const DynamicContext *context) 
{
  Node::Ptr result = node;
  Node::Ptr parent = node->dmParent(context);
  while(parent.notNull()) {
    result = parent;
    parent = result->dmParent(context);
  }
  return result;
}

ASTNode* FunctionRoot::staticResolution(StaticContext *context) {
  if(_args.empty()) {
    _src.contextItemUsed(true);
  }
  return resolveASTNodes(_args, context, !_args.empty());
}

Sequence FunctionRoot::collapseTreeInternal(DynamicContext* context, int flags) const
{
	XPath2MemoryManager* memMgr = context->getMemoryManager();

  Node::Ptr node = NULL;
  if(getNumArgs() == 1)
  {
    Sequence arg1=getParamNumber(1,context);
    if(arg1.isEmpty())
      return Sequence(memMgr);
    node = (const Node::Ptr )arg1.first();
  }
  else
  {
    const Item::Ptr item = context->getContextItem();
    if(item==NULLRCP)
        XQThrow(FunctionException, X("FunctionRoot::collapseTreeInternal"),X("Undefined context item in fn:root [err:FONC0001]"));
    if(!item->isNode())
        XQThrow(FunctionException, X("FunctionRoot::collapseTreeInternal"),X("The context item is not a node [err:XPTY0006]"));
    node = (const Node::Ptr )item;
  }
  return Sequence(root(node, context), memMgr);
}
