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
#include <xqilla/functions/FunctionDateTime.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/ATDateTimeOrDerived.hpp>
#include <xqilla/items/ATTimeOrDerived.hpp>
#include <xqilla/items/ATDateOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>

const XMLCh FunctionDateTime::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_T, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull };
const unsigned int FunctionDateTime::minArgs = 2;
const unsigned int FunctionDateTime::maxArgs = 2;

/**
 * fn:dateTime($arg1 as xs:date, $arg2 as xs:time) as xs:dateTime
**/

FunctionDateTime::FunctionDateTime(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "date, time", args, memMgr)
{
}

ASTNode* FunctionDateTime::staticResolution(StaticContext *context)
{
  return resolveASTNodesForDateOrTime(_args, context, true);
}

Sequence FunctionDateTime::collapseTreeInternal(DynamicContext* context, int flags) const
{
    Sequence arg1= getParamNumber(1, context);
    const ATDateOrDerived::Ptr date=arg1.first();
    Sequence arg2= getParamNumber(2, context);
    const ATTimeOrDerived::Ptr time=arg2.first();

    // convert the time into a duration
    XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer buff(64, context->getMemoryManager());
    buff.append(XERCES_CPP_NAMESPACE_QUALIFIER chLatin_P);
    buff.append(XERCES_CPP_NAMESPACE_QUALIFIER chLatin_T);
    if(!time->getHours()->isZero())
    {
        buff.append(time->getHours()->asString(context));
        buff.append(XERCES_CPP_NAMESPACE_QUALIFIER chLatin_H);
    }
    if(!time->getMinutes()->isZero())
    {
        buff.append(time->getMinutes()->asString(context));
        buff.append(XERCES_CPP_NAMESPACE_QUALIFIER chLatin_M);
    }
    buff.append(time->getSeconds()->asString(context));
    buff.append(XERCES_CPP_NAMESPACE_QUALIFIER chLatin_S);
    ATDurationOrDerived::Ptr timeAsDur=context->getItemFactory()->createDayTimeDuration(buff.getRawBuffer(), context);

    // convert the date into a dateTime, with no timezone
    const ATDateTimeOrDerived::Ptr dateTime=date->castAs(XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgURI_SCHEMAFORSCHEMA, 
                                                         XERCES_CPP_NAMESPACE_QUALIFIER SchemaSymbols::fgDT_DATETIME, 
                                                         context);
    Timezone::Ptr emptyTZ = new Timezone(0, 0);  
    const ATDateTimeOrDerived::Ptr dateTimeNoTZ=dateTime->setTimezone(emptyTZ, context);

    // add them
    const ATDateTimeOrDerived::Ptr result=dateTimeNoTZ->addDayTimeDuration(timeAsDur, context);

    // fix the timezone
    if(date->hasTimezone())
    {
        const Timezone::Ptr dateTZ=date->getTimezone();
        if(time->hasTimezone())
        {
            const Timezone::Ptr timeTZ=time->getTimezone();
            if(!timeTZ->equals(dateTZ))
                DSLthrow(FunctionException, X("FunctionDateTime::collapseTreeInternal"), X("Both arguments to fn:dateTime have a speciified timezone [err:FORG0008]"));
        }
        return Sequence(result->setTimezone(dateTZ, context), context->getMemoryManager());
    }
    else if(time->hasTimezone())
    {
        const Timezone::Ptr timeTZ=time->getTimezone();
        return Sequence(result->setTimezone(timeTZ, context), context->getMemoryManager());
    }
    return Sequence(result, context->getMemoryManager());
}















