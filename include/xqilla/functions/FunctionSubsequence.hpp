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

#ifndef _FUNCTIONSUBSEQUENCE_HPP
#define _FUNCTIONSUBSEQUENCE_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>

class XQILLA_API FunctionSubsequence : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionSubsequence(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  Result createResult(DynamicContext* context, int flags=0) const;

private:
  class SubsequenceResult : public ResultImpl
  {
  public:
    SubsequenceResult(const FunctionSubsequence *func, int flags, DynamicContext *context);

    Item::Ptr next(DynamicContext *context);
    std::string asString(DynamicContext *context, int indent) const;
  private:
    int _flags;
    const FunctionSubsequence *_func;
    Numeric::Ptr _length;
    Numeric::Ptr _one;
    Numeric::Ptr _i;
    Result _source;
  };
};

#endif // _FUNCTIONSUBSEQUENCE_HPP




