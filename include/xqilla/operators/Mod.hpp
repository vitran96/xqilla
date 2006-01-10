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
   Mod operator function
*/

#ifndef _MOD_HPP
#define _MOD_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/operators/ArithmeticOperator.hpp>

/** OpMod operator function*/
class XQILLA_API Mod : public ArithmeticOperator
{
public:
  static const XMLCh name[];

  Mod(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  Item::Ptr execute(const AnyAtomicType::Ptr &atom1, const AnyAtomicType::Ptr &atom2, DynamicContext *context) const;
};

#endif // _FUNCTIONOPMOD_HPP

