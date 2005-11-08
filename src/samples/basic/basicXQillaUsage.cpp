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

#include <xqilla/utils/XStr.hpp>

//System includes

#if defined(WIN32) && !defined(__CYGWIN__)
#include <iostream.h>
#endif

//Xerces includes

#include <xercesc/dom/DOM.hpp>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>

//XQilla includes

#include <xqilla/dom-api/XQillaNSResolver.hpp>
#include <xqilla/exceptions/XQillaException.hpp>
#include <xqilla/dom-api/XQillaExpression.hpp>
#include <xqilla/dom-api/XQillaImplementation.hpp>
#include <xqilla/dom-api/XPath2Result.hpp>
#include <xqilla/utils/XQillaPlatformUtils.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>

// IO include
#include <iostream>

#define XERCES XERCES_CPP_NAMESPACE_QUALIFIER

int main(int argc, char *argv[])
{
  ///////////////////////
  // Initialise XQilla //
  ///////////////////////

  // 1. Initialize XQilla
  //
  // Note that this initialisation takes care of initialising
  // xerces-c as well
  try {
    
    XQillaPlatformUtils::initialize();
    
  } catch (const XERCES XMLException& eXerces) {
    char *pMsg = XERCES XMLString::transcode(eXerces.getMessage());
    std::cerr << "Error during Xerces-C initialisation.\n"
              << "Xerces exception message: "
              << pMsg << std::endl;
    delete pMsg;
    return 1;
  }

  // 2. Obtain a DOM3 XPath2 implementation.  This is a XQilla-specific 
  //    implementation that overrides the standard DOMDocument, the standard 
  //    DOMWriter and the standard DOMBuilder
  XERCES DOMImplementation* xqillaImplementation = 
    XERCES DOMImplementationRegistry::getDOMImplementation(X("XPath2 3.0"));

  // 3. Obtain a parser and set 'do namespaces', 'use schema' and 'validate' to 
  //    true.
  XERCES DOMBuilder* xmlParser = xqillaImplementation->createDOMBuilder(XERCES DOMImplementationLS::MODE_SYNCHRONOUS, 0);
  xmlParser->setFeature(X("namespaces"), true);
  xmlParser->setFeature(X("http://apache.org/xml/features/validation/schema"), true);
  xmlParser->setFeature(X("validation"), true);

  ////////////////////////////
  // Parse our XML document //
  ////////////////////////////
  
  XERCES DOMDocument* document = xmlParser->parseURI("data.xml");


  ////////////////////////////////
  // Create a parsed expression //
  // (compiled) and evaluate it //
  ////////////////////////////////


  // 1. Create a Namespace Resolver.  This holds a map of namespace prefixes 
  //    to namespace URIs.
  
  const XERCES DOMXPathNSResolver* resolver = document->createNSResolver(document->getDocumentElement());

  //    For a more advanced interface (like to have the ability to add 
  //    namespace bindings, this NSResolver can be cast to a XQillaNSResolver
  XQillaNSResolver* xqillaResolver = (XQillaNSResolver*)resolver;
  xqillaResolver->addNamespaceBinding(X("my"), X("http://example.com/myURI"));
  
  // **************** Example 1: max() function ****************** //
  
  // 2. Create a parsed expression
  char* expression = "max(( data(/Catalogue/Book[1]/Price), data(/Catalogue/Book[2]/Price) ))";
  const XERCES DOMXPathExpression* parsedExpression = document->createExpression(X(expression), resolver); 

  // 3. Evaluate the expression. We choose to have a first result, since we 
  //    know the answer will have only one item. Could also choose 
  //    XPath2Result::SNAPSHOT_RESULT and XPath2Result::ITERATOR_RESULT
  const XPath2Result* firstResult = (const XPath2Result*)parsedExpression->evaluate(document->getDocumentElement(), XPath2Result::FIRST_RESULT, 0);

  // 4. Work with the result: output it to the screen in this case
  std::cout << "The answer for expression '" << expression << "' is: " << firstResult->asDouble() <<std::endl;

  // **************** Example 2: output of nodes ****************** //
    
  // 2. Create a parsed expression
  char* expression2 = "//Magazine";
  parsedExpression = document->createExpression(X(expression2), resolver);

  // 3. Evaluate the expression. We choose to have a snapshot result, in case 
  //    the document changes 
  const XPath2Result* snapshotResult = (const XPath2Result*)parsedExpression->evaluate(document->getDocumentElement(), XPath2Result::SNAPSHOT_RESULT, 0);

  // 4. Work with the result: output it to the screen in this case
  
  // create a DOMWriter (serializer) to output the nodes
  XERCES DOMWriter* serializer = xqillaImplementation->createDOMWriter();
  XERCES StdOutFormatTarget* target = new XERCES StdOutFormatTarget();

  std::cout << "The answer for expression '" << expression2 << "' is: " <<std::endl;

  for(unsigned int i = 0; i < snapshotResult->getSnapshotLength(); i++) {
    if(snapshotResult->isNode()) {
      std::cout << "Node " << i << ": "<< std::flush;
      serializer->writeNode(target, *(snapshotResult->asNode()));
      std::cout << std::endl; // separate nodes with \n
    } else {
      std::cerr << "Expected a node but received an atomic value!"<< std::endl;
    }
  }

  serializer->release();

  ///////////////
  // Terminate //
  ///////////////

  XQillaPlatformUtils::terminate();
  
  return 0;
}