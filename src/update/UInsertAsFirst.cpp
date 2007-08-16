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

static const XMLCh err_XUTY0005[] = { 'e', 'r', 'r', ':', 'X', 'U', 'T', 'Y', '0', '0', '0', '5', 0 };
static const XMLCh err_XUDY0027[] = { 'e', 'r', 'r', ':', 'X', 'U', 'D', 'Y', '0', '0', '2', '7', 0 };

ASTNode* UInsertAsFirst::staticResolution(StaticContext *context)
{
  XPath2MemoryManager *mm = context->getMemoryManager();

  source_ = new (mm) XQContentSequence(source_, mm);
  source_->setLocationInfo(this);
  source_ = source_->staticResolution(context);

  SequenceType *targetType1 = new (mm) SequenceType(new (mm) SequenceType::ItemType(SequenceType::ItemType::TEST_ANYTHING),
                                                    SequenceType::PLUS);
  targetType1->setLocationInfo(this);

  SequenceType *targetType2 = new (mm) SequenceType(new (mm) SequenceType::ItemType(SequenceType::ItemType::TEST_NODE),
                                                    SequenceType::EXACTLY_ONE);
  targetType2->setLocationInfo(this);

  target_ = new (mm) XQTreatAs(target_, targetType1, mm, err_XUDY0027);
  target_->setLocationInfo(this);
  target_ = target_->staticResolution(context);

  target_ = new (mm) XQTreatAs(target_, targetType2, mm, err_XUTY0005);
  target_->setLocationInfo(this);
  target_ = target_->staticResolution(context);

  return this;
}

ASTNode *UInsertAsFirst::staticTyping(StaticContext *context)
{
  _src.clear();

  source_ = source_->staticTyping(context);
  _src.add(source_->getStaticAnalysis());

  if(source_->getStaticAnalysis().isUpdating()) {
    XQThrow(StaticErrorException,X("UInsertAsFirst::staticTyping"),
            X("It is a static error for the source expression of an insert expression "
              "to be an updating expression [err:XUST0001]"));
  }

  target_ = target_->staticTyping(context);
  _src.add(target_->getStaticAnalysis());

  if(target_->getStaticAnalysis().isUpdating()) {
    XQThrow(StaticErrorException,X("UInsertAsFirst::staticTyping"),
            X("It is a static error for the target expression of an insert expression "
              "to be an updating expression [err:XUST0001]"));
  }

  _src.updating(true);
  return this;
}

PendingUpdateList UInsertAsFirst::createUpdateList(DynamicContext *context) const
{
  Node::Ptr node = (Node*)target_->createResult(context)->next(context).get();

  if(node->dmNodeKind() != Node::element_string &&
     node->dmNodeKind() != Node::document_string)
    XQThrow(XPath2TypeMatchException,X("UInsertAsFirst::createUpdateList"),
            X("It is a type error for the target expression of an insert as first expression not to be a single element "
              "or document [err:XUTY0005]"));

  Sequence alist(context->getMemoryManager());
  Sequence clist(context->getMemoryManager());

  Result value = source_->createResult(context);
  Item::Ptr item;
  while((item = value->next(context)).notNull()) {
    if(((Node*)item.get())->dmNodeKind() == Node::attribute_string) {
      if(!clist.isEmpty())
        XQThrow(ASTException,X("UInsertAsFirst::createUpdateList"),
                X("Attribute nodes must occur before other nodes in the source expression for an insert as first expression [err:XUTY0004]"));
      alist.addItem(item);
    }
    else
      clist.addItem(item);
  }

  PendingUpdateList result;

  if(!alist.isEmpty()) {
    // 3. If $alist is not empty and into is specified, the following checks are performed:
    //    a. $target must be an element node [err:XUTY0022].
    if(node->dmNodeKind() == Node::document_string)
      XQThrow(XPath2TypeMatchException,X("UInsertInto::createUpdateList"),
              X("It is a type error if an insert expression specifies the insertion of an attribute node into a document node [err:XUTY0022]"));
    //    b. No attribute node in $alist may have a QName whose implied namespace binding conflicts with a namespace
    //       binding in the "namespaces" property of $target [err:XUDY0023].  
    // TBD make this check - jpcs
    result.addUpdate(PendingUpdate(PendingUpdate::INSERT_ATTRIBUTES, node, alist, this));
  }
  if(!clist.isEmpty()) {
    result.addUpdate(PendingUpdate(PendingUpdate::INSERT_INTO_AS_FIRST, node, clist, this));
  }

  return result;
}

