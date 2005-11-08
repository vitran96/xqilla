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
#include <xqilla/functions/FunctionAdjustDateTimeToTimezone.hpp>
#include <xqilla/items/ATDateTimeOrDerived.hpp>
#include <xqilla/items/ATDurationOrDerived.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include "../utils/DateUtils.hpp"
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xqilla/items/Timezone.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>

const XMLCh FunctionAdjustDateTimeToTimezone::name[] = { 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_j, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_T, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_z, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionAdjustDateTimeToTimezone::minArgs = 1;
const unsigned int FunctionAdjustDateTimeToTimezone::maxArgs = 2;

/*
 * fn:adjust-dateTime-to-timezone($arg as xs:dateTime?) as xs:dateTime?
 * fn:adjust-dateTime-to-timezone($arg as xs:dateTime?, $timezone as xdt:dayTimeDuration?) as xs:dateTime?
 */

FunctionAdjustDateTimeToTimezone::FunctionAdjustDateTimeToTimezone(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "dateTime?, dayTimeDuration?", args, memMgr)
{
}

ASTNode* FunctionAdjustDateTimeToTimezone::staticResolution(StaticContext *context) {
  if(getNumArgs() == 1) {
    _src.implicitTimezoneUsed(true);
  }
  return resolveASTNodes(_args, context, getNumArgs() > 1);
}

Sequence FunctionAdjustDateTimeToTimezone::collapseTreeInternal(DynamicContext* context, int flags) const
{
	XPath2MemoryManager* memMgr = context->getMemoryManager();

  //If $srcval is the empty sequence, then the result is the empty sequence.
  Sequence op1 = getParamNumber(1, context);
  if (op1.isEmpty()) {
    return Sequence(memMgr);
  }

  const ATDateTimeOrDerived* dateTime = (const ATDateTimeOrDerived*)(const Item*)op1.first();

  //If $timezone is not specified, then $timezone is the value of the implicit timezone in the evaluation context.
  ATDurationOrDerived::Ptr timezoneAsDuration = 0;

  if (getNumArgs() > 1) {
    Sequence op2 = getParamNumber(2, context);
    if (op2.isEmpty()) {
      // unset the timezone
      return Sequence(dateTime->setTimezone(0, context), memMgr);
    } else {
      timezoneAsDuration = (const ATDurationOrDerived::Ptr )op2.first();
      Timezone::Ptr timezone = new Timezone(timezoneAsDuration, context);
      if(!timezoneAsDuration->equals(timezone->asDayTimeDuration(context), context)) {
        DSLthrow(FunctionException, X("FunctionAdjustDateTimeToTimeZone::collapseTreeInternal"),X("invalid timezone value"));    
      }
    }
  }
  else {
    timezoneAsDuration = context->getImplicitTimezone();
  }

  return Sequence(dateTime->addTimezone(timezoneAsDuration, context), memMgr);
}