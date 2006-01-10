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
   index-of function: returns the location(s) of the specified item in a sequence
*/

#ifndef _FUNCTIONINDEXOF_HPP
#define _FUNCTIONINDEXOF_HPP

#include <xqilla/ast/ConstantFoldingFunction.hpp>
#include <xqilla/runtime/Sequence.hpp>

class XPath2MemoryManager;
class Collation;

/** index-of function*/
class XQILLA_API FunctionIndexOf : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionIndexOf(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  /** Returns a sequence of indices where the item occurs in the sequence */
  Sequence indexOf(Sequence &list, const Item::Ptr &item, Collation* collation, DynamicContext* context) const;
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;
};

#endif // _FUNCTIONINDEXOF_HPP
