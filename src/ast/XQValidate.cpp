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
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
  Result toBeValidated = _expr->collapseTree(context, ASTNode::UNORDERED|ASTNode::RETURN_TWO);
  const Item::Ptr first = toBeValidated.next(context);
  const Item::Ptr second = toBeValidated.next(context);

  if(first == NULLRCP || second != NULLRCP || !first->isNode())
    XQThrow(FunctionException,X("XQValidate::collapseTreeInternal"), X("The expression to be validated must evaluate to exactly one document or element node [err:XQ0030]"));

  Node::Ptr node = (Node::Ptr)first;
  if(node->dmNodeKind() != Node::element_string &&
     node->dmNodeKind() != Node::document_string)
    XQThrow(FunctionException,X("XQValidate::collapseTreeInternal"), X("The expression to be validated must evaluate to exactly one document or element node [err:XQ0030]"));

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
  return resolvePredicates(ctx); // Never constant fold
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
