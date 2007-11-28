/*
 * Copyright (c) 2001-2007
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2007
 *     Oracle. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Id$
 */

#ifndef _XQSTEP_HPP
#define _XQSTEP_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ASTNodeImpl.hpp>

class NodeTest;

///this class calculates a node list based on a context
class XQILLA_API XQStep : public ASTNodeImpl
{
public:
  enum Axis {
    ANCESTOR,
    ANCESTOR_OR_SELF,
    ATTRIBUTE,
    CHILD,
    DESCENDANT,
    DESCENDANT_OR_SELF,
    FOLLOWING,
    FOLLOWING_SIBLING,
    NAMESPACE,
    PARENT,
    PRECEDING,
    PRECEDING_SIBLING,
    SELF
  };

  //constuctor that takes the step this XQ is refuring to
  XQStep(Axis axis, NodeTest* nodeTest, XPath2MemoryManager* memMgr);
  ~XQStep();

  virtual ASTNode* staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);
  virtual Result createResult(DynamicContext* context, int flags=0) const;

  const NodeTest *getNodeTest() const;
  void setNodeTest(NodeTest *nodeTest);

  Axis getAxis() const;
  void setAxis(Axis axis);

  static bool isForwardAxis(Axis axis);
  static unsigned int getAxisProperties(Axis axis);

private:
  NodeTest* nodeTest_;
  Axis axis_;
};

/**
 * Lazily apply an axis and NodeTest filter to the context node
 */
class XQILLA_API StepResult : public ResultImpl
{
public:
  StepResult(XQStep::Axis axis, const NodeTest *nt, const LocationInfo *location);
  virtual ~StepResult() {}

  Item::Ptr next(DynamicContext *context);
  std::string asString(DynamicContext *context, int indent) const;

protected:
  bool toDo_;
  Result result_;

  XQStep::Axis axis_;
  const NodeTest *nodeTest_;
};

#endif
