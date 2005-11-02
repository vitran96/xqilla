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
#include <assert.h>
#include <sstream>

#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xqilla/ast/DataItemCastableAs.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/parser/QName.hpp>
#include <xqilla/exceptions/TypeErrorException.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/Item.hpp>
#include <xqilla/items/AnyAtomicType.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/PathanFactory.hpp>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DataItemCastableAs::DataItemCastableAs(DataItem* expr, SequenceType* exprType, XPath2MemoryManager* memMgr)
  : DataItemImpl(memMgr),
  _expr(expr),
  _exprType(exprType)
{
	setType(DataItem::CASTABLE_AS);
}

Result DataItemCastableAs::createResult(DynamicContext* context, int flags) const
{
  return new CastableAsResult(this, context);
}

DataItem* DataItemCastableAs::staticResolution(StaticContext *context) {
  return resolveDataItem(_expr, context, true);
}

const DataItem *DataItemCastableAs::getExpression() const {
  return _expr;
}

const SequenceType *DataItemCastableAs::getSequenceType() const {
  return _exprType;
}

void DataItemCastableAs::setExpression(DataItem *item) {
  _expr = item;
}

DataItemCastableAs::CastableAsResult::CastableAsResult(const DataItemCastableAs *di, DynamicContext *context)
  : SingleResult(context),
    _di(di)
{
}

Item::Ptr DataItemCastableAs::CastableAsResult::getSingleResult(DynamicContext *context) const
{
  // The semantics of the cast expression are as follows:
  //    1. Atomization is performed on the input expression.
	Result toBeCasted(_di->getExpression()->collapseTree(context, DataItem::RETURN_TWO|DataItem::UNORDERED));

  if(_di->getExpression()->getStaticResolutionContext().getStaticType().flags & StaticResolutionContext::NODE_TYPE) {
    toBeCasted = toBeCasted.atomize(context);
  }

  const Item::Ptr first = toBeCasted.next(context);

  bool result = false;
	if(first == NULLRCP) {
    //    3. If the result of atomization is an empty sequence:
    //       1. If ? is specified after the target type, the result of the cast expression is an empty sequence.
    //       2. If ? is not specified after the target type, a type error is raised.[err:XP0004][err:XP0006]
    result = _di->getSequenceType()->getOccurrenceIndicator() != SequenceType::EXACTLY_ONE;
  }
  else {
    const Item::Ptr second = toBeCasted.next(context);

    //    2. If the result of atomization is a sequence of more than one atomic value, a type error is raised.[err:XP0004][err:XP0006]
    if(second != NULLRCP) {
      result = false;
    }
    else {
      if(_di->getSequenceType()->getItemTestType() != SequenceType::ItemType::TEST_ATOMIC_TYPE)
        DSLthrow(TypeErrorException,X("DataItemCastableAs::collapseTreeInternal"),X("Cannot cast to a non atomic type"));
      //    4. If the result of atomization is a single atomic value, the result of the cast expression depends on the input type and the target type.
      //       The normative definition of these rules is given in [XQuery 1.0 and XPath 2.0 Functions and Operators].
      result = ((const AnyAtomicType::Ptr)first)->castable(_di->getSequenceType()->getTypeURI(context), _di->getSequenceType()->getConstrainingType()->getName(), context);
    }
  }
  return (const Item::Ptr)context->getPathanFactory()->createBoolean(result, context);
}

std::string DataItemCastableAs::CastableAsResult::asString(DynamicContext *context, int indent) const
{
  std::ostringstream oss;
  std::string in(getIndent(indent));

  oss << in << "<castableas/>" << std::endl;

  return oss.str();

}
