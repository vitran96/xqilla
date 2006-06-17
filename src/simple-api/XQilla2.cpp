/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

//////////////////////////////////////////////////////////////////////
// XQEvaluator.cpp: implementation of the XQEvaluator class.
//////////////////////////////////////////////////////////////////////

#include <xqilla/simple-api/XQilla.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/simple-api/XQQuery.hpp>
#include <xqilla/context/XQDebugCallback.hpp>
#include <xqilla/exceptions/ContextException.hpp>
#include <xqilla/exceptions/XQException.hpp>
#include "../lexer/XPathScanner.hpp"

#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/Janitor.hpp>

#if defined(XERCES_HAS_CPP_NAMESPACE)
XERCES_CPP_NAMESPACE_USE
#endif

XQQuery* XQilla::parseXPath2(const XMLCh* inputQuery, DynamicContext* context/*=0*/,
                             const XMLCh* queryFile/*=NULL*/, unsigned int flags/*=0*/,
                             MemoryManager *memMgr)
{
  bool contextOwned = (flags & NO_ADOPT_CONTEXT) == 0;
  if(context == 0) {
    contextOwned = true;
    context = createContext();
  }

  XERCES_CPP_NAMESPACE_QUALIFIER Janitor<XQQuery> query(new (memMgr) XQQuery(inputQuery, context, contextOwned, memMgr));

  try {
    CXPathScanner scanner(context->getMemoryManager(), inputQuery);

    XPath2ParserArgs args;
    args._memMgr=context->getMemoryManager();
    args._scanner=&scanner;
    args._query=query.get();
    args._query->setFile(queryFile);

    XPath2::yyparse(&args);

    // Perform static resolution, if requested
    if((flags & NO_STATIC_RESOLUTION) == 0) {
      query->staticResolution(context);
    }
  }
  catch(XQException& e) {
    // parsing errors and staticResolution don't invoke ReportFirstError, so do it here
    if(context->getDebugCallback() && context->isDebuggingEnabled()) 
      context->getDebugCallback()->ReportFirstError(context, e.getError(), queryFile, e.getXQueryLine());
    throw e;
  }

  return query.release();
}
