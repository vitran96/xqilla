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

/*
 * xf:exactly-one(item* $srcval) => item
 */

#ifndef _FUNCTIONEXACTLYONE_HPP
#define _FUNCTIONEXACTLYONE_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>

class XQILLA_API FunctionExactlyOne : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionExactlyOne(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  Result createResult(DynamicContext* context, int flags=0) const;

private:
  class ExactlyOneResult : public ResultImpl
  {
  public:
    ExactlyOneResult(const FunctionExactlyOne *func, int flags);

    Item::Ptr next(DynamicContext *context);
    std::string asString(DynamicContext *context, int indent) const;
  private:
    int _flags;
    const FunctionExactlyOne *_func;
    Result _arg;
    unsigned int _argNo;
  };
};

#endif // _FUNCTIONEXACTLYONE_HPP
