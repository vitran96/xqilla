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

#ifndef AFXQ_XQUERYPRINTDATAITEMTREE_HPP__FAA9543A_2F10_49A4_93D2_857E2I8C48E3__INCLUDED_
#define	AFXQ_XQUERYPRINTDATAITEMTREE_HPP__FAA9543A_2F10_49A4_93D2_857E2I8C48E3__INCLUDED_

#include <xqilla/utils/PrintDataItemTree.hpp>

#include <xqilla/ast/XQTypeswitch.hpp>
#include <xqilla/functions/XQUserFunction.hpp>

class XQQuery;
class XQDebugHook;
class XQDOMConstructor;
class XQFLWOR;
class XQVariableBinding;
class XQSort;
class XQQuantified;
class XQFunctionCall;
class XQGlobalVariable;
class XQValidate;
class XQOrderingChange;

class XQENGINE_API XQueryPrintDataItemTree : public PrintDataItemTree
{
public:
	static std::string print(const PathanExpression *expr, const DynamicContext *context, int indent = 0);
	static std::string print(const XQQuery *query, const DynamicContext *context, int indent = 0);
	static std::string print(const ASTNode *item, const DynamicContext *context, int indent = 0);

	virtual std::string printX(const ASTNode *item, const DynamicContext *context, int indent);
	virtual std::string printDebugHook(const XQDebugHook *item, const DynamicContext *context, int indent);
	virtual std::string printFLWOR(const XQFLWOR *item, const DynamicContext *context, int indent);
	virtual std::string printFLWORQuantified(const XQQuantified *item, const DynamicContext *context, int indent);
	virtual std::string printTypeswitch(const XQTypeswitch *item, const DynamicContext *context, int indent);
	virtual std::string printValidate(const XQValidate *item, const DynamicContext *context, int indent);
	virtual std::string printGlobal(const XQGlobalVariable *item, const DynamicContext *context, int indent);
	virtual std::string printFunctionCall(const XQFunctionCall *item, const DynamicContext *context, int indent);
	virtual std::string printDOMConstructor(const XQDOMConstructor *item, const DynamicContext *context, int indent);
	virtual std::string printOrderingChange(const XQOrderingChange *item, const DynamicContext *context, int indent);
	virtual std::string printUserFunction(const XQUserFunction::XQFunctionEvaluator *item, const DynamicContext *context, int indent);

	virtual std::string printXQVariableBinding(const XQVariableBinding *binding, const DynamicContext *context, int indent);
	virtual std::string printSort(const XQSort *sort, const DynamicContext *context, int indent);
	virtual std::string printClause(const XQTypeswitch::Clause *clause, const DynamicContext *context, int indent);
};

#endif
