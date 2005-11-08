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
#include <xqilla/functions/FunctionEndsWith.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/impl/CodepointCollation.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/items/ATAnyURIOrDerived.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/ItemFactory.hpp>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>

const XMLCh FunctionEndsWith::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_w, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_h, 
  XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionEndsWith::minArgs = 2;
const unsigned int FunctionEndsWith::maxArgs = 3;

/*
 * fn:ends-with($arg1 as xs:string?, $arg2 as xs:string?) as xs:boolean
 * fn:ends-with($arg1 as xs:string?, $arg2 as xs:string?, $collation as xs:string) as xs:boolean
 */

FunctionEndsWith::FunctionEndsWith(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?,string?,string", args, memMgr)
{
}

Sequence FunctionEndsWith::collapseTreeInternal(DynamicContext* context, int flags) const
{
    Sequence sourceString=getParamNumber(1,context);
    Sequence findString=getParamNumber(2,context);

    const XMLCh* source = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
    if(!sourceString.isEmpty())
        source=sourceString.first()->asString(context);
    const XMLCh* find = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
    if(!findString.isEmpty())
        find=findString.first()->asString(context);

    // If the value of $operand1 is the zero-length string and the value of $operand2 is not the zero-length string,
    // then the function returns false.
    if(XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(source)==0 && XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(find)>0)
        return Sequence(context->getItemFactory()->createBoolean(false, context), context->getMemoryManager());
    // If the value of $operand2 is the zero-length string, then the function returns true
    if(XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(find)==0)
        return Sequence(context->getItemFactory()->createBoolean(true, context), context->getMemoryManager());

    Collation* collation=NULL;
    if(getNumArgs()>2) {
        Sequence collArg = getParamNumber(3,context);
        const XMLCh* collName = collArg.first()->asString(context);
        try {
            context->getItemFactory()->createAnyURI(collName, context);
        } catch(XPath2ErrorException &e) {
            DSLthrow(FunctionException, X("FunctionEndsWith::collapseTreeInternal"), X("Invalid collationURI"));  
        }
        collation=context->getCollation(collName);
        if(collation==NULL)
            DSLthrow(FunctionException,X("FunctionEndsWith::collapseTreeInternal"),X("Cannot find requested collation"));
    }
    else
        collation=context->getCollation(CodepointCollation::getCodepointCollationName());

	// Returns a boolean indicating whether or not the value of $operand1 ends with a string that is equal to the value
	// of $operand2 according to the specified collation

    if(XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(find)>XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(source))
        return Sequence(context->getItemFactory()->createBoolean(false, context), context->getMemoryManager());
    int i,j;
    for(i = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(source)-1, j=XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(find)-1; i >=0 && j >=0; i--,j--)
    {
        const XMLCh *string1 = XPath2Utils::subString(source, i,1, context->getMemoryManager());
        const XMLCh *string2 =  XPath2Utils::subString(find, j, 1, context->getMemoryManager());
        bool result = (collation->compare(string1, string2)!=0);

        if(result) {
            return Sequence(context->getItemFactory()->createBoolean(false, context), context->getMemoryManager());
        }
    }

    return Sequence(context->getItemFactory()->createBoolean(true, context), context->getMemoryManager());
}