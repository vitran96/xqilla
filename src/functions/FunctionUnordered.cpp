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
#include <sstream>

#include <xqilla/functions/FunctionUnordered.hpp>
#include <xqilla/context/DynamicContext.hpp>

const XMLCh FunctionUnordered::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_d, 
  XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionUnordered::minArgs = 1;
const unsigned int FunctionUnordered::maxArgs = 1;

/**
 * fn:unordered($sourceSeq as item()*) as item()*
**/

FunctionUnordered::FunctionUnordered(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : XQFunction(name, minArgs, maxArgs, "item()*", args, memMgr)
{
}

ASTNode* FunctionUnordered::staticResolution(StaticContext *context)
{
  bool allConstant = true;
  for(VectorOfASTNodes::iterator i = _args.begin(); i != _args.end(); ++i) {
    *i = (*i)->staticResolution(context);
    _src.getStaticType() = (*i)->getStaticResolutionContext().getStaticType();
    _src.add((*i)->getStaticResolutionContext());
    if(!(*i)->isConstant()) {
      allConstant = false;
    }
    break; // There should be only one
  }

  if(allConstant) {
    return constantFold(context);
  }
  else {
    return resolvePredicates(context);
  }
}

Result FunctionUnordered::createResult(DynamicContext* context, int flags) const
{
  return new UnorderedResult(this, flags, context);
}

FunctionUnordered::UnorderedResult::UnorderedResult(const FunctionUnordered *func, int flags, DynamicContext *context)
  : ResultImpl(context),
    _flags(flags),
    _func(func),
    _arg(0)
{
}

Item::Ptr FunctionUnordered::UnorderedResult::next(DynamicContext *context)
{
  if(_arg.isNull()) {
    _arg = _func->getParamNumber(1, context, ASTNode::UNORDERED|_flags);
  }
  return _arg.next(context);
}

std::string FunctionUnordered::UnorderedResult::asString(DynamicContext *context, int indent) const
{
  std::ostringstream oss;
  std::string in(getIndent(indent));

  oss << in << "<unordered/>" << std::endl;

  return oss.str();
}