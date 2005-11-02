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
  string-join function
*/

#ifndef _FUNCTIONSTRINGJOIN_HPP
#define _FUNCTIONSTRINGJOIN_HPP

#include <xqilla/framework/Pathan.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>

/* string-join function */
class PATHAN_EXPORT FunctionStringJoin : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  //Constructor.
  FunctionStringJoin(const VectorOfDataItems &args, XPath2MemoryManager* memMgr);
  
protected:
  /* Accepts a sequence of strings and returns the strings concatenated together with an optional separator. */
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;

};

#endif // _FUNCTIONSTRINGJOIN_HPP
