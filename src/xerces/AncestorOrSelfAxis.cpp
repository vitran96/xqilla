/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Oracle. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#include "../config/xqilla_config.h"
#include "AncestorOrSelfAxis.hpp"
#include <xercesc/dom/DOMNode.hpp>
#include <xqilla/utils/XPath2NSUtils.hpp>

AncestorOrSelfAxis::AncestorOrSelfAxis(const LocationInfo *info, const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *contextNode, const Node *nodeObj,
       const NodeTest *nodeTest, const AxisNodeFactory &factory)
  : Axis(info, contextNode, nodeObj, nodeTest, factory),
    ancestor_(0)
{
}

const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *AncestorOrSelfAxis::nextNode(DynamicContext *context)
{
  if(toDo_) {
    // initialise
    toDo_ = false;
    ancestor_ = contextNode_;
  }
  else if(ancestor_ != 0) {
    ancestor_ = getParent(ancestor_);
  }

  return ancestor_;
}

std::string AncestorOrSelfAxis::asString(DynamicContext *context, int indent) const
{
  return getIndent(indent) + "<ancestor_or_self_axis/>";
}