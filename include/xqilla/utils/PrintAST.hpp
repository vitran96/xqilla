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

#ifndef __PRINTAST_HPP
#define  __PRINTAST_HPP

#include <string>

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/ASTNode.hpp>
#include <xqilla/axis/NodeTest.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/operators/GeneralComp.hpp>
#include <xqilla/ast/XQTypeswitch.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/fulltext/FTOption.hpp>
#include <xqilla/fulltext/FTRange.hpp>

class XQillaExpression;
class XQFunction;
class ASTNodeImpl;
class XQLiteral;
class XQNav;
class XQParenthesizedExpr;
class XQSequence;
class XQStep;
class XQVariable;
class XQIf;
class XQInstanceOf;
class XQCastableAs;
class XQCastAs;
class XQTreatAs;
class XQOperator;
class XQContextItem;
class XQQuery;
class XQDOMConstructor;
class XQQuantified;
class XQFunctionCall;
class XQGlobalVariable;
class XQValidate;
class XQOrderingChange;
class XQAtomize;
class XPath1CompatConvertFunctionArg;
class XQPromoteUntyped;
class XQPromoteNumeric;
class XQPromoteAnyURI;
class XQDocumentOrder;
class XQPredicate;
class XQNameExpression;
class XQContentSequence;
class XQDirectName;
class XQReturn;
class DynamicContext;
class Item;

class FTContains;
class FTSelection;
class FTWords;
class FTWord;
class FTOr;
class FTAnd;
class FTMildnot;
class FTUnaryNot;
class FTOrder;
class FTDistance;
class FTDistanceLiteral;
class FTScope;
class FTContent;
class FTWindow;
class FTWindowLiteral;

class UDelete;
class URename;
class UReplace;
class UReplaceValueOf;
class UInsertAsFirst;
class UInsertAsLast;
class UInsertInto;
class UInsertAfter;
class UInsertBefore;
class UTransform;
class UApplyUpdates;

class TupleNode;
class ContextTuple;
class ForTuple;
class LetTuple;
class WhereTuple;
class OrderByTuple;

class XQILLA_API PrintAST
{
public:
  virtual ~PrintAST() {}

  static std::string print(const XQillaExpression *expr, const DynamicContext *context, int indent = 0);
  static std::string print(const XQQuery *query, const DynamicContext *context, int indent = 0);
  static std::string print(const ASTNode *item, const DynamicContext *context, int indent = 0);

  virtual std::string printASTNode(const ASTNode *item, const DynamicContext *context, int indent = 0);
  virtual std::string printFunction(const XQFunction *item, const DynamicContext *context, int indent);
  virtual std::string printLiteral(const XQLiteral *item, const DynamicContext *context, int indent);
  virtual std::string printNav(const XQNav *item, const DynamicContext *context, int indent);
  virtual std::string printParenthesized(const XQParenthesizedExpr *item, const DynamicContext *context, int indent);
  virtual std::string printSequence(const XQSequence *item, const DynamicContext *context, int indent);
  virtual std::string printStep(const XQStep *item, const DynamicContext *context, int indent);
  virtual std::string printVariable(const XQVariable *item, const DynamicContext *context, int indent);
  virtual std::string printIf(const XQIf *item, const DynamicContext *context, int indent);
  virtual std::string printInstanceOf(const XQInstanceOf *item, const DynamicContext *context, int indent);
  virtual std::string printCastableAs(const XQCastableAs *item, const DynamicContext *context, int indent);
  virtual std::string printCastAs(const XQCastAs *item, const DynamicContext *context, int indent);
  virtual std::string printTreatAs(const XQTreatAs *item, const DynamicContext *context, int indent);
  virtual std::string printOperator(const XQOperator *item, const DynamicContext *context, int indent);
  virtual std::string printContextItem(const XQContextItem *item, const DynamicContext *context, int indent);
  virtual std::string printQuantified(const XQQuantified *item, const DynamicContext *context, int indent);
  virtual std::string printTypeswitch(const XQTypeswitch *item, const DynamicContext *context, int indent);
  virtual std::string printValidate(const XQValidate *item, const DynamicContext *context, int indent);
  virtual std::string printGlobal(const XQGlobalVariable *item, const DynamicContext *context, int indent);
  virtual std::string printFunctionCall(const XQFunctionCall *item, const DynamicContext *context, int indent);
  virtual std::string printDOMConstructor(const XQDOMConstructor *item, const DynamicContext *context, int indent);
  virtual std::string printOrderingChange(const XQOrderingChange *item, const DynamicContext *context, int indent);
  virtual std::string printAtomize(const XQAtomize *item, const DynamicContext *context, int indent);
  virtual std::string printXPath1CompatConvertFunctionArg(const XPath1CompatConvertFunctionArg *item, const DynamicContext *context, int indent);
  virtual std::string printPromoteUntyped(const XQPromoteUntyped *item, const DynamicContext *context, int indent);
  virtual std::string printPromoteNumeric(const XQPromoteNumeric *item, const DynamicContext *context, int indent);
  virtual std::string printPromoteAnyURI(const XQPromoteAnyURI *item, const DynamicContext *context, int indent);
  virtual std::string printDocumentOrder(const XQDocumentOrder *item, const DynamicContext *context, int indent);
  virtual std::string printPredicate(const XQPredicate *item, const DynamicContext *context, int indent);
  virtual std::string printNameExpression(const XQNameExpression *item, const DynamicContext *context, int indent);
  virtual std::string printContentSequence(const XQContentSequence *item, const DynamicContext *context, int indent);
  virtual std::string printDirectName(const XQDirectName *item, const DynamicContext *context, int indent);
  virtual std::string printUserFunction(const XQUserFunction::Instance *item, const DynamicContext *context, int indent);
  virtual std::string printReturn(const XQReturn *item, const DynamicContext *context, int indent);

  virtual std::string printFTContains(const FTContains *item, const DynamicContext *context, int indent);
  virtual std::string printFTSelection(const FTSelection *selection, const DynamicContext *context, int indent);
  virtual std::string printFTWords(const FTWords *selection, const DynamicContext *context, int indent);
  virtual std::string printFTWord(const FTWord *selection, const DynamicContext *context, int indent);
  virtual std::string printFTOr(const FTOr *selection, const DynamicContext *context, int indent);
  virtual std::string printFTAnd(const FTAnd *selection, const DynamicContext *context, int indent);
  virtual std::string printFTMildnot(const FTMildnot *selection, const DynamicContext *context, int indent);
  virtual std::string printFTUnaryNot(const FTUnaryNot *selection, const DynamicContext *context, int indent);
  virtual std::string printFTOrder(const FTOrder *selection, const DynamicContext *context, int indent);
  virtual std::string printFTDistance(const FTDistance *selection, const DynamicContext *context, int indent);
  virtual std::string printFTDistanceLiteral(const FTDistanceLiteral *selection, const DynamicContext *context, int indent);
  virtual std::string printFTScope(const FTScope *selection, const DynamicContext *context, int indent);
  virtual std::string printFTContent(const FTContent *selection, const DynamicContext *context, int indent);
  virtual std::string printFTWindow(const FTWindow *selection, const DynamicContext *context, int indent);
  virtual std::string printFTWindowLiteral(const FTWindowLiteral *selection, const DynamicContext *context, int indent);

  virtual std::string printFTRange(const FTRange &range, const DynamicContext *context, int indent);

  virtual std::string printUDelete(const UDelete *item, const DynamicContext *context, int indent);
  virtual std::string printURename(const URename *item, const DynamicContext *context, int indent);
  virtual std::string printUReplace(const UReplace *item, const DynamicContext *context, int indent);
  virtual std::string printUReplaceValueOf(const UReplaceValueOf *item, const DynamicContext *context, int indent);
  virtual std::string printUInsertAsFirst(const UInsertAsFirst *item, const DynamicContext *context, int indent);
  virtual std::string printUInsertAsLast(const UInsertAsLast *item, const DynamicContext *context, int indent);
  virtual std::string printUInsertInto(const UInsertInto *item, const DynamicContext *context, int indent);
  virtual std::string printUInsertAfter(const UInsertAfter *item, const DynamicContext *context, int indent);
  virtual std::string printUInsertBefore(const UInsertBefore *item, const DynamicContext *context, int indent);
  virtual std::string printUTransform(const UTransform *item, const DynamicContext *context, int indent);
  virtual std::string printUApplyUpdates(const UApplyUpdates *item, const DynamicContext *context, int indent);

  virtual std::string printTupleNode(const TupleNode *item, const DynamicContext *context, int indent);
  virtual std::string printContextTuple(const ContextTuple *item, const DynamicContext *context, int indent);
  virtual std::string printForTuple(const ForTuple *item, const DynamicContext *context, int indent);
  virtual std::string printLetTuple(const LetTuple *item, const DynamicContext *context, int indent);
  virtual std::string printWhereTuple(const WhereTuple *item, const DynamicContext *context, int indent);
  virtual std::string printOrderByTuple(const OrderByTuple *item, const DynamicContext *context, int indent);

  virtual std::string printItem(const Item::Ptr item, const DynamicContext *context, int indent);
  virtual std::string printSequenceType(const SequenceType *type, const DynamicContext *context, int indent);
  virtual std::string printCase(const XQTypeswitch::Case *cse, const DynamicContext *context, int indent);

  static std::string getIndent(int indent);
  static std::string getAxisName(XQStep::Axis axis);
  static std::string getItemTestTypeName(int type);
  static std::string getOccurrenceIndicatorName(SequenceType::OccurrenceIndicator oi);
  static std::string getComparisonOperationName(GeneralComp::ComparisonOperation co);
  static std::string getFTUnitName(FTOption::FTUnit unit);
  static std::string getFTRangeTypeName(FTRange::Type type);
  static std::string printItemTypeAttrs(const SequenceType::ItemType *type, const DynamicContext *context);
};

#endif
