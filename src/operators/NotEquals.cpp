/*
 * Copyright (c) 2001, 2008,
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004, 2010,
 *     Oracle and/or its affiliates. All rights reserved.
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
 */

#include "../config/xqilla_config.h"
#include <xqilla/operators/NotEquals.hpp>
#include <xqilla/operators/Equals.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/context/impl/CodepointCollation.hpp>
#include <xqilla/context/DynamicContext.hpp>

/*static*/ const XMLCh NotEquals::name[]={ XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull };

NotEquals::NotEquals(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ComparisonOperator(name, args, memMgr)
{
}

/*static*/ bool NotEquals::not_equals(const AnyAtomicType::Ptr &arg1, const AnyAtomicType::Ptr &arg2, Collation* collation, DynamicContext* context, const LocationInfo *info)
{
  // define "ne" as "!eq"
  return !Equals::equals(arg1,arg2,collation,context, info);
}

bool NotEquals::execute(const AnyAtomicType::Ptr &atom1, const AnyAtomicType::Ptr &atom2, DynamicContext *context) const
{
  return not_equals(atom1, atom2, context->getDefaultCollation(this), context, this);
}












