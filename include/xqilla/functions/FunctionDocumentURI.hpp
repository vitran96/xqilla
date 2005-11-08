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

/*

   document-uri function

*/

#ifndef _FUNCTIONDOCUMENTURI_HPP
#define _FUNCTIONDOCUMENTURI_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ConstantFoldingFunction.hpp>

class Sequence;

/* document-uri function */
class XQILLA_API FunctionDocumentURI : public ConstantFoldingFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionDocumentURI(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
	/* returns the document-URI property of the node */
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;
};

#endif

