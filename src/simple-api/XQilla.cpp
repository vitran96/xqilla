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
// XQEvaluator.cpp: implementation of the XQEvaluator class.
//////////////////////////////////////////////////////////////////////

#include <xqilla/simple-api/XQilla.hpp>
#include <xqilla/simple-api/XQQuery.hpp>
#include <xqilla/context/XQDebugCallback.hpp>
#include <xqilla/exceptions/ContextException.hpp>
#include <xqilla/context/impl/XQContextImpl.hpp>
#include <xqilla/utils/XQillaPlatformUtils.hpp>
#include "../lexer/Scanner.hpp"

#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/framework/XMLRecognizer.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/util/Janitor.hpp>

#if defined(XERCES_HAS_CPP_NAMESPACE)
XERCES_CPP_NAMESPACE_USE
#endif

XQilla::XQilla(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *memMgr)
{
  XQillaPlatformUtils::initialize(memMgr);
}

XQilla::~XQilla()
{
  XQillaPlatformUtils::terminate();
}

XQQuery* XQilla::parseXQuery(const XMLCh* inputQuery, DynamicContext* context/*=0*/,
                             const XMLCh* queryFile/*=NULL*/, unsigned int flags/*=0*/,
                             MemoryManager *memMgr)
{
  bool contextOwned = (flags & NO_ADOPT_CONTEXT) == 0;
  if(context == 0) {
    contextOwned = true;
    context = createContext();
  }

  XQueryParserArgs args;
  try {
    CXQueryScanner scanner(context->getMemoryManager(), inputQuery);

    args._context=context;
    args._scanner=&scanner;
    args._query=new (memMgr) XQQuery(inputQuery, context, contextOwned, memMgr);
    args._query->setFile(queryFile);

    XQuery::yyparse(&args);

    // Perform static resolution, if requested
    if((flags & NO_STATIC_RESOLUTION) == 0) {
      args._query->staticResolution(context);
    }
  }
  catch(XQException& e) {
    // parsing errors and staticResolution don't invoke ReportFirstError, so do it here
    if(context->getDebugCallback() && context->isDebuggingEnabled()) 
      context->getDebugCallback()->ReportFirstError(context, e.getError(), queryFile, e.m_nLine);
    throw XQException(e.getError(),e.m_szFile?e.m_szFile:queryFile,e.m_nLine,e.m_nColumn);
  }
  catch(DSLException& e) {
    if(context->getDebugCallback() && context->isDebuggingEnabled()) 
      context->getDebugCallback()->ReportFirstError(context, e.getError(), queryFile, 0);
    throw XQException(e.getError(),queryFile,0,0);
  }

  return args._query;
}

XQQuery* XQilla::parseXQuery(const InputSource& querySrc, DynamicContext* context/*=0*/,
                             unsigned int flags/*=0*/, MemoryManager *memMgr)
{
  XMLBuffer moduleText;
  if(!readQuery(querySrc, memMgr, moduleText)) {
    DSLthrow(ContextException,X("XQilla::parse"), X("Exception reading query content"));
  }

  return parseXQuery(moduleText.getRawBuffer(), context, querySrc.getSystemId(), flags, memMgr);
}

XQQuery* XQilla::parseXQueryFromURI(const XMLCh* queryFile, DynamicContext* context/*=0*/,
                                    unsigned int flags/*=0*/, MemoryManager *memMgr)
{
  XMLBuffer moduleText;
  if(!readQuery(queryFile, memMgr, moduleText)) {
    DSLthrow(ContextException,X("XQilla::parseFromUri"), X("Exception reading query content"));
  }

  return parseXQuery(moduleText.getRawBuffer(), context, queryFile, flags, memMgr);
}

DynamicContext *XQilla::createContext(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *memMgr)
{
  return new (memMgr) XQContextImpl(memMgr, 0, 0);
}

#ifdef _DEBUG
  #define BUFFER_SIZE 128
#else
  #define BUFFER_SIZE 8192
#endif

bool XQilla::readQuery(const XMLCh* queryFile, MemoryManager* memMgr, XMLBuffer& queryText)
{
    Janitor<InputSource> srcToFill(NULL);
    try {
      XMLURL urlTmp(queryFile);
      if (urlTmp.isRelative())
        throw MalformedURLException(__FILE__, __LINE__, XMLExcepts::URL_NoProtocolPresent);
      srcToFill.reset(new (memMgr) URLInputSource(urlTmp));
    }
    catch(const MalformedURLException&) {
      srcToFill.reset(new (memMgr) LocalFileInputSource(queryFile));
    }
    return readQuery(*srcToFill.get(), memMgr, queryText);
}

bool XQilla::readQuery(const InputSource& querySrc, MemoryManager* memMgr, XMLBuffer& queryText)
{
	try {
    BinInputStream* stream=querySrc.makeStream();
    if(stream==NULL)
      return false;
    Janitor<BinInputStream> janStream(stream);
    XMLByte buffer[BUFFER_SIZE];
    unsigned int nRead=stream->readBytes(buffer,BUFFER_SIZE);
    Janitor<XMLTranscoder> transcoder(NULL);
    XMLTransService::Codes retCode;
    if(querySrc.getEncoding()==NULL) {
      XMLRecognizer::Encodings encoding=XMLRecognizer::basicEncodingProbe(buffer,BUFFER_SIZE);
      transcoder.reset(XMLPlatformUtils::fgTransService->makeNewTranscoderFor(encoding, retCode, BUFFER_SIZE, memMgr));
    }
    else {
      transcoder.reset(XMLPlatformUtils::fgTransService->makeNewTranscoderFor(querySrc.getEncoding(), retCode, BUFFER_SIZE, memMgr));
    }
    XMLCh tempBuff[BUFFER_SIZE];
    unsigned char charSizes[BUFFER_SIZE];
    unsigned int bytesEaten=0, nOffset=0;
    unsigned int nCount=transcoder->transcodeFrom(buffer,nRead,tempBuff,BUFFER_SIZE,bytesEaten,charSizes);
    queryText.set(tempBuff,nCount);
    if(bytesEaten<nRead){
      nOffset=nRead-bytesEaten;
      memmove(buffer, buffer+bytesEaten, nRead-bytesEaten);
    }

    while((nRead=stream->readBytes(buffer+nOffset,BUFFER_SIZE-nOffset))>0) {
      nCount=transcoder->transcodeFrom(buffer,nRead,tempBuff,BUFFER_SIZE,bytesEaten,charSizes);
      queryText.append(tempBuff,nCount);
      if(bytesEaten<nRead) {
        nOffset=nRead-bytesEaten;
        memmove(buffer, buffer+bytesEaten, nRead-bytesEaten);
      }
    }
	}
	catch(...) {
    return false;
	}
  return true;
}