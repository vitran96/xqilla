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

//////////////////////////////////////////////////////////////////////
// XQVariableBinding.hpp: interface for the XQVariableBinding class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFXQ_XQVARIABLEBINDING_H__4EDA7D8A_78E2_476F_80DA_029C3E4B9AC8__INCLUDED_)
#define AFXQ_XQVARIABLEBINDING_H__4EDA7D8A_78E2_476F_80DA_029C3E4B9AC8__INCLUDED_

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/ASTNode.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>

class XQILLA_API XQVariableBinding
{
public:
	typedef enum
	{
		letBinding,
		forBinding
	} BindingType;

  XQVariableBinding(XPath2MemoryManager* memMgr, BindingType bindingType, const XMLCh* variable, ASTNode* allValues, const XMLCh* positionalVariable=NULL, SequenceType* seqType=NULL);
  XQVariableBinding(XPath2MemoryManager* memMgr, const XQVariableBinding &o);

  void addWhereCondition(ASTNode *clause);

	BindingType _bindingType;

	const XMLCh *_variable, *_vURI, *_vName;
  const XMLCh *_positionalVariable, *_pURI, *_pName;

  StaticResolutionContext _src, _pSrc;

  SequenceType* _seqType;

	ASTNode* _allValues;

  bool _valuesResultMustBeRecalculated;
  bool _needsNewScope;

  ASTNode *_where;

	unsigned long _line;
	const XMLCh* _file;

  XPath2MemoryManager *_memMgr;

private:
  XQVariableBinding(const XQVariableBinding &o);
};

typedef std::vector<XQVariableBinding*, XQillaAllocator<XQVariableBinding*> > VectorOfVariableBinding;

#endif // !defined(AFXQ_XQVARIABLEBINDING_H__4EDA7D8A_78E2_476F_80DA_029C3E4B9AC8__INCLUDED_)