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

#include <xqilla/update/UInsertAsFirst.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/items/Node.hpp>
#include <xqilla/ast/XQTreatAs.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/exceptions/StaticErrorException.hpp>
#include <xqilla/exceptions/XPath2TypeMatchException.hpp>
#include <xqilla/exceptions/ASTException.hpp>
#include <xqilla/update/PendingUpdateList.hpp>
#include <xqilla/ast/XQDOMConstructor.hpp>

UInsertAsFirst::UInsertAsFirst(ASTNode *source, ASTNode *target, XPath2MemoryManager* memMgr)
  : ASTNodeImpl(memMgr),
    source_(source),
    target_(target)
{
  setType(ASTNode::UINSERT_AS_FIRST);
}

ASTNode* UInsertAsFirst::staticResolution(StaticContext *context)
{
  XPath2MemoryManager *mm = context->getMemoryManager();

  source_ = new (mm) XQContentSequence(source_, /*copy*/true, mm);
  source_->setLocationInfo(this);
  source_ = source_->staticResolution(context);

  SequenceType *targetType = new (mm) SequenceType(new (mm) SequenceType::ItemType(SequenceType::ItemType::TEST_NODE),
                                                   SequenceType::EXACTLY_ONE);
  targetType->setLocationInfo(this);
  target_ = new (mm) XQTreatAs(target_, targetType, mm);
  target_->setLocationInfo(this);
  target_ = target_->staticResolution(context);

  return this;
}

ASTNode *UInsertAsFirst::staticTyping(StaticContext *context)
{
  _src.clear();

  source_ = source_->staticTyping(context);
  _src.add(source_->getStaticResolutionContext());

  if(source_->getStaticResolutionContext().isUpdating()) {
    XQThrow(StaticErrorException,X("UInsertAsFirst::staticTyping"),
            X("It is a static error for the source expression of an insert expression "
              "to be an updating expression [err:XUST0001]"));
  }

  target_ = target_->staticTyping(context);
  _src.add(target_->getStaticResolutionContext());

  if(target_->getStaticResolutionContext().isUpdating()) {
    XQThrow(StaticErrorException,X("UInsertAsFirst::staticTyping"),
            X("It is a static error for the target expression of an insert expression "
              "to be an updating expression [err:XUST0001]"));
  }

  _src.updating(true);
  return this;
}

PendingUpdateList UInsertAsFirst::createUpdateList(DynamicContext *context) const
{
  Node::Ptr node = (Node*)target_->collapseTree(context)->next(context).get();

  if(node->dmNodeKind() != Node::element_string &&
     node->dmNodeKind() != Node::document_string)
    XQThrow(XPath2TypeMatchException,X("UInsertAsFirst::createUpdateList"),
            X("It is a type error for the target expression of an insert as first expression not to be a single element "
              "or document [err:TBD]"));

  Sequence alist(context->getMemoryManager());
  Sequence clist(context->getMemoryManager());

  Result value = source_->collapseTree(context);
  Item::Ptr item;
  while((item = value->next(context)).notNull()) {
    if(((Node*)item.get())->dmNodeKind() == Node::attribute_string) {
      if(!clist.isEmpty())
        XQThrow(ASTException,X("UInsertAsFirst::createUpdateList"),
                X("Attribute nodes must occur before other nodes in the source expression for an insert as first expression [err:TBD]"));
      alist.addItem(item);
    }
    else
      clist.addItem(item);
  }

  PendingUpdateList result;

  if(!alist.isEmpty()) {
    result.addUpdate(PendingUpdate(PendingUpdate::INSERT_ATTRIBUTES, node, alist, this));
  }
  if(!clist.isEmpty()) {
    result.addUpdate(PendingUpdate(PendingUpdate::INSERT_INTO_AS_FIRST, node, clist, this));
  }

  return result;
}
