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
#include <xqilla/axis/DescendantOrSelfAxis.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xqilla/items/Node.hpp>

DescendantOrSelfAxis::DescendantOrSelfAxis(const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *contextNode, const Node *nodeObj,
       const NodeTest *nodeTest, DynamicContext *context, const AxisNodeFactory &factory)
  : Axis(contextNode, nodeObj, nodeTest, context, factory),
    descendant_(0)
{
}

const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *DescendantOrSelfAxis::nextNode()
{
  if(toDo_) {
    // initialise
    toDo_ = false;
    descendant_ = contextNode_;
  }
  else if(descendant_ != 0) {
    const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *result = getFirstChild(descendant_);

    while(result == 0 && descendant_ != contextNode_) {
      result = getNextSibling(descendant_);
      if(result == 0) {
        descendant_ = getParent(descendant_);
      }
    }

    descendant_ = result;
  }

  return descendant_;
}

std::string DescendantOrSelfAxis::asString(DynamicContext *context, int indent) const
{
  return getIndent(indent) + "<descendant_or_self_axis/>";
}