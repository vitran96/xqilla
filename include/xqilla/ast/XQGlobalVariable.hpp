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

#ifndef XQGLOBALVARIABLE_HPP
#define XQGLOBALVARIABLE_HPP

#include <xqilla/ast/ASTNodeImpl.hpp>

class SequenceType;

class XQILLA_API XQGlobalVariable : public LocationInfo
{
public:
  XQGlobalVariable(const XMLCh* varQName, SequenceType* seqType, ASTNode* value, XPath2MemoryManager *mm);

  void execute(DynamicContext* context) const;
  void staticResolution(StaticContext *context);
  void staticTyping(StaticContext *context);

  const XMLCh* getVariableName() const;
  bool isExternal() const;
  void setVariableExpr(ASTNode* value);

  const XMLCh *getVariableURI() const;
  const XMLCh *getVariableLocalName() const;
  const SequenceType *getSequenceType() const;
  const ASTNode *getVariableExpr() const;
  const StaticAnalysis &getStaticAnalysis() const { return _src; }

protected:
  const XMLCh* m_szQName;
  const XMLCh* m_szURI;
  const XMLCh* m_szLocalName;
  SequenceType* m_Type;
  ASTNode* m_Value;
  StaticAnalysis _src;
};

#endif
