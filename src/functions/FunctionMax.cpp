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
#include <xqilla/functions/FunctionMax.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/ast/XQSequence.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/impl/CodepointCollation.hpp>
#include "../operators/TotalOrderComparison.hpp"
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/exceptions/IllegalArgumentException.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xercesc/validators/schema/SchemaSymbols.hpp>

const XMLCh FunctionMax::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_m, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_a, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_x, 
  XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionMax::minArgs = 1;
const unsigned int FunctionMax::maxArgs = 2;

/**
 * fn:max($arg as xdt:anyAtomicType*) as xdt:anyAtomicType?
 * fn:max($arg as xdt:anyAtomicType*, $collation as string) as xdt:anyAtomicType?
**/

FunctionMax::FunctionMax(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : AggregateFunction(name, minArgs, maxArgs, "anyAtomicType*, string", args, memMgr)
{
  // TBD - could do better here - jpcs
  _src.getStaticType().flags = StaticResolutionContext::NUMERIC_TYPE | StaticResolutionContext::OTHER_TYPE;
}

Sequence FunctionMax::collapseTreeInternal(DynamicContext* context, int flags) const
{
    XPath2MemoryManager* memMgr = context->getMemoryManager();

    Sequence sequence(memMgr);
    try {
        sequence = validateSequence(getParamNumber(1,context,ASTNode::UNORDERED), context);
    } catch (IllegalArgumentException &e) {
        DSLthrow(IllegalArgumentException, X("FunctionMax::collapseTreeInternal"), X("Invalid argument to fn:max() function"));
    }

    // Return the empty sequence if the sequence is empty
    if(sequence.isEmpty()) {
        return Sequence(memMgr);
    }
    if(sequence.getLength()==1 && isNumericNaN(sequence.first()))
        return sequence;

    Collation* collation=NULL;
    if (getNumArgs()>1) {
        Sequence collArg = getParamNumber(2,context);
        const XMLCh* collName = collArg.first()->asString(context);
        try {
            context->getItemFactory()->createAnyURI(collName, context);
        } catch(XPath2ErrorException &e) {
            DSLthrow(FunctionException, X("FunctionMax::collapseTreeInternal"), X("Invalid collationURI"));  
        }
        collation=context->getCollation(collName);
        if (collation==NULL)
            DSLthrow(FunctionException,X("FunctionMax::collapseTreeInternal"),X("Collation object is not available"));
    }
    else
        collation=context->getDefaultCollation();
    if(collation==NULL)
        collation=context->getCollation(CodepointCollation::getCodepointCollationName());

    Sequence::iterator i = sequence.begin();
    Item::Ptr maxItem = *i;
    ++i;
    for (; i != sequence.end(); ++i) {
        if(((AnyAtomicType*)(const Item*)(*i))->getPrimitiveTypeIndex() == AnyAtomicType::STRING) {
          if(collation->compare((*i)->asString(context),maxItem->asString(context))>0) {
            maxItem = *i;
          }
        } else {
            ATBooleanOrDerived::Ptr greater;
            VectorOfASTNodes gtArgs = VectorOfASTNodes(XQillaAllocator<ASTNode*>(memMgr));
            XQSequence seq1(*i, context, memMgr);
            gtArgs.push_back(&seq1);
            XQSequence seq2(maxItem, context, memMgr);
            gtArgs.push_back(&seq2);
            TotalOrderComparison gt(gtArgs, true, memMgr);
            try {
                greater = (const ATBooleanOrDerived::Ptr )gt.collapseTree(context).next(context);
            } catch (IllegalArgumentException &e) {
                DSLthrow(IllegalArgumentException, X("FunctionMax::collapseTreeInternal"), X("Invalid argument to fn:max() function"));
            } catch (XPath2ErrorException &e) {
                DSLthrow(IllegalArgumentException, X("FunctionMax::collapseTreeInternal"), X("Invalid argument to fn:max() function"));
            }
            if(((const ATBooleanOrDerived*)greater)->isTrue()) {
              maxItem = *i;
            }
        }
    }
    return Sequence(maxItem, memMgr);
}