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

#ifndef _DEBUGHOOKDECORATOR_HPP
#define _DEBUGHOOKDECORATOR_HPP

#include <xqilla/optimizer/ASTVisitor.hpp>

class XQILLA_API DebugHookDecorator : public ASTVisitor
{
public:
	DebugHookDecorator(DynamicContext *context, Optimizer *parent = 0);

protected:
  virtual ASTNode *optimize(ASTNode *item);
  virtual TupleNode *optimizeTupleNode(TupleNode *item);

  XPath2MemoryManager *mm_;
};

#endif
