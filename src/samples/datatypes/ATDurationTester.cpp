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

#include "ATDurationTester.hpp"
#include <xqilla/utils/XStr.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/IllegalArgumentException.hpp>
#include <xqilla/functions/FunctionConstructor.hpp>
#include <xqilla/items/DatatypeFactory.hpp>

#include <xqilla/items/ATDurationOrDerived.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>

ATDurationTester::ATDurationTester(XPath2MemoryManager* memMgr) : DatatypeTester(memMgr, "ATDurationOrDerived") {
}

void ATDurationTester::run(const DynamicContext* context) {
  // test 1 -- equality
  const ATDurationOrDerived::Ptr duration1 = createDuration(X("P21Y11M35DT13H20M10.69S"), context);
  const ATDurationOrDerived::Ptr duration2 = createDuration(X("P21Y11M35DT13H20M10.69S"), context);

  const ATDurationOrDerived::Ptr ym_duration1 = context->getItemFactory()->createYearMonthDuration(X("P21Y11M"), context);
  const ATDurationOrDerived::Ptr ym_duration2 = context->getItemFactory()->createYearMonthDuration(X("P263M"), context);

  const ATDurationOrDerived::Ptr dt_duration1 = context->getItemFactory()->createDayTimeDuration(X("P35DT13H20M10.69S"), context);
  const ATDurationOrDerived::Ptr dt_duration2 = context->getItemFactory()->createDayTimeDuration(X("P34DT36H80M10.69S"), context);

  assertEquals(duration1->asString(context), X("P21Y11M35DT13H20M10.69S")); 
  assertEquals(duration1->asString(context), duration2->asString(context));

  assertObjectEquals(ym_duration1, ym_duration1, context);  
  assertObjectEquals(ym_duration1, ym_duration2, context); 
  assertEquals(ym_duration1->asString(context), X("P21Y11M")); 
  assertEquals(ym_duration2->asString(context), X("P21Y11M")); 
  assertEquals(ym_duration1->asString(context), ym_duration2->asString(context));

  assertObjectEquals(dt_duration1, dt_duration1, context);  
  assertObjectEquals(dt_duration1, dt_duration2, context); 
  assertEquals(dt_duration1->asString(context), X("P35DT13H20M10.69S"));
  assertEquals(dt_duration2->asString(context), X("P35DT13H20M10.69S")); 
  assertEquals(dt_duration1->asString(context), dt_duration2->asString(context));

  // test 2 -- inequality

  const ATDurationOrDerived::Ptr duration3 = createDuration(X("P21Y7M20DT13H20M10.69S"), context);
  const ATDurationOrDerived::Ptr ym_duration3 = context->getItemFactory()->createYearMonthDuration(X("P21Y7M"), context);  
  const ATDurationOrDerived::Ptr ym_duration4 = context->getItemFactory()->createYearMonthDuration(X("-P21Y7M"), context);  
  const ATDurationOrDerived::Ptr dt_duration3 = context->getItemFactory()->createDayTimeDuration(X("P20DT13H20M10.69S"), context); 
  const ATDurationOrDerived::Ptr dt_duration4 = context->getItemFactory()->createDayTimeDuration(X("-P20DT13H20M10.69S"), context); 

  bool opNotSupported = false;
  try {
    assertCondition(!duration1->equals(duration3, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);
  
  opNotSupported = false;
  try {
    assertCondition(((const ATDurationOrDerived*)duration1)->greaterThan(duration3, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);

  opNotSupported = false;
  try {
    assertCondition(((const ATDurationOrDerived*)duration3)->lessThan(duration1, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);

  assertCondition(!ym_duration1->equals(ym_duration3, context));
  assertCondition(!ym_duration3->equals(ym_duration4, context));
  assertCondition(((const ATDurationOrDerived*)ym_duration1)->greaterThan(ym_duration3, context));
  assertCondition(((const ATDurationOrDerived*)ym_duration3)->greaterThan(ym_duration4, context));
  assertCondition(((const ATDurationOrDerived*)ym_duration3)->lessThan(ym_duration1, context));
  assertCondition(((const ATDurationOrDerived*)ym_duration4)->lessThan(ym_duration3, context));

  assertCondition(!dt_duration1->equals(dt_duration3, context));
  assertCondition(!dt_duration3->equals(dt_duration4, context));
  assertCondition(((const ATDurationOrDerived*)dt_duration1)->greaterThan(dt_duration3, context));
  assertCondition(((const ATDurationOrDerived*)dt_duration3)->greaterThan(dt_duration4, context));
  assertCondition(((const ATDurationOrDerived*)dt_duration3)->lessThan(dt_duration1, context));
  assertCondition(((const ATDurationOrDerived*)dt_duration4)->lessThan(dt_duration3, context));

  opNotSupported = false;
  try {
    assertCondition(!dt_duration1->equals(duration3, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);

  opNotSupported = false;
  try {
    assertCondition(!ym_duration1->equals(dt_duration3, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);
  
  opNotSupported = false;
  try {
    assertCondition(((const ATDurationOrDerived*)duration1)->greaterThan(ym_duration3, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);

  opNotSupported = false;
  try {
    assertCondition(((const ATDurationOrDerived*)dt_duration1)->greaterThan(ym_duration3, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);

  opNotSupported = false;
  try {
    assertCondition(((const ATDurationOrDerived*)duration3)->lessThan(dt_duration1, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);
  opNotSupported = false;
  try {
    assertCondition(((const ATDurationOrDerived*)ym_duration3)->lessThan(duration1, context));
  } catch (IllegalArgumentException &e) {
    opNotSupported = true;
  }
  assertCondition(opNotSupported);

  // test 3 -- component extraction
  assertObjectEquals(((const ATDurationOrDerived*)duration3)->getYears(), context->getItemFactory()->createInteger(21, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)duration3)->getMonths(), context->getItemFactory()->createInteger(7, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)duration3)->getDays(), context->getItemFactory()->createInteger(20, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)duration3)->getHours(), context->getItemFactory()->createInteger(13, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)duration3)->getMinutes(), context->getItemFactory()->createInteger(20, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)duration3)->getSeconds(), context->getItemFactory()->createDecimal(10.69, context), context);
  assertCondition(!((const ATDurationOrDerived*)duration3)->isNegative());

  assertObjectEquals(((const ATDurationOrDerived*)ym_duration3)->getYears(), context->getItemFactory()->createInteger(21, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)ym_duration3)->getMonths(), context->getItemFactory()->createInteger(7, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)ym_duration3)->getDays(), context->getItemFactory()->createInteger(0, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)ym_duration3)->getHours(), context->getItemFactory()->createInteger(0, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)ym_duration3)->getMinutes(), context->getItemFactory()->createInteger(0, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)ym_duration3)->getSeconds(), context->getItemFactory()->createDecimal(MAPM(0), context), context);
  assertCondition(!((const ATDurationOrDerived*)ym_duration3)->isNegative());
  assertCondition(((const ATDurationOrDerived*)ym_duration4)->isNegative());

  assertObjectEquals(((const ATDurationOrDerived*)dt_duration3)->getYears(), context->getItemFactory()->createInteger(0, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)dt_duration3)->getMonths(), context->getItemFactory()->createInteger(0, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)dt_duration3)->getDays(), context->getItemFactory()->createInteger(20, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)dt_duration3)->getHours(), context->getItemFactory()->createInteger(13, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)dt_duration3)->getMinutes(), context->getItemFactory()->createInteger(20, context), context);
  assertObjectEquals(((const ATDurationOrDerived*)dt_duration3)->getSeconds(), context->getItemFactory()->createDecimal(10.69, context), context);
  assertCondition(!((const ATDurationOrDerived*)dt_duration3)->isNegative());
  assertCondition(((const ATDurationOrDerived*)dt_duration4)->isNegative());

  // test 4 -- type name, type uri, hierarchy
  assertCondition(duration1->isInstanceOfType(
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA, 
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_DURATION, context));
  assertCondition(!duration1->isInstanceOfType(
      FunctionConstructor::XMLChXPath2DatatypesURI,
      ATDurationOrDerived::fgDT_YEARMONTHDURATION, context));
  assertCondition(!duration1->isInstanceOfType(
      FunctionConstructor::XMLChXPath2DatatypesURI,
      ATDurationOrDerived::fgDT_DAYTIMEDURATION, context));
  assertCondition(ym_duration1->isInstanceOfType(
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA, 
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_DURATION, context));
  assertCondition(ym_duration1->isInstanceOfType(
      FunctionConstructor::XMLChXPath2DatatypesURI,
      ATDurationOrDerived::fgDT_YEARMONTHDURATION, context));
  assertCondition(!ym_duration1->isInstanceOfType(
      FunctionConstructor::XMLChXPath2DatatypesURI,
      ATDurationOrDerived::fgDT_DAYTIMEDURATION, context));
  assertCondition(dt_duration1->isInstanceOfType(
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA, 
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_DURATION, context));
  assertCondition(dt_duration1->isInstanceOfType(
      FunctionConstructor::XMLChXPath2DatatypesURI,
      ATDurationOrDerived::fgDT_DAYTIMEDURATION, context));
  assertCondition(!dt_duration1->isInstanceOfType(
      FunctionConstructor::XMLChXPath2DatatypesURI,
      ATDurationOrDerived::fgDT_YEARMONTHDURATION, context));

  assertCondition(dt_duration1->isInstanceOfType(dt_duration1->getPrimitiveTypeURI(),
                                                  dt_duration1->getPrimitiveTypeName(),
                                                  context));
  assertCondition(dt_duration1->isInstanceOfType(dt_duration1->getTypeURI(),
                                                  dt_duration1->getTypeName(),
                                                  context));
  }

const ATDurationOrDerived::Ptr ATDurationTester::createDuration(const XMLCh* value,
                                             const DynamicContext* context) {
  return context->getItemFactory()->createDurationOrDerived(
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA,
      XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_DURATION,
      value, context);
}