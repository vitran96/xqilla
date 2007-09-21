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

#include <xqilla/ast/XQAtomize.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/exceptions/StaticErrorException.hpp>

XQAtomize::XQAtomize(ASTNode* expr, XPath2MemoryManager* memMgr)
  : ASTNodeImpl(memMgr),
  expr_(expr)
{
  setType(ASTNode::ATOMIZE);
}

ASTNode* XQAtomize::staticResolution(StaticContext *context)
{
  expr_ = expr_->staticResolution(context);
  return this;
}

ASTNode *XQAtomize::staticTyping(StaticContext *context)
{
  _src.clear();

  expr_ = expr_->staticTyping(context);
  _src.getStaticType() = expr_->getStaticAnalysis().getStaticType();
  _src.add(expr_->getStaticAnalysis());

  if(expr_->getStaticAnalysis().isUpdating()) {
    XQThrow(StaticErrorException,X("XQAtomize::staticTyping"),
            X("It is a static error for an atomized expression "
              "to be an updating expression [err:XUST0001]"));
  }

  if(!_src.getStaticType().containsType(StaticType::NODE_TYPE)) {
    // If the expression has no nodes, this function does nothing
    return expr_;
  }

  static const unsigned int anytype_types = StaticType::ELEMENT_TYPE | StaticType::ATTRIBUTE_TYPE;
  static const unsigned int untyped_types = StaticType::DOCUMENT_TYPE | StaticType::TEXT_TYPE;
  static const unsigned int string_types = StaticType::NAMESPACE_TYPE | StaticType::COMMENT_TYPE | StaticType::PI_TYPE;

  if(_src.getStaticType().containsType(anytype_types)) {
    _src.getStaticType().flags &= ~anytype_types;
    _src.getStaticType().flags |= StaticType::ANY_ATOMIC_TYPE;
  }
  if(_src.getStaticType().containsType(untyped_types)) {
    _src.getStaticType().flags &= ~untyped_types;
    _src.getStaticType().flags |= StaticType::UNTYPED_ATOMIC_TYPE;
  }
  if(_src.getStaticType().containsType(string_types)) {
    _src.getStaticType().flags &= ~string_types;
    _src.getStaticType().flags |= StaticType::STRING_TYPE;
  }

  if(expr_->isConstant()) {
    return constantFold(context);
  }
  return this;
}

Result XQAtomize::createResult(DynamicContext* context, int flags) const
{
  return new AtomizeResult(this, expr_->createResult(context, flags));
}

Item::Ptr AtomizeResult::next(DynamicContext *context)
{
  // for $item in (Expr) return
  //   typeswitch ($item)
  //     case $value as atomic value return $value
  //     default $node return fn:data($node)

  Item::Ptr result = _sub->next(context);
  while(result.isNull()) {
    _sub = 0;
    result = _parent->next(context);
    if(result.isNull()) {
      _parent = 0;
      return 0;
    }
    if(result->isNode()) {
      _sub = ((Node*)result.get())->dmTypedValue(context);
      result = _sub->next(context);
    }
  }
  return result;
}

