/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 * Copyright (c) 2004-2006
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

#include "../config/xqilla_config.h"
#include <assert.h>
#include <sstream>

#include <xqilla/utils/PrintAST.hpp>
#include <xqilla/axis/NodeTest.hpp>

#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/utils/XStr.hpp>

#if defined(XERCES_HAS_CPP_NAMESPACE)
XERCES_CPP_NAMESPACE_USE
#endif

NodeTest::NodeTest()
  : _name(0),
    _uri(0),
    _prefix(0),
    _type(0),
    _wildcardName(false),
    _wildcardNamespace(false),
    _wildcardType(false),
    _usePrefix(false),
    _hasChildren(false),
    _itemType(0)
{
}

NodeTest::~NodeTest() {
  delete _itemType;
}

void *NodeTest::getInterface(const XMLCh *name) const
{
  return 0;
}

Result NodeTest::filterResult(const Result &toFilter, DynamicContext* context) const
{
  return new FilterResult(toFilter, this, context);
}

bool NodeTest::filterNode(Node::Ptr node, DynamicContext* context) const
{
  if(_itemType) return _itemType->matches(node, context);
  else return checkNodeType(node) && checkNodeName(node, context);
}

bool NodeTest::checkNodeType(Node::Ptr node) const
{
	assert(node.notNull());

	if(_wildcardType) {
    if(_hasChildren) {
      return node->dmNodeKind() == Node::element_string || node->dmNodeKind() == Node::document_string;
    }
		else return true;
	}

  return node->dmNodeKind() == _type;
}

bool NodeTest::checkNodeName(Node::Ptr node, const DynamicContext *context) const
{
  ATQNameOrDerived::Ptr name = node->dmNodeName(context);

  const XMLCh *uri = _uri;
  if(uri == 0 && node->dmNodeKind() == Node::element_string) {
    uri = context->getDefaultElementAndTypeNS();
  }

  return (_wildcardName || (name.notNull() && XPath2Utils::equals(((ATQNameOrDerived*)name.get())->getName(), _name)))
	  && (_wildcardNamespace || (name.notNull() && XPath2Utils::equals(((ATQNameOrDerived*)name.get())->getURI(), uri)));
}


void NodeTest::setNodeName(const XMLCh* name)
{
  _name = name;
}

void NodeTest::setNodePrefix(const XMLCh* prefix)
{
  _prefix=prefix;
  _usePrefix=true;
}

void NodeTest::setNodeUri(const XMLCh* uri)
{
  _uri = uri;
  _usePrefix=false;
}

void NodeTest::setNodeType(const XMLCh *type)
{
  _type = type;
}

void NodeTest::setNameWildcard(bool value)
{
  _wildcardName = value;
}

void NodeTest::setNamespaceWildcard(bool value)
{
  _wildcardNamespace = value;
}

void NodeTest::setTypeWildcard(bool value)
{
  _wildcardType = value;
}

bool NodeTest::getHasChildren() const
{
  return _hasChildren;
}

void NodeTest::setHasChildren(bool value)
{
  _hasChildren = value;
}


const XMLCh *NodeTest::getNodeType() const
{
  return _type;
}

const XMLCh* NodeTest::getNodeUri() const
{
  return _uri;
}

const XMLCh* NodeTest::getNodePrefix() const
{
  return _prefix;
}

const XMLCh* NodeTest::getNodeName() const
{
  return _name;
}

bool NodeTest::getNameWildcard() const
{
  return _wildcardName;
}

bool NodeTest::getNamespaceWildcard() const
{
  return _wildcardNamespace;
}

bool NodeTest::getTypeWildcard() const
{
  return _wildcardType;
}


bool NodeTest::isNodeTypeSet() const
{
  return _type != 0;
}

void NodeTest::staticResolution(StaticContext *context)
{
  if(isNodePrefixSet()) {
    setNodeUri(context->getUriBoundToPrefix(getNodePrefix()));
  }
}

bool NodeTest::isNodePrefixSet() const {
	return _usePrefix;
}

SequenceType::ItemType* NodeTest::getItemType() const {
    return _itemType;
}

void NodeTest::setItemType(SequenceType::ItemType* type) {
    _itemType=type;
}

/////////////////////////////////////
// FilterResult
/////////////////////////////////////

NodeTest::FilterResult::FilterResult(const Result &toFilter, const NodeTest *nodeTest, DynamicContext *context)
  : ResultImpl(context),
    toFilter_(toFilter),
    nodeTest_(nodeTest)
{
}

Item::Ptr NodeTest::FilterResult::next(DynamicContext *context)
{
  Node::Ptr result = 0;
  while((result = toFilter_.next(context)).notNull() && !nodeTest_->filterNode(result, context)) {}

  return result;
}

std::string NodeTest::FilterResult::asString(DynamicContext *context, int indent) const
{
  std::ostringstream oss;
  std::string in(getIndent(indent));

  oss << in << "<nodetest_filter/>" << std::endl;

  return oss.str();
}
