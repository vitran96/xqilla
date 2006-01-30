/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

//////////////////////////////////////////////////////////////////////
// XQValidate.cpp: implementation of the XQValidate class.
//////////////////////////////////////////////////////////////////////

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQValidate.hpp>
#include <xqilla/context/impl/XQDynamicContextImpl.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/validators/schema/SchemaGrammar.hpp>
#include <xercesc/validators/common/ContentSpecNode.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>
#include <xqilla/ast/XQSequence.hpp>
#include <xqilla/items/DatatypeFactory.hpp>

////////////////////////////////////////////////////////////////////////////////////////
//
//

XQValidate::XQValidate(ASTNode* valExpr, DocumentCache::ValidationMode valMode, XPath2MemoryManager* expr)
  : ASTNodeImpl(expr)
{
  _expr=valExpr;
  _validationMode=valMode;
  setType(ASTNode::VALIDATE);
}

Sequence XQValidate::collapseTreeInternal(DynamicContext* context, int flags) const
{
  Result toBeValidated = _expr->collapseTree(context);
  const Item::Ptr first = toBeValidated->next(context);
  const Item::Ptr second = toBeValidated->next(context);

  if(first == NULLRCP || second != NULLRCP || !first->isNode())
    XQThrow(FunctionException,X("XQValidate::collapseTreeInternal"), X("The expression to be validated must evaluate to exactly one document or element node [err:XQTY0030]."));

  Node::Ptr node = (Node::Ptr)first;
  if(node->dmNodeKind() != Node::element_string &&
     node->dmNodeKind() != Node::document_string)
    XQThrow(FunctionException,X("XQValidate::collapseTreeInternal"), X("The expression to be validated must evaluate to exactly one document or element node [err:XQTY0030]."));

  // perform validation on this item
  Node::Ptr validatedElt = context->validate(node, _validationMode);
  if(validatedElt.isNull())
    XQThrow(FunctionException,X("XQValidate::collapseTreeInternal"), X("Unexpected error while validating"));

  return Sequence(validatedElt, context->getMemoryManager());
}

ASTNode* XQValidate::staticResolution(StaticContext* ctx)
{
  _expr = _expr->staticResolution(ctx);
  _src.add(_expr->getStaticResolutionContext());

  _src.getStaticType().flags = StaticType::NODE_TYPE;
  _src.forceNoFolding(true);
  return this; // Never constant fold
}

const ASTNode *XQValidate::getExpression() const
{
  return _expr;
}

DocumentCache::ValidationMode XQValidate::getValidationMode() const
{
  return _validationMode;
}

void XQValidate::setExpression(ASTNode *expr)
{
  _expr = expr;
}
