/*
 * Copyright (c) 2001-2007
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2007
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

#ifndef _NUMERICFUNCTION_HPP
#define _NUMERICFUNCTION_HPP

#include <xqilla/ast/ConstantFoldingFunction.hpp>

/** Virtual interface class for functions */
class XQILLA_API NumericFunction : public ConstantFoldingFunction
{
public:

  /// constructor, checks for the correct number of arguments.
  NumericFunction(const XMLCh* name, unsigned int argsFrom, unsigned int argsTo, const char* paramDecl, const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);

  virtual ASTNode* staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);

protected:
  Numeric::Ptr getNumericParam(unsigned int number, DynamicContext *context, int flags=0) const;
};
#endif // _NUMERICFUNCTION_HPP
