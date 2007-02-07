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

/*
 * Avg function -- takes a sequence, returns a vlue of the same type as the items which is
 * the average of the values
 */

#ifndef _FUNCTIONAVG_HPP
#define _FUNCTIONAVG_HPP

#include <xqilla/ast/ConstantFoldingFunction.hpp>

/** Avg operator function*/
class XQILLA_API FunctionAvg : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionAvg(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  ASTNode* staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);
  /** Takes a list of nodes and averages their values */
  Sequence createSequence(DynamicContext* context, int flags=0) const;

};

#endif // _FUNCTIONAVG_HPP
