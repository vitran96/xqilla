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

#include "../config/pathan_config.h"
#include <xqilla/dom-api/impl/PathanExpressionImpl.hpp>
#include <xqilla/simple-api/PathanEngine.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/items/Item.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/dom-api/PathanExpression.hpp>
#include <xqilla/dom-api/XPath2Result.hpp>
#include <xqilla/ast/DataItem.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>

#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/ContextException.hpp>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/RuntimeException.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/util/XercesDefs.hpp>

PathanExpressionImpl::PathanExpressionImpl(const XMLCh *expression,
                                           const XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* documentRoot,
                                           XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr,
                                           const XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathNSResolver *nsr,
                                           XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool *xmlGP)
	: _createdWith(memMgr),
    _memMgr(memMgr),
    _docRoot(documentRoot),
    _staticContextOwned(true)
{
  _staticContext = PathanEngine::createContext(xmlGP, &_memMgr);
  _staticContext->setNSResolver(nsr);
  _compiledExpression = PathanEngine::createDataItem(expression, _staticContext, &_memMgr, true);
}

PathanExpressionImpl::PathanExpressionImpl(const XMLCh *expression, DynamicContext *context,
                                           XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr)
	: _createdWith(memMgr),
    _memMgr(memMgr),
    _docRoot(0),
    _staticContextOwned(false),
    _staticContext(context)
{
  _compiledExpression = PathanEngine::createDataItem(expression, _staticContext, &_memMgr, true);
}

PathanExpressionImpl::~PathanExpressionImpl() 
{
  if(_staticContextOwned) _staticContext->release();
}//destructor

void PathanExpressionImpl::release()
{
  this->~PathanExpressionImpl();
  _createdWith->deallocate(this);
}

// weak version -  must create a context from scratch
void* PathanExpressionImpl::evaluate(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* contextNode,
                                     unsigned short type,
                                     void*) const
  throw (XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathException, XERCES_CPP_NAMESPACE_QUALIFIER DOMException)
{
  return new (_createdWith) XPath2Result((XPath2Result::ResultType)type, _compiledExpression,
                                         contextNode, _staticContext, _createdWith);
}

// strong version, use given context
XPath2Result* PathanExpressionImpl::evaluate(DynamicContext* context, unsigned short type) const
	throw (XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathException, XERCES_CPP_NAMESPACE_QUALIFIER DOMException)
{
  return new (_createdWith) XPath2Result((XPath2Result::ResultType)type, _compiledExpression,
                                         context, _createdWith);
}

DynamicContext *PathanExpressionImpl::createContext(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *mm) const
{
  if(mm == 0) {
    return 0;
  }
  return _staticContext->createDynamicContext(mm);
}
