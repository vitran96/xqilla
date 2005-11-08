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
#include <xqilla/axis/FollowingAxis.hpp>

#include <xqilla/items/Node.hpp>

#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>

FollowingAxis::FollowingAxis(const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *contextNode, const Node *nodeObj,
       const NodeTest *nodeTest, DynamicContext *context, const AxisNodeFactory &factory)
  : Axis(contextNode, nodeObj, nodeTest, context, factory),
    node_(0)
{
}

const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *FollowingAxis::nextNode()
{
  if(toDo_) {
    // initialise
    toDo_ = false;
    node_ = contextNode_;
  }
  
  if(node_ != 0) {
    const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *result = 0;

    if(node_ != contextNode_) {
      result = getFirstChild(node_);
    }

    while(result == 0 && node_ != 0) {
      result = getNextSibling(node_);
      if(result == 0) {
        node_ = getParent(node_);
      }
    }

    node_ = result;
  }

  return node_;
}

std::string FollowingAxis::asString(DynamicContext *context, int indent) const
{
  return getIndent(indent) + "<following_axis/>";
}