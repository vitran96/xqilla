/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Oracle. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */
#include "../config/xqilla_config.h"
#include <xqilla/functions/FunctionDoc.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XMLParseException.hpp>
#include <xqilla/ast/StaticAnalysis.hpp>
#include <xqilla/utils/XPath2Utils.hpp>

#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_USE;

const XMLCh FunctionDoc::name[] = {
  chLatin_d, chLatin_o, chLatin_c, 
  chNull 
};
const unsigned int FunctionDoc::minArgs = 1;
const unsigned int FunctionDoc::maxArgs = 1;

/**
 * fn:doc($uri as xs:string?) as document?
 **/
FunctionDoc::FunctionDoc(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "string?", args, memMgr),
    queryPathTree_(0)
{
}

ASTNode* FunctionDoc::staticResolution(StaticContext *context)
{
  return resolveArguments(context);
}

ASTNode *FunctionDoc::staticTyping(StaticContext *context)
{
  _src.clear();

  _src.setProperties(StaticAnalysis::DOCORDER | StaticAnalysis::GROUPED |
                     StaticAnalysis::PEER | StaticAnalysis::SUBTREE | StaticAnalysis::ONENODE);
  _src.getStaticType().flags = StaticType::DOCUMENT_TYPE;
  _src.availableDocumentsUsed(true);

  calculateSRCForArguments(context);

  if(_args[0]->isConstant()) {
  }
  else {
  }

  return this;
}

Sequence FunctionDoc::createSequence(DynamicContext* context, int flags) const
{
  Sequence uriArg = getParamNumber(1,context)->toSequence(context);
  
  if (uriArg.isEmpty()) {
    return Sequence(context->getMemoryManager());
  }
  
  const XMLCh *uri = uriArg.first()->asString(context);

  // on Windows, we can have URIs using \ instead of /; let's normalize them
  if(uri != 0) {
    unsigned int len = XMLString::stringLen(uri);
    AutoDeleteArray<XMLCh> newURI(new XMLCh[len + 1]);

    const XMLCh *src = uri;
    XMLCh *dst = newURI;
    while(*src != 0) {
      if(*src == '\\') *dst = '/';
      else *dst = *src;

      ++src; ++dst;
    }
    *dst = 0;

    uri = context->getMemoryManager()->getPooledString(newURI);
  }

  if(!XPath2Utils::isValidURI(uri, context->getMemoryManager()))
    XQThrow(FunctionException, X("FunctionDoc::createSequence"), X("Invalid argument to fn:doc function [err:FODC0005]"));

  QPNVector projection;
  projection.push_back(queryPathTree_);
  return context->resolveDocument(uri, this, queryPathTree_ ? &projection : 0);
}
