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

#include "../config/xqilla_config.h"
#include <xqilla/functions/FunctionReplace.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/util/regx/RegularExpression.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xercesc/util/XMLUni.hpp>

const XMLCh FunctionReplace::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_l, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionReplace::minArgs = 3;
const unsigned int FunctionReplace::maxArgs = 4;

/** 
 * fn:replace($input as xs:string?, $pattern as xs:string, $replacement as xs:string) as xs:string
 * fn:replace($input as xs:string?, $pattern as xs:string, $replacement as xs:string, $flags as xs:string) as xs:string
 */
  
FunctionReplace::FunctionReplace(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?, string, string, string", args, memMgr)
{
}

Sequence FunctionReplace::collapseTreeInternal(DynamicContext* context, int flags) const
{
	XPath2MemoryManager* memMgr = context->getMemoryManager();
	Sequence inputString=getParamNumber(1,context);
	Sequence patternString=getParamNumber(2,context);
	Sequence replacementString=getParamNumber(3,context);

 	const XMLCh* input = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
    if(!inputString.isEmpty())
        input=inputString.first()->asString(context);
	const XMLCh *pattern = patternString.first()->asString(context);
	const XMLCh *replacement = replacementString.first()->asString(context);

	const XMLCh *options = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
	if(getNumArgs()>3)
		options=getParamNumber(4,context).castAsSingleString(context);
  
  //Check that the options are valid - throw an exception if not (can have s,m,i and x)
  //Note: Are allowed to duplicate the letters.
  for (unsigned int i=0; i< XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(options); i++){
   if (options[i]!= XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s &&
       options[i]!= XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m &&
       options[i]!= XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i &&
       options[i]!= XERCES_CPP_NAMESPACE_QUALIFIER chLatin_x)
      DSLthrow(FunctionException, X("FunctionReplace::collapseTreeInternal"),X("Invalid regular expression flags"));  
  }

  const XMLCh* result=NULL;
  //Now attempt to replace
  try {
    XERCES_CPP_NAMESPACE_QUALIFIER RegularExpression regEx(pattern, options, memMgr);
    result = regEx.replace(input, replacement);
  } catch (XERCES_CPP_NAMESPACE_QUALIFIER XMLException &e){ 
    DSLthrow(FunctionException, X("FunctionReplace::collapseTreeInternal"), e.getMessage());  
  }
  catch(...) {
    DSLthrow(FunctionException, X("FunctionReplace::collapseTreeInternal"),X("Invalid regular expression"));
  }  

  return Sequence(context->getItemFactory()->createString(result, context), memMgr);
}