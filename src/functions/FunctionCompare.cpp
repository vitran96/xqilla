/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Oracle. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#include "../config/xqilla_config.h"
#include <xqilla/functions/FunctionCompare.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/impl/CodepointCollation.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/items/ATAnyURIOrDerived.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/ItemFactory.hpp>

const XMLCh FunctionCompare::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_c, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_p, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionCompare::minArgs = 2;
const unsigned int FunctionCompare::maxArgs = 3;

/**
 * fn:compare($comparand1 as xs:string?, $comparand2 as xs:string?) as xs:integer?
 * fn:compare($comparand1 as xs:string?, $comparand2 as xs:string?, $collation as xs:string) as xs:integer?
**/

FunctionCompare::FunctionCompare(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?,string?,string", args, memMgr)
{
  _src.getStaticType().flags = StaticType::DECIMAL_TYPE;
}

Sequence FunctionCompare::createSequence(DynamicContext* context, int flags) const
{
    Sequence str1 = getParamNumber(1,context)->toSequence(context);
    Sequence str2 = getParamNumber(2,context)->toSequence(context);
    if(str1.isEmpty() || str2.isEmpty())
        return Sequence(context->getMemoryManager());

    Collation* collation = NULL;
    if(getNumArgs()>2) {
        Sequence collArg = getParamNumber(3,context)->toSequence(context);
        const XMLCh* collName = collArg.first()->asString(context);
        try {
            context->getItemFactory()->createAnyURI(collName, context);
        } catch(XPath2ErrorException &e) {
            XQThrow(FunctionException, X("FunctionCompare::createSequence"), X("Invalid argument to compare function"));  
        }
        collation = context->getCollation(collName, this);
        if(collation == NULL)
            XQThrow(FunctionException,X("FunctionCompare::createSequence"),X("Collation object is not available"));
    }
    else
        collation = context->getDefaultCollation(this);
    if(collation == NULL)
        collation = context->getCollation(CodepointCollation::getCodepointCollationName(), this);

    const XMLCh* string1 = str1.first()->asString(context);
    const XMLCh* string2 = str2.first()->asString(context);
    Sequence result(context->getItemFactory()->createInteger(collation->compare(string1,string2), context), context->getMemoryManager());

    return result;
}
