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
 * fn:prefix-from-QName function
 */

#ifndef _FUNCTIONPREFIXFROMQNAME_HPP
#define _FUNCTIONPREFIXFROMQNAME_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>
#include <xqilla/runtime/Sequence.hpp>

class XQILLA_API FunctionPrefixFromQName : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionPrefixFromQName(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  /** Returns the prefix part of a QName, eg for foo:bar it returns foo */
  Sequence createSequence(DynamicContext* context, int flags=0) const;
};

#endif // _FUNCTIONPREFIXFROMQNAME_HPP
