/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#include "../config/xqilla_config.h"
#include <xqilla/functions/FunctionTranslate.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLString.hpp>

#include <map>

const XMLCh FunctionTranslate::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_l, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionTranslate::minArgs = 3;
const unsigned int FunctionTranslate::maxArgs = 3;

/**
 * fn:translate($arg as xs:string?, $mapString as xs:string, $transString as xs:string) as xs:string
**/

FunctionTranslate::FunctionTranslate(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?,string,string", args, memMgr)
{
  _src.getStaticType().flags = StaticType::STRING_TYPE;
}

Sequence FunctionTranslate::collapseTreeInternal(DynamicContext* context, int flags) const
{
	XPath2MemoryManager* memMgr = context->getMemoryManager();
	Sequence str1 = getParamNumber(1,context)->toSequence(context);

	if(str1.isEmpty()) {
    return Sequence(context->getItemFactory()->createString(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString, context), memMgr);
  }
 
	Sequence str2 = getParamNumber(2,context)->toSequence(context);
	Sequence str3 = getParamNumber(3,context)->toSequence(context);

	const XMLCh* container = str1.first()->asString(context);
	const XMLCh* search = str2.first()->asString(context);
	const XMLCh* replace = str3.first()->asString(context);

  if(XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(search)==0)
    return Sequence(context->getItemFactory()->createString(container, context), memMgr);

  std::map<XMLInt32,XMLInt32> Change;
  const XMLCh* cursorS=search;
  const XMLCh* cursorR=replace;
  while(*cursorS)
  {
    XMLInt32 chS=*cursorS;
    if(XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::isHighSurrogate(*cursorS) && 
       XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::isLowSurrogate(*(cursorS+1)))
    {
      chS=XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::composeFromSurrogate(*cursorS, *(cursorS+1));
      cursorS++;
    }
    XMLInt32 chR=0;
    if(*cursorR)
    {
      if(XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::isHighSurrogate(*cursorR) && 
         XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::isLowSurrogate(*(cursorR+1)))
      {
        chR=XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::composeFromSurrogate(*cursorR, *(cursorR+1));
        cursorR++;
      }
      else
        chR=*cursorR;
    }
    if(Change.find(chS)==Change.end())
      Change[chS] = chR;
    cursorS++;
    if(*cursorR)
      cursorR++;
  }
  
  XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer result(1023, context->getMemoryManager());
  const XMLCh* cursor=container;
  while(*cursor)
  {
    XMLInt32 ch=*cursor;
    if(XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::isHighSurrogate(*cursor) && 
       XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::isLowSurrogate(*(cursor+1)))
    {
      ch=XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::composeFromSurrogate(*cursor, *(cursor+1));
      cursor++;
    }
    std::map<XMLInt32,XMLInt32>::iterator it=Change.find(ch);
    XMLInt32 newCh=0;
    if (it == Change.end())
      newCh=ch;
    else
      newCh=it->second;
    if(newCh!=0)
    {
      if ( newCh >= 0x10000) 
      {
        XMLCh one, two;
        XERCES_CPP_NAMESPACE_QUALIFIER RegxUtil::decomposeToSurrogates(newCh, one, two);
        result.append(one);
        result.append(two);
    }
    else
        result.append(newCh);
    }
    cursor++;
  }

  return Sequence(context->getItemFactory()->createString(result.getRawBuffer(), context), memMgr);
}
