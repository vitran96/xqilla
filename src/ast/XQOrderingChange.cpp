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

//////////////////////////////////////////////////////////////////////
// XQOrderingChange.cpp: implementation of the XQOrderingChange class.
//////////////////////////////////////////////////////////////////////

#include <sstream>

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQOrderingChange.hpp>

#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/ContextHelpers.hpp>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XQOrderingChange::XQOrderingChange(StaticContext::NodeSetOrdering ordering, ASTNode* astNode, XPath2MemoryManager* expr)
  : ASTNodeImpl(expr),
    m_nOrdering(ordering),
    m_pExpr(astNode)
{
  setType(ASTNode::ORDERING_CHANGE);
}

Result XQOrderingChange::createResult(DynamicContext *context, int flags/*=0*/) const
{
  assert(0);
  return 0;
}

ASTNode* XQOrderingChange::staticResolution(StaticContext* context)
{
  AutoNodeSetOrderingReset orderReset(context, m_nOrdering);
  return m_pExpr->staticResolution(context);
}

StaticContext::NodeSetOrdering XQOrderingChange::getOrderingValue() const
{
  return m_nOrdering;
}

ASTNode* XQOrderingChange::getExpr() const
{
  return m_pExpr;
}

void XQOrderingChange::setExpr(ASTNode *expr)
{
	m_pExpr = expr;
}
