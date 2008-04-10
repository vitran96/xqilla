/*
 * Copyright (c) 2001-2008
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2008
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

#include <xqilla/simple-api/XQilla.hpp>
#include <xqilla/simple-api/XQQuery.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/ItemFactory.hpp>
#include <xqilla/exceptions/XQException.hpp>
#include <xqilla/utils/XStr.hpp>
#include <xqilla/utils/UTF8Str.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/ast/LocationInfo.hpp>
#include <xqilla/context/MessageListener.hpp>
#include <xqilla/events/EventSerializer.hpp>
#include <xqilla/events/NSFixupFilter.hpp>
#include <xqilla/xerces/XercesConfiguration.hpp>
#include <xqilla/fastxdm/FastXDMConfiguration.hpp>
#include <xqilla/context/ModuleResolver.hpp>
#include <xqilla/context/URIResolver.hpp>
