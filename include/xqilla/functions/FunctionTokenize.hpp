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

#ifndef _FUNCTIONTOKENIZE_HPP
#define _FUNCTIONTOKENIZE_HPP

#include <xqilla/ast/ConstantFoldingFunction.hpp>

/** 
 * Breaks the $input string into a sequence of strings, 
 * treating any substring that matches $pattern as a separator. 
 * The separators themselves are not returned. 
 *
 * tokenize(string? $input, string $pattern) => string*
 * tokenize(string? $input, string $pattern, string $flags) => string*
 */
class XQILLA_API FunctionTokenize : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  /**
   * Constructor.
   */
  FunctionTokenize(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  /**
   * Returns $input broken into a sequence of strings 
   * using matches to $pattern as a separator. 
   */
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;

};

#endif // _FUNCTIONTOKENIZE_HPP
