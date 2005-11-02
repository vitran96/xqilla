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

/*
   current-date function
*/

#ifndef _FUNCTIONCURRENTDATE_HPP
#define _FUNCTIONCURRENTDATE_HPP

#include <xqilla/framework/Pathan.hpp>

#include <xqilla/ast/DataItemFunction.hpp>

/** Current-date function*/
class PATHAN_EXPORT FunctionCurrentDate : public DataItemFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionCurrentDate(const VectorOfDataItems &args, XPath2MemoryManager* memMgr);
  
  virtual DataItem* staticResolution(StaticContext *context);

  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;
};

#endif // _FUNCTIONCURRENTDATE_HPP



