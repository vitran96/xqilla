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

#include "DatatypeTester.hpp"
#include <xercesc/util/XMLString.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/AnyAtomicType.hpp>
#include <xqilla/exceptions/DSLException.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/utils/XStr.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <iostream>
#include <sstream>

DatatypeTester::DatatypeTester(XPath2MemoryManager* memMgr, char* name) : _memMgr(memMgr), _name(name) {
}

void DatatypeTester::assertEqualsInternal(const XMLCh* actual, const XMLCh* expected, const char *file, int line) {
  if(!XERCES_CPP_NAMESPACE_QUALIFIER XMLString::equals(actual, expected)) {
    std::stringstream str;
    str << file << ":" << line << ": assertion failed.  Actual value: '"
        << XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(actual) << "'. Expected value: '"
        << XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(expected) << "'." << std::flush;
    testFailed(str.str().c_str());
  } else {
    testPassed();
  }
}

void DatatypeTester::assertObjectEqualsInternal(const AnyAtomicType::Ptr &actual, const AnyAtomicType::Ptr &expected, const DynamicContext* context, const char *file, int line) {
  if(!actual->equals(expected, context)) {
    std::stringstream str;
    str << file << ":" << line << ": assertion failed.  First value: '"
        << XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(actual->asString(context)) << "'. Second value: '"
        << XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(expected->asString(context)) << "'." << std::flush;
    testFailed(str.str().c_str());
  } else {
    testPassed();
  }
}

void DatatypeTester::assertConditionInternal(bool condition, const char *file, int line) {
  if(!condition) {
    std::stringstream str;
    str << file << ":" << line << ": assertion failed." << std::flush;
    testFailed(str.str().c_str());
  } else {
    testPassed();
  }
}

        
void DatatypeTester::init() {
  std::cerr << "--> Testing " << _name << std::endl;
}

void DatatypeTester::wrapUp() {
  std::cerr << std::endl;
}

void DatatypeTester::testPassed() const {
  std::cerr<< "." << std::flush;
}

void DatatypeTester::testFailed(const char* msg) const {
  DSLthrow(XPath2ErrorException, X("DatatypeTester"), XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(msg));
}

XPath2MemoryManager* DatatypeTester::getMemoryManager() const {
  return _memMgr;
}

char* DatatypeTester::getName() const {
  return _name;
}