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


#include "../../config/xqilla_config.h"
#include "XQillaXMLGrammarPoolImpl.hpp"
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/util/RuntimeException.hpp>

XQillaXMLGrammarPoolImpl::XQillaXMLGrammarPoolImpl(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* const memMgr) : XMLGrammarPoolImpl(memMgr)
{};

bool XQillaXMLGrammarPoolImpl::cacheGrammar(XERCES_CPP_NAMESPACE_QUALIFIER Grammar* const  gramToCache)
{
  try {
    return XMLGrammarPoolImpl::cacheGrammar(gramToCache);
  }
  catch(XERCES_CPP_NAMESPACE_QUALIFIER RuntimeException& e) {
    //do nothing - return false because the grammar was not accepted
    return false;
  }
  return false;
}