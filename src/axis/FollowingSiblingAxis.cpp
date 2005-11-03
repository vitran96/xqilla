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
#include <xqilla/axis/FollowingSiblingAxis.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xqilla/items/Node.hpp>

FollowingSiblingAxis::FollowingSiblingAxis(const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *contextNode, const Node *nodeObj,
       const NodeTest *nodeTest, DynamicContext *context, const AxisNodeFactory &factory)
  : Axis(contextNode, nodeObj, nodeTest, context, factory),
    node_(0)
{
}

const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *FollowingSiblingAxis::nextNode()
{
  if(toDo_) {
    // initialise
    toDo_ = false;
    node_ = getNextSibling(contextNode_);
  }
  else if(node_ != 0) {
    node_ = getNextSibling(node_);
  }

  return node_;
}

std::string FollowingSiblingAxis::asString(DynamicContext *context, int indent) const
{
  return getIndent(indent) + "<following_sibling_axis/>";
}
