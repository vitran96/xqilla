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
#include "xqilla/functions/FunctionNumber.hpp"
#include "xqilla/framework/StringPool.hpp"
#include <xqilla/functions/FunctionMatches.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/regx/RegularExpression.hpp>

#if defined(XERCES_HAS_CPP_NAMESPACE)
XERCES_CPP_NAMESPACE_USE
#endif

const XMLCh FunctionMatches::name[] = {
  chLatin_m, chLatin_a, chLatin_t, 
  chLatin_c, chLatin_h, chLatin_e, 
  chLatin_s, chNull 
};
const unsigned int FunctionMatches::minArgs = 2;
const unsigned int FunctionMatches::maxArgs = 3;

/**
 * fn:matches($input as xs:string?, $pattern as xs:string) as xs:boolean
 * fn:matches($input as xs:string?, $pattern as xs:string, $flags as xs:string) as xs:boolean
 */
  
FunctionMatches::FunctionMatches(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?, string, string", args, memMgr),
    regExp_(0), pattern_(0), options_(0)
{
  _src.getStaticType() = StaticType::BOOLEAN_TYPE;
}

ASTNode *FunctionMatches::staticTypingImpl(StaticContext *context)
{
  //either there are 2 args, and regexp should be a constant,
  //or there is an options argument as well, and it should also be a constant
  if(context && !regExp_ && _args[1]->isConstant() &&
    (getNumArgs() == 2 || (getNumArgs() == 3 && _args[2]->isConstant())))
  {
    XPath2MemoryManager* memMgr = context->getMemoryManager();

    AutoDelete<DynamicContext> dContext(context->createDynamicContext());
    dContext->setMemoryManager(memMgr);

    Item::Ptr patternItem = getParamNumber(2, dContext)->next(dContext);
    pattern_ = (XMLCh*) patternItem->asString(dContext);

    options_ = (XMLCh*) XMLUni::fgZeroLenString;
    if(getNumArgs() == 3)
    {
      Item::Ptr optsItem = getParamNumber(3, dContext)->next(dContext);
      options_ = (XMLCh*) optsItem->asString(dContext);
    	checkRegexpOpts(options_);
  	}

  	try
    {
      regExp_ = new (memMgr) RegularExpression(pattern_, options_);
    } catch (ParseException &e){
      processParseException(e, memMgr);
    }
  }
	
  return this;
}


Sequence FunctionMatches::createSequence(DynamicContext* context, int flags) const
{
  XPath2MemoryManager* memMgr = context->getMemoryManager();

  const XMLCh* input = XMLUni::fgZeroLenString;
  Item::Ptr inputItem = getParamNumber(1,context)->next(context);
  if(inputItem.notNull())
    input=inputItem->asString(context);

  if(regExp_)
  {
    try
    {
      return Sequence(context->getItemFactory()->createBoolean(matches(input, regExp_), context), memMgr);
    } catch (XMLException &e){
      processXMLException(e);
    }
  }

  //do not get here if we had precompiled regexp

  const XMLCh* pattern = getParamNumber(2,context)->next(context)->asString(context);

  const XMLCh* options = XMLUni::fgZeroLenString;
  if(getNumArgs()>2)
    options=getParamNumber(3,context)->next(context)->asString(context);

  //Check that the options are valid - throw an exception if not (can have s,m,i and x)
  //Note: Are allowed to duplicate the letters.
  checkRegexpOpts(options);

  try {
    return Sequence(context->getItemFactory()->createBoolean(matches(input, pattern, options), context), memMgr);
  } catch (ParseException &e){ 
	processParseException(e, memMgr);
  } catch (XMLException &e){
	processXMLException(e);
  }  

  //do not get here

}

void FunctionMatches::checkRegexpOpts(const XMLCh* opts) const
{
  const XMLCh* cursor = opts;
  for(; *cursor != 0; ++cursor){
    switch(*cursor) {
    case chLatin_s:
    case chLatin_m:
    case chLatin_i:
    case chLatin_x:
      break;
    default:
      XQThrow(FunctionException, X("FunctionMatches::createSequence"),X("Invalid regular expression flags [err:FORX0001]."));
    }
  }
}

void FunctionMatches::processParseException(ParseException &e, XPath2MemoryManager* memMgr) const
{
  XMLBuffer buf(1023, memMgr);
  buf.set(X("Invalid regular expression: "));
  buf.append(e.getMessage());
  buf.append(X(" [err:FORX0002]"));
  XQThrow(FunctionException, X("FunctionMatches::createSequence"), buf.getRawBuffer());
}

void FunctionMatches::processXMLException(XMLException &e) const
{
  XQThrow(FunctionException, X("FunctionMatches::createSequence"), e.getMessage());
}

bool FunctionMatches::matches(const XMLCh *input, const XMLCh *pattern, const XMLCh *options)
{
  // If the value of $operand2 is the zero-length string, then the function returns true
  if(pattern == 0 || *pattern == 0) return true;

  if(input == 0) input = XMLUni::fgZeroLenString;

  // Always turn off head character optimisation, since it is broken
  XMLBuffer optionsBuf;
  optionsBuf.set(options);
  optionsBuf.append(chLatin_H);

  //Build the Regular Expression
  RegularExpression regEx(pattern, optionsBuf.getRawBuffer());
  return regEx.matches(input);
}

//should be invoked only we have a precompiled regexp
bool FunctionMatches::matches(const XMLCh *input, XERCES_CPP_NAMESPACE_QUALIFIER RegularExpression* regExp)
{
  if(input == 0)
  {
    input = XMLUni::fgZeroLenString;
  }
  return regExp->matches(input);
}

void FunctionMatches::copyRegExp(FunctionMatches* source, XPath2MemoryManager* memMgr)
{
  if(source->regExp_)
  {
    pattern_ = memMgr->getPooledString(source->pattern_);
    options_ = memMgr->getPooledString(source->options_);

    //compiling regexp again
    try
    {
      regExp_ = new (memMgr) RegularExpression(pattern_, options_);
    } catch (ParseException &e){
      processParseException(e, memMgr);
    }
  }
}

