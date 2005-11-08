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
#include <xqilla/functions/FunctionContains.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/impl/CodepointCollation.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/ATAnyURIOrDerived.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xqilla/context/ItemFactory.hpp>

const XMLCh FunctionContains::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionContains::minArgs = 2;
const unsigned int FunctionContains::maxArgs = 3;

/**
 * fn:contains($arg1 as xs:string?, $arg2 as xs:string?) as xs:boolean
 * fn:contains($arg1 as xs:string?, $arg2 as xs:string?, $collation as xs:string) as xs:boolean
**/

FunctionContains::FunctionContains(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?,string?,string", args, memMgr)
{
}

Sequence FunctionContains::collapseTreeInternal(DynamicContext* context, int flags) const
{
    Sequence str1 = getParamNumber(1,context);
    Sequence str2 = getParamNumber(2,context);

    Collation* collation = NULL;
    if(getNumArgs()>2) {
        Sequence collArg = getParamNumber(3,context);
        const XMLCh* collName = collArg.first()->asString(context);
        try {
            context->getItemFactory()->createAnyURI(collName, context);
        } catch(XPath2ErrorException &e) {
            DSLthrow(FunctionException, X("FunctionContains::collapseTreeInternal"), X("Invalid collationURI"));  
        }
        collation=context->getCollation(collName);
        if(collation==NULL)
            DSLthrow(FunctionException,X("FunctionContains::collapseTreeInternal"),X("Collation object is not available"));
    }
    else
        collation=context->getCollation(CodepointCollation::getCodepointCollationName());

    const XMLCh* container = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
    if(!str1.isEmpty())
        container=str1.first()->asString(context);
    const XMLCh* pattern = XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString;
    if(!str2.isEmpty())
        pattern=str2.first()->asString(context);

    if(XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(pattern)==0)
        return Sequence(context->getItemFactory()->createBoolean(true, context), context->getMemoryManager());
    else if(XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen(container)==0)
        return Sequence(context->getItemFactory()->createBoolean(false, context), context->getMemoryManager());

    bool contains = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::patternMatch(container, pattern) > -1;
    return Sequence(context->getItemFactory()->createBoolean(contains, context), context->getMemoryManager());
}