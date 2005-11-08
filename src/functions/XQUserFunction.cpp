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

//////////////////////////////////////////////////////////////////////
// XQUserFunction.cpp: implementation of the XQUserFunction class.
//////////////////////////////////////////////////////////////////////

#include <sstream>

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XPath2TypeMatchException.hpp>
#include <xqilla/ast/XQSequence.hpp>
#include <xqilla/context/VariableStore.hpp>
#include <xqilla/context/VariableTypeStore.hpp>
#include <xqilla/utils/XPath2NSUtils.hpp>
#include <xqilla/context/DynamicContext.hpp>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/XMLBuffer.hpp>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 /* http://www.w3.org/2005/04/xquery-local-functions */
const XMLCh XQUserFunction::XMLChXQueryLocalFunctionsURI[] =
{
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_h, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, XERCES_CPP_NAMESPACE_QUALIFIER chColon, XERCES_CPP_NAMESPACE_QUALIFIER chForwardSlash,
    XERCES_CPP_NAMESPACE_QUALIFIER chForwardSlash, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_w, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_w,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_w, XERCES_CPP_NAMESPACE_QUALIFIER chPeriod, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_w,
    XERCES_CPP_NAMESPACE_QUALIFIER chDigit_3, XERCES_CPP_NAMESPACE_QUALIFIER chPeriod, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_g, XERCES_CPP_NAMESPACE_QUALIFIER chForwardSlash,
    XERCES_CPP_NAMESPACE_QUALIFIER chDigit_2, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_0, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_0,
    XERCES_CPP_NAMESPACE_QUALIFIER chDigit_5, XERCES_CPP_NAMESPACE_QUALIFIER chForwardSlash, XERCES_CPP_NAMESPACE_QUALIFIER chDigit_0,
    XERCES_CPP_NAMESPACE_QUALIFIER chDigit_4, XERCES_CPP_NAMESPACE_QUALIFIER chForwardSlash, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_x,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_q, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_y, XERCES_CPP_NAMESPACE_QUALIFIER chDash, 
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_l, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_l, XERCES_CPP_NAMESPACE_QUALIFIER chDash, 
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_f, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i,
    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s,
    XERCES_CPP_NAMESPACE_QUALIFIER chNull
};

XQUserFunction::XQUserFunction(const XMLCh* fnName, VectorOfFunctionParameters* params, ASTNode* body, SequenceType* returnValue, XPath2MemoryManager* memMgr)
	: m_body(body),
    m_szPrefix(NULL),
    m_szName(NULL),
    m_szSignature(NULL),
    m_szFullName(fnName),
    m_szURI(NULL),
    m_pMemMgr(memMgr),
    m_bStaticallyResolved(false)
{
  int nColon=XERCES_CPP_NAMESPACE_QUALIFIER XMLString::indexOf(fnName,':');
  if(nColon==-1)
    DSLthrow(FunctionException,X("User-defined Function"), X("The name for a user defined function must have a namespace prefix [err:XQ0045]"));

  XMLCh* tempPrefix = new XMLCh[nColon + 1];
  XERCES_CPP_NAMESPACE_QUALIFIER XMLString::subString(tempPrefix, fnName, 0, nColon);
  tempPrefix[nColon] = 0;
  m_szPrefix = memMgr->getPooledString(tempPrefix);
  delete [] tempPrefix;

  m_szName=memMgr->getPooledString(fnName+nColon+1);
  m_pReturnPattern=returnValue;
  m_pParams=params;
}

const XMLCh* XQUserFunction::getFullName() const
{
  return m_szFullName;
}

const XMLCh* XQUserFunction::getName() const
{
  return m_szName;
}

const XMLCh *XQUserFunction::getURI() const
{
  return m_szURI;
}

unsigned int XQUserFunction::getMinArgs() const
{
  return m_pParams==NULL?0:m_pParams->size();
}

unsigned int XQUserFunction::getMaxArgs() const
{
  return m_pParams==NULL?0:m_pParams->size();
}

const XQUserFunction::VectorOfFunctionParameters* XQUserFunction::getParams() const
{
  return m_pParams;
}

const SequenceType* XQUserFunction::getReturnValue() const
{
  return m_pReturnPattern;
}

void XQUserFunction::setURI(const XMLCh* uri)
{
  m_szURI=uri;
}

const XMLCh *XQUserFunction::getPrefix() const
{
  return m_szPrefix;
}

bool XQUserFunction::isExternal() const
{
  return m_body==NULL;
}

void XQUserFunction::setFunctionBody(ASTNode* value)
{
  m_body=value;
}

const ASTNode *XQUserFunction::getFunctionBody() const
{
  return m_body;
}

ASTNode* XQUserFunction::createInstance(const VectorOfASTNodes &args, XPath2MemoryManager* expr) const
{
  XQFunctionEvaluator* fnInstance=new (expr) XQFunctionEvaluator(this, args, expr);
  fnInstance->setSignature(m_szSignature);
  return fnInstance;
}

void XQUserFunction::staticResolution(StaticContext *context)
{
  if(m_bStaticallyResolved)
      return;
  m_bStaticallyResolved=true;
  // define the new variables in a new scope and assign them the proper values
  VariableTypeStore* varStore=context->getVariableTypeStore();
  varStore->addLocalScope();

  // Resolve the parameter names, and declare them
  if(m_pParams) {
    for (VectorOfFunctionParameters::iterator it = m_pParams->begin(); it != m_pParams->end (); ++it) {
      (*it)->_uri = context->getUriBoundToPrefix(XPath2NSUtils::getPrefix((*it)->_qname, context->getMemoryManager()));
      (*it)->_name = XPath2NSUtils::getLocalName((*it)->_qname);
      (*it)->m_pType->getItemType()->getStaticType((*it)->_src.getStaticType(), context);
      varStore->declareVar((*it)->_uri, (*it)->_name, (*it)->_src);
    }
  }

  StaticResolutionContext m_src(context->getMemoryManager());
  if(m_body!=NULL) {
    m_body = m_body->staticResolution(context);
    m_src.add(m_body->getStaticResolutionContext());
  }

  // Remove the parameter variables from the stored StaticResolutionContext
  if(m_pParams) {
    for(VectorOfFunctionParameters::iterator it = m_pParams->begin(); it != m_pParams->end (); ++it) {
      if(!m_src.removeVariable((*it)->_uri, (*it)->_name)) {
        // The parameter isn't used, so set it to null, so that we don't bother to evaluate it
        (*it)->_qname = 0;
      }
    }
  }

  varStore->removeScope();
}

void XQUserFunction::setSignature(const XMLCh* signature)
{
  m_szSignature=m_pMemMgr->getPooledString(signature);
}

const XMLCh* XQUserFunction::getSignature()
{
  return m_szSignature;
}

///////////////////////////////////////////////////////////////
// XQUserFunction::XQFunctionEvaluator

typedef pair<XQUserFunction::XQFunctionParameter*, Sequence> ParamBinding;
typedef vector<ParamBinding> VectorOfParamBindings;

XQUserFunction::XQFunctionEvaluator::XQFunctionEvaluator(const XQUserFunction* funcDef, const VectorOfASTNodes& args, XPath2MemoryManager* expr) 
  : XQFunction(funcDef->getName(),0,UNLIMITED,"",args,expr)
{
  setType(ASTNode::USER_FUNCTION);
  m_pFuncDef = funcDef;
  _fURI = funcDef->getURI();
}

Result XQUserFunction::XQFunctionEvaluator::createResult(DynamicContext* context, int flags) const
{
  Result result(new FunctionEvaluatorResult(this, flags, context));
  if(m_pFuncDef->m_pReturnPattern)
    return result.matches(m_pFuncDef->m_pReturnPattern, context);
  return result;
}

ASTNode* XQUserFunction::XQFunctionEvaluator::staticResolution(StaticContext* context)
{
  unsigned int nDefinedArgs = m_pFuncDef->m_pParams ? m_pFuncDef->m_pParams->size() : 0;
  if(_args.size() != nDefinedArgs) {
    XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer buf;
    buf.set(X("Function '"));
    buf.append(m_pFuncDef->m_szName);
    buf.append(X("' has been called with a number of arguments that doesn't match the function signature"));
    DSLthrow(FunctionException,X("User-defined Function"), buf.getRawBuffer());
  }

  _src.getStaticType() = m_pFuncDef->m_body->getStaticResolutionContext().getStaticType();
  _src.add(m_pFuncDef->m_body->getStaticResolutionContext());

  if(nDefinedArgs > 0) {
    VectorOfASTNodes::iterator argIt = _args.begin();
    for(VectorOfFunctionParameters::iterator defIt = m_pFuncDef->m_pParams->begin();
        defIt != m_pFuncDef->m_pParams->end() && argIt != _args.end(); ++defIt, ++argIt) {
      if((*defIt)->_qname || context->isDebuggingEnabled()) {
        *argIt = (*argIt)->staticResolution(context);
	_src.add((*argIt)->getStaticResolutionContext());
      }
      else {
        // Don't resolve the argument, since it isn't used by the function body
      }
    }
  }

  if(_src.isUsed()) {
    return resolvePredicates(context);
  }
  else {
    // as we are going to evaluate the user-defined function, be sure it has been statically resolved
    const_cast<XQUserFunction*>(m_pFuncDef)->staticResolution(context);
    return constantFold(context);
  }
}

XQUserFunction::XQFunctionEvaluator::FunctionEvaluatorResult::FunctionEvaluatorResult(const XQFunctionEvaluator *di, int flags, DynamicContext *context)
  : ResultImpl(context),
    _flags(flags),
    _di(di),
    _scope(0),
    _result(0),
    _scopeRemoved(false)
{
}

Item::Ptr XQUserFunction::XQFunctionEvaluator::FunctionEvaluatorResult::next(DynamicContext *context)
{
  VariableStore* varStore=context->getVariableStore();
  Scope<Sequence> *oldScope = varStore->getScopeState();

  if(_result.isNull()) {
    int nDefinedArgs = _di->getFunctionDefinition()->getParams() ? _di->getFunctionDefinition()->getParams()->size() : 0;

    VectorOfParamBindings varValues;
    if(nDefinedArgs > 0) {
      // the variables should be evaluated in the calling context
      // (before the VariableStore::addLocalScope call: after this call, the variables that can be seen are only the local ones)
      int index = 0;
      for(VectorOfFunctionParameters::const_iterator it = _di->getFunctionDefinition()->getParams()->begin();
          it != _di->getFunctionDefinition()->getParams()->end(); ++it, ++index) {
        if((*it)->_qname || context->isDebuggingEnabled()) {
          Sequence argValue(_di->getArguments()[index]->collapseTree(context)
                            .convertFunctionArg((*it)->m_pType, _di->getArguments()[index]->getStaticResolutionContext().getStaticType(), context)
                            .toSequence(context));
          varValues.push_back(ParamBinding(*it, argValue));
        }
        else {
          // Skip evaluation of the parameter, since it isn't used, and debugging isn't enabled
        }
      }
    }
    // define the new variables in a new scope and assign them the proper values
    varStore->addLocalScope();
    for(VectorOfParamBindings::iterator it2 = varValues.begin(); it2 != varValues.end(); ++it2) {
      varStore->declareVar(it2->first->_uri, it2->first->_name, it2->second, context);
    }

    if(_di->getFunctionDefinition()->getFunctionBody() == NULL) {
      XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer buf;
      buf.set(X("External function '"));
      buf.append(_di->getFunctionDefinition()->getName());
      buf.append(X("' has not been bound to an implementation"));
      DSLthrow(FunctionException,X("User-defined Function"), buf.getRawBuffer());
    }

    _result = _di->getFunctionDefinition()->getFunctionBody()->collapseTree(context, _flags & ~(ASTNode::RETURN_ONE|ASTNode::RETURN_TWO));
  }
  else if(_scope != 0) {
    varStore->setScopeState(_scope);
  }

  const Item::Ptr item = _result.next(context);

  if(!_scopeRemoved) {
    if(item == NULLRCP) {
      varStore->removeScope();
      _scope = 0;
    }
    else {
      _scope = varStore->getScopeState();
      varStore->setScopeState(oldScope);
    }
  }

  return item;
}

std::string XQUserFunction::XQFunctionEvaluator::FunctionEvaluatorResult::asString(DynamicContext *context, int indent) const
{
  std::ostringstream oss;
  std::string in(getIndent(indent));

  oss << in << "<functionevaluator/>" << std::endl;

  return oss.str();
}