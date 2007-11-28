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

/*

  ContextException

*/

#ifndef _CONTEXTEXCEPTION_HPP
#define _CONTEXTEXCEPTION_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/exceptions/XQException.hpp>
#include <xqilla/utils/XStr.hpp>

/** exception class for DSLPath parser */

class XQILLA_API ContextException : public XQException
{
public:

  ContextException(const XMLCh *functionName, const XMLCh *reason, const LocationInfo *info, const char *file, int line)
    : XQException(X("ContextException"), functionName, reason, info, file, line) {};
};

#endif // _CONTEXTEXCEPTION_HPP

