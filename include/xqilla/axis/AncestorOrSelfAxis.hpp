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

#ifndef _ANCESTORORSELFAXIS_HPP
#define _ANCESTORORSELFAXIS_HPP

#include <xqilla/axis/Axis.hpp>

/**
This class implements the AncestorOrSelf axis as defined by the XPath spec
*/
class XQILLA_API AncestorOrSelfAxis : public Axis
{
public:
  AncestorOrSelfAxis(const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *contextNode, const Node *nodeObj,
       const NodeTest *nodeTest, DynamicContext *context,
       const AxisNodeFactory &factory = Axis::gNodeImplFactory);
  const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *nextNode();
  std::string asString(DynamicContext *context, int indent) const;
private:
  const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *ancestor_;
};


#endif

