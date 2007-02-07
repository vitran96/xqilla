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
  fn:encode-for-uri($uri-part as xs:string?) as xs:string
*/

#ifndef _FUNCTIONENCODEFORURI_HPP
#define _FUNCTIONENCODEFORURI_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>

class XQILLA_API FunctionEncodeForUri : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionEncodeForUri(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);

  Sequence createSequence(DynamicContext* context, int flags=0) const;
};

#endif // _FUNCTIONENCODEFORURI_HPP



