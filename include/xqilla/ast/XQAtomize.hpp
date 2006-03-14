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

#ifndef _XQATOMIZE_HPP
#define _XQATOMIZE_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/ASTNodeImpl.hpp>

class XQILLA_API XQAtomize : public ASTNodeImpl
{
public:
  XQAtomize(ASTNode* expr, XPath2MemoryManager* memMgr);

  virtual Result createResult(DynamicContext* context, int flags=0) const;
  virtual ASTNode* staticResolution(StaticContext *context);

  const ASTNode *getExpression() const { return expr_; }
  void setExpression(ASTNode *expr) { expr_ = expr; }

protected:
  ASTNode* expr_;
};

class XQILLA_API AtomizeResult : public ResultImpl
{
public:
  AtomizeResult(const Result &parent)
    : _parent(parent), _sub(0) {}
  Item::Ptr next(DynamicContext *context);
  std::string asString(DynamicContext *context, int indent) const { return "atomizeresult"; }
private:
  Result _parent;
  Result _sub;
};

#endif
