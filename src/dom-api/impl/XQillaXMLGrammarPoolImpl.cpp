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
