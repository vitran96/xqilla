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

   default-collation function

*/


#ifndef _FUNCTIONDEFAULTCOLLATION_HPP
#define _FUNCTIONDEFAULTCOLLATION_HPP

#include <xqilla/ast/ConstantFoldingFunction.hpp>

/** default-collation function*/
class PATHAN_EXPORT FunctionDefaultCollation : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionDefaultCollation(const VectorOfDataItems &args, XPath2MemoryManager* memMgr);
  
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;
};

#endif // _FUNCTIONDEFAULTCOLLATION_HPP
