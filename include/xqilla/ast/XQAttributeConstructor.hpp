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

#ifndef XQATTRIBUTECONSTRUCTOR_HPP
#define XQATTRIBUTECONSTRUCTOR_HPP

#include <xqilla/ast/XQDOMConstructor.hpp>

class XQILLA_API XQAttributeConstructor : public XQDOMConstructor
{
public:
  XQAttributeConstructor(ASTNode* name, VectorOfASTNodes* children, XPath2MemoryManager* mm);

  virtual void generateEvents(EventHandler *events, DynamicContext *context,
                              bool preserveNS, bool preserveType) const;
  virtual ASTNode* staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);

  virtual const XMLCh* getNodeType() const;
  virtual const ASTNode *getName() const;
  virtual const VectorOfASTNodes *getChildren() const;

  virtual void setName(ASTNode *name);

protected:
  ASTNode* m_name;
  VectorOfASTNodes* m_children;
};

#endif
