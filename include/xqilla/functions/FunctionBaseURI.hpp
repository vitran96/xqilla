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

   base-uri function

*/

#ifndef _FUNCTIONBASEURI_HPP
#define _FUNCTIONBASEURI_HPP

#include <xqilla/framework/Pathan.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>
#include <xqilla/runtime/Sequence.hpp>

/** base-uri function */
class PATHAN_EXPORT FunctionBaseURI : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionBaseURI(const VectorOfDataItems &args, XPath2MemoryManager* memMgr);
  
  virtual DataItem* staticResolution(StaticContext *context);

	/* returns the base-URI property of document or element nodes,
	 * and the empty sequence for all other kinds of nodes */
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;
};

#endif
