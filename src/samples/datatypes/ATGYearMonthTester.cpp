/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 * Copyright (c) 2004-2006
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

#include "ATGYearMonthTester.hpp"
#include <xqilla/utils/XStr.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/ItemFactory.hpp>

#include <xqilla/items/ATGYearMonthOrDerived.hpp>
#include <xqilla/items/Timezone.hpp>

ATGYearMonthTester::ATGYearMonthTester() : DatatypeTester("ATGYearMonthOrDerived") {
}

void ATGYearMonthTester::run(const DynamicContext* context) {
  // test 1 -- equality
  const ATGYearMonthOrDerived::Ptr gYearMonth1 = this->createGYearMonth(X("2003-07Z"), context);
  const ATGYearMonthOrDerived::Ptr gYearMonth2 = this->createGYearMonth(X("2003-07Z"), context);

  assertObjectEquals(gYearMonth1, gYearMonth1, context);
  assertObjectEquals(gYearMonth1, gYearMonth2, context);

  assertEquals(gYearMonth1->asString(context), X("2003-07Z"));
  assertEquals(gYearMonth1->asString(context), gYearMonth2->asString(context));
  
  // test 2 -- inequality
  const ATGYearMonthOrDerived::Ptr gYearMonth3 = this->createGYearMonth(X("1981-12"), context);
  const ATGYearMonthOrDerived::Ptr gYearMonth4 = this->createGYearMonth(X("-1981-12"), context);
  assertCondition(!gYearMonth1->equals(gYearMonth3, context));
  assertCondition(((const ATGYearMonthOrDerived*)gYearMonth1)->greaterThan(gYearMonth3, context));
  assertCondition(((const ATGYearMonthOrDerived*)gYearMonth4)->lessThan(gYearMonth3, context));
  assertEquals(gYearMonth4->asString(context), X("-1981-12"));

  // test 3 -- timezones
  assertCondition(((const ATGYearMonthOrDerived*)gYearMonth1)->hasTimezone());
  assertCondition(!((const ATGYearMonthOrDerived*)gYearMonth3)->hasTimezone());

  const ATGYearMonthOrDerived::Ptr gYearMonth5 = ((const ATGYearMonthOrDerived*)gYearMonth3)->setTimezone(new Timezone(-8, 0), context);
  assertCondition(((const ATGYearMonthOrDerived*)gYearMonth5)->hasTimezone());
  assertEquals(gYearMonth5->asString(context), X("1981-12-08:00"));
  
  // test 4 -- typeURI and typeName
  assertEquals(gYearMonth5->getTypeName(), XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_YEARMONTH);
  assertEquals(gYearMonth5->getTypeName(), gYearMonth3->getPrimitiveTypeName());
  
  assertEquals(gYearMonth5->getTypeURI(), gYearMonth3->getPrimitiveTypeURI());
  assertEquals(gYearMonth5->getTypeURI(), XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA);
  
}

const ATGYearMonthOrDerived::Ptr ATGYearMonthTester::createGYearMonth(const XMLCh* value,
                                                   const DynamicContext* context) {
  return context->getItemFactory()->createGYearMonthOrDerived(
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA,
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_YEARMONTH,
      value, context);
}
