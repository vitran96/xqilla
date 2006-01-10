/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

/*
  Factory base class
*/

#ifndef _FUNCFACTORY_HPP
#define _FUNCFACTORY_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ASTNode.hpp>

class XQILLA_API FuncFactory
{
public:
  FuncFactory();
  virtual ~FuncFactory();

  ///Create instance of a function, using FuncFactoryTemplate to determine type
  virtual ASTNode *createInstance(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr) const = 0;

  virtual const XMLCh *getName() const = 0;
  virtual const XMLCh *getURI() const = 0;
  virtual unsigned int getMinArgs() const = 0;
  virtual unsigned int getMaxArgs() const = 0;
};

#endif

