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

//////////////////////////////////////////////////////////////////////
// XQGlobalVariable.cpp: implementation of the XQGlobalVariable class.
//////////////////////////////////////////////////////////////////////

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQGlobalVariable.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/context/VariableStore.hpp>
#include <xqilla/context/VariableTypeStore.hpp>
#include <xqilla/utils/XPath2NSUtils.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/IllegalArgumentException.hpp>
#include <xqilla/exceptions/XPath2TypeMatchException.hpp>
#include <xercesc/framework/XMLBuffer.hpp>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XQGlobalVariable::XQGlobalVariable(const XMLCh* varQName, SequenceType* seqType, ASTNode* value, XPath2MemoryManager* expr)
  : ASTNodeImpl(expr),
    m_szURI(0),
    m_szLocalName(0),
    m_Type(seqType),
    m_Value(value)
{
  m_szQName=expr->getPooledString(varQName);
  setType(ASTNode::VARIABLE_DEFINITION);
}

Sequence XQGlobalVariable::collapseTreeInternal(DynamicContext* context, int flags) const
{
  VariableStore* varStore = context->getVariableStore();
  Sequence variableValue(context->getMemoryManager());
  if(m_Value==NULL) {
    // It's an external declaration, so check the user has set the value in the variable store
    std::pair<bool, Sequence> value=varStore->getGlobalVar(m_szURI, m_szLocalName, context);
    if(!value.first) {
      XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer errMsg;
      errMsg.set(X("A value for the external variable '"));
      errMsg.append(m_szQName);
      errMsg.append(X("' has not been provided"));
      XQThrow(IllegalArgumentException,X("XQGlobalVariable::collapseTreeInternal"),errMsg.getRawBuffer());
    }
    variableValue=value.second;
  }
  else {
    variableValue=m_Value->collapseTree(context).toSequence(context);
    varStore->setGlobalVar(m_szURI, m_szLocalName, variableValue, context);
  }
  if(m_Type!=NULL)
  {
    Result matchesRes=m_Type->matches(variableValue, context);
    try {
      while(matchesRes.next(context) != NULLRCP) {}
    }
    catch(const XPath2TypeMatchException &ex) {
      XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer errMsg;
      errMsg.set(X("The value for the global variable '"));
      errMsg.append(m_szQName);
      errMsg.append(X("' does not match the declared type: "));
      errMsg.append(ex.getError());
      XQThrow(XPath2TypeMatchException,X("XQGlobalVariable::collapseTreeInternal"),errMsg.getRawBuffer());
    }
  }

  return Sequence(context->getMemoryManager());
}

ASTNode* XQGlobalVariable::staticResolution(StaticContext* context)
{
  // variables with no prefix are in no namespace
  const XMLCh* prefix=XPath2NSUtils::getPrefix(m_szQName, context->getMemoryManager());
  if(prefix && *prefix)
    m_szURI = context->getUriBoundToPrefix(prefix);
  m_szLocalName = XPath2NSUtils::getLocalName(m_szQName);
  VariableTypeStore* varStore = context->getVariableTypeStore();
  if(m_Value!=NULL) {
    m_Value = m_Value->staticResolution(context);
    _src.add(m_Value->getStaticResolutionContext());
    varStore->declareGlobalVar(m_szURI, m_szLocalName, m_Value->getStaticResolutionContext());
  }
  else {
    m_Type->getItemType()->getStaticType(_src.getStaticType(), context);
    varStore->declareGlobalVar(m_szURI, m_szLocalName, _src);
  }
  return this;
}

const XMLCh* XQGlobalVariable::getVariableName() const
{
  return m_szQName;
}

bool XQGlobalVariable::isExternal() const
{
  return (m_Value==NULL);
}

void XQGlobalVariable::setVariableExpr(ASTNode* value)
{
  m_Value=value;
}

const SequenceType *XQGlobalVariable::getSequenceType() const
{
  return m_Type;
}

const ASTNode *XQGlobalVariable::getVariableExpr() const
{
  return m_Value;
}

const XMLCh *XQGlobalVariable::getVariableURI() const
{
  return m_szURI;
}

const XMLCh *XQGlobalVariable::getVariableLocalName() const
{
  return m_szLocalName;
}
