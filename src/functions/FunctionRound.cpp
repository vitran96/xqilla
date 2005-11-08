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
#include <xqilla/functions/FunctionRound.hpp>

#include <xqilla/items/Numeric.hpp>

#include <xqilla/context/DynamicContext.hpp>

const XMLCh FunctionRound::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionRound::minArgs = 1;
const unsigned int FunctionRound::maxArgs = 1;

/*
 * fn:round($arg as numeric?) as numeric?
 */

FunctionRound::FunctionRound(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : NumericFunction(name, minArgs, maxArgs, "anySimpleType?", args, memMgr)
{
  _src.getStaticType().flags = StaticResolutionContext::NUMERIC_TYPE;
}

Sequence FunctionRound::collapseTreeInternal(DynamicContext* context, int flags) const
{
	XPath2MemoryManager* memMgr = context->getMemoryManager();

  Sequence arg = getParamNumber(1, context);
    
  //If the argument is the empty sequence, the empty sequence is returned.

  if(arg.isEmpty()) {
    return Sequence(memMgr);
  }

  const Numeric::Ptr numericArg = (const Numeric::Ptr )arg.first();
  if(isNaN(numericArg))
    return Sequence(numericArg, memMgr);
  if(isINF(numericArg))
    return Sequence(numericArg, memMgr);
  return Sequence(numericArg->round(context), memMgr);
}
