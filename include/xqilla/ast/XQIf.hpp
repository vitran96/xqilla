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

#ifndef _XQIF_HPP
#define _XQIF_HPP

#include <xqilla/framework/XQillaExport.hpp>

#include <xqilla/ast/ASTNodeImpl.hpp>

/** If function. */
class XQILLA_API XQIf : public ASTNodeImpl
{
public:
  XQIf(ASTNode* test, ASTNode* whenTrue, ASTNode* whenFalse, XPath2MemoryManager* memMgr);
  
  virtual Result createResult(DynamicContext* context, int flags=0) const;
  virtual ASTNode* staticResolution(StaticContext *context);

  const ASTNode *getTest() const;
  const ASTNode *getWhenTrue() const;
  const ASTNode *getWhenFalse() const;

  void setTest(ASTNode *item);
  void setWhenTrue(ASTNode *item);
  void setWhenFalse(ASTNode *item);

protected:
  class IfResult : public ResultImpl
  {
  public:
    IfResult(const XQIf *di, int flags, DynamicContext *context);

    Item::Ptr next(DynamicContext *context);
    std::string asString(DynamicContext *context, int indent) const;

  private:
    int _flags;
    const XQIf *_di;
    Result _results;
  };

  ASTNode* _test,* _whenTrue,* _whenFalse;
};

#endif // _XQIF_HPP

