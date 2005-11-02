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

#include "../config/pathan_config.h"
#include <xqilla/functions/FunctionFalse.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/PathanFactory.hpp>

const XMLCh FunctionFalse::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_f, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_l, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionFalse::minArgs = 0;
const unsigned int FunctionFalse::maxArgs = 0;

/*
 * fn:false() as xs:boolean
 */

FunctionFalse::FunctionFalse(const VectorOfDataItems &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "empty()", args, memMgr)
{
}

Sequence FunctionFalse::collapseTreeInternal(DynamicContext* context, int flags) const
{
	return Sequence(context->getPathanFactory()->createBoolean(false, context),
                  context->getMemoryManager());
}
