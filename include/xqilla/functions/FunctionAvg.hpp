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

/*
 * Avg function -- takes a sequence, returns a vlue of the same type as the items which is
 * the average of the values
 */

#ifndef _FUNCTIONAVG_HPP
#define _FUNCTIONAVG_HPP

#include <xqilla/ast/AggregateFunction.hpp>

/** Avg operator function*/
class XQILLA_API FunctionAvg : public AggregateFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionAvg(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  /** Takes a list of nodes and averages their values */
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;

};

#endif // _FUNCTIONAVG_HPP
