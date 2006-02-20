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

#ifndef _XQTREATAS_HPP
#define _XQTREATAS_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ASTNodeImpl.hpp>
#include <xqilla/runtime/LazySequenceResult.hpp>

class SequenceType;

class XQILLA_API XQTreatAs : public ASTNodeImpl
{
public:
  XQTreatAs(ASTNode* expr, const SequenceType *exprType, XPath2MemoryManager* memMgr);

  virtual Result createResult(DynamicContext* context, int flags=0) const;
  virtual ASTNode* staticResolution(StaticContext *context);

  const ASTNode *getExpression() const;
  const SequenceType *getSequenceType() const;
  bool getDoTypeCheck() const { return _doTypeCheck; }

  void setExpression(ASTNode *item);

protected:
  ASTNode* _expr;
  const SequenceType* _exprType;
  bool _doTypeCheck;
};

#endif
