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

/*
  Factory base class
*/

#ifndef _FUNCFACTORY_HPP
#define _FUNCFACTORY_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ASTNode.hpp>

class XQILLA_API FuncFactory
{
public:
  FuncFactory();
  virtual ~FuncFactory();

  ///Create instance of a function, using FuncFactoryTemplate to determine type
  virtual ASTNode *createInstance(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr) const = 0;

  virtual const XMLCh *getName() const = 0;
  virtual const XMLCh *getURI() const = 0;
  virtual const XMLCh *getURINameHash() const = 0;
  virtual size_t getMinArgs() const = 0;
  virtual size_t getMaxArgs() const = 0;
};

#endif

