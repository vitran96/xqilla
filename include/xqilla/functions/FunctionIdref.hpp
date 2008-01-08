/*
 * Copyright (c) 2001-2008
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2008
 *     Oracle. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Id$
 */

#ifndef _FUNCTIONIDREF_HPP
#define _FUNCTIONIDREF_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQFunction.hpp>
#include <xqilla/runtime/Sequence.hpp>

#include <vector>

/** 
 * Function idref
 * 
 * fn:idref(string* $srcval) => element*
 *
 */
class XQILLA_API FunctionIdref : public XQFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  /**
   * Constructor
   */
  FunctionIdref(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  virtual ASTNode* staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);

  /** 
   * Returns the sequence of elements nodes having either an IDREF attribute 
   * whose value matches the value of one of the items in the value of $srcval 
   * or an IDREFS attribute whose value contains an IDREF value that matches 
   * the value of one of the items in the value of $srcval. 
   *
   * This function allows reverse navigation from IDs to IDREFs.
   */
  Sequence createSequence(DynamicContext* context, int flags=0) const;
};

#endif // _FUNCTIONIDREF_HPP

