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
#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQContextItem.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/DynamicErrorException.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>

XQContextItem::XQContextItem(XPath2MemoryManager* memMgr)
	: ASTNodeImpl(memMgr)
{
	setType(ASTNode::CONTEXT_ITEM);
}

XQContextItem::~XQContextItem() {
	//no-op
}

ASTNode* XQContextItem::staticResolution(StaticContext *context)
{
  _src.setProperties(StaticResolutionContext::DOCORDER | StaticResolutionContext::GROUPED | StaticResolutionContext::PEER | StaticResolutionContext::SUBTREE | StaticResolutionContext::SAMEDOC | StaticResolutionContext::ONENODE);
  _src.getStaticType().flags = StaticResolutionContext::NODE_TYPE | StaticResolutionContext::NUMERIC_TYPE | StaticResolutionContext::OTHER_TYPE;
  _src.contextItemUsed(true);
  return resolvePredicates(context);
}

Result XQContextItem::createResult(DynamicContext* context, int flags) const
{
  return new ContextItemResult(context);
}

XQContextItem::ContextItemResult::ContextItemResult(DynamicContext *context)
  : SingleResult(context)
{
}

Item::Ptr XQContextItem::ContextItemResult::getSingleResult(DynamicContext *context) const
{
  const Item::Ptr item = context->getContextItem();
  if(item == NULLRCP) {
    DSLthrow(DynamicErrorException,X("XQContextItem::ContextItemResult::getSingleResult"),
             X("It is an error for the context item to be undefined when using it [err:XPDY0002]"));
  }
  return item;
}

std::string XQContextItem::ContextItemResult::asString(DynamicContext *context, int indent) const
{
  return "<contextitemresult/>";
}