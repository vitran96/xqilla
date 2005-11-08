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
// XQQuantified.hpp: interface for the XQQuantified class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFXQ_XQUANTIFIED_H__2B6902E9_A4FA_4AB3_9C69_08A8E77E70DA__INCLUDED_)
#define AFXQ_XQUANTIFIED_H__2B6902E9_A4FA_4AB3_9C69_08A8E77E70DA__INCLUDED_

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQFLWOR.hpp>
#include <xqilla/runtime/SingleResult.hpp>

class XQILLA_API XQQuantified : public XQFLWOR
{
public:
	typedef enum {some, every} QuantifierType;

	XQQuantified(QuantifierType qType, VectorOfVariableBinding* bindings, ASTNode* returnExpr, XPath2MemoryManager *expr);

  virtual ASTNode* staticResolution(StaticContext* context);

  QuantifierType getQuantifierType() const;

protected:
  virtual Result createResultImpl(VectorOfVariableBinding::const_iterator it, VectorOfVariableBinding::const_iterator end,
                                  DynamicContext* context, int flags = 0) const;

  class QuantifiedResult : public SingleResult
  {
  public:
    QuantifiedResult(VectorOfVariableBinding::const_iterator it, VectorOfVariableBinding::const_iterator end,
                     const XQQuantified *quantified, DynamicContext *context);

    Item::Ptr getSingleResult(DynamicContext *context) const;
    std::string asString(DynamicContext *context, int indent) const;

  private:
    const XQQuantified *_quantified;
    ExecutionBindings _ebs; // mutable
  };

	QuantifierType _qType;
};

#endif // !defined(AFXQ_XQUANTIFIED_H__2B6902E9_A4FA_4AB3_9C69_08A8E77E70DA__INCLUDED_)