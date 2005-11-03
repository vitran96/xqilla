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
// XQDebugCallback.h: interface for debugging
//////////////////////////////////////////////////////////////////////

#if !defined(AFXQ_XQDEBUGCALLBACK_H__446AD191_E9D0_4658_BD8C_032D29DA125F__INCLUDED_)
#define AFXQ_XQDEBUGCALLBACK_H__446AD191_E9D0_4658_BD8C_032D29DA125F__INCLUDED_

#include <xqilla/framework/XQEngine.hpp>
#include <xercesc/util/XercesDefs.hpp>

class Sequence;
class DynamicContext;

XERCES_CPP_NAMESPACE_BEGIN
    class DOMNode;
XERCES_CPP_NAMESPACE_END

class XQENGINE_API XQDebugCallback
{
public:
    virtual void IsBreakPointHit(DynamicContext* context, const XMLCh* file, unsigned int nLine) = 0;
    virtual void EnterFunction(DynamicContext* context, const XMLCh* file, const XMLCh* fnName, unsigned int nLine, unsigned int nColumn) = 0;
    virtual void ExitFunction(DynamicContext* context, const XMLCh* fnName) = 0;
    virtual void ReportClonedNode(DynamicContext* context, const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* original, const XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* clone) = 0;
    virtual void ReportResult(DynamicContext* context, const XMLCh* file, unsigned int nLine, unsigned int nColumn, Sequence& result) = 0;
    virtual void ReportFirstError(DynamicContext* context, const XMLCh* error, const XMLCh* file, unsigned int nLine) = 0;

    virtual void NotifyQueryBegin(DynamicContext* context, const XMLCh* query) = 0;
    virtual void NotifyQueryEnd(DynamicContext* context, Sequence& result) = 0;
};

#endif // !defined(AFXQ_XQDEBUGCALLBACK_H__446AD191_E9D0_4658_BD8C_032D29DA125F__INCLUDED_)
