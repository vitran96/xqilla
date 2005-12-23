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

#include <xqilla/dom-api/XQillaExpression.hpp>
#include <xqilla/dom-api/XPath2Result.hpp>
#include <xqilla/dom-api/XQillaNSResolver.hpp>
#include <xqilla/exceptions/XQillaException.hpp>
#include <xqilla/utils/XQillaPlatformUtils.hpp>
#include <xqilla/utils/XStr.hpp>
#include <xqilla/utils/UTF8Str.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>