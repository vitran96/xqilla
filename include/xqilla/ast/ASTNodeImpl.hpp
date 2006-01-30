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

#ifndef _ASTNODEIMPL_HPP
#define _ASTNODEIMPL_HPP

class DynamicContext;
class Numeric;

#include <xqilla/ast/ASTNode.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/runtime/LazySequenceResult.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>

/** class which is used as base for all the different data types */
class XQILLA_API ASTNodeImpl : public ASTNode
{
public:
  ASTNodeImpl(XPath2MemoryManager* memMgr);
  virtual ~ASTNodeImpl();

  ASTNode::whichType getType(void) const;
	
  /** Returns true if this ASTNode is an instance of XQSequence or XQLiteral */
  virtual bool isConstant() const;
  /** Returns true if this ASTNode is an instance of
      XQSequence or XQLiteral. If the literal value of this ASTNode
      is a single DateOrTimeType, then hasTimezone() on it must return true,
      otherwise this method will return false. */
  virtual bool isConstantAndHasTimezone(StaticContext* context) const;

  virtual bool isSingleNumericConstant(StaticContext *context) const;

  ///calls createResult
  virtual Result collapseTree(DynamicContext* context, int flags=0) const;

  /**
   * Can be overridden by derived classes. Default implementation returns a
   * SequenceResult made from the Sequence returned by collapseTreeInternal.
   */
  virtual Result createResult(DynamicContext* context, int flags=0) const;

  /**
   * Collapse the compiled expression based on context. Default implementation
   * returns an empty sequence.
   */
  virtual Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;

  /** Calls staticResolution on the ASTNodes, then if isConstant() is true for
      all of them, and constantFold is true, returns the result of the
      constantFold() method, otherwise returns this. */
  ASTNode *resolveASTNodes(VectorOfASTNodes &dis, StaticContext *context, bool constantFold);
  /** Calls staticResolution on the ASTNodes, then if isConstantAndHasTimezone() is true for
      all of them, and constantFold is true, returns the result of the
      constantFold() method, otherwise returns this. */
  ASTNode *resolveASTNodesForDateOrTime(VectorOfASTNodes &dis, StaticContext *context, bool constantFold);
  /** Calls staticResolution on the ASTNode, then if isConstant() is true for
      it, and constantFold is true, returns the result of the
      constantFold() method, otherwise returns this. */
  ASTNode *resolveASTNode(ASTNode *&di, StaticContext *context, bool constantFold);
  /** Performs constant folding on this ASTNode. */
  ASTNode *constantFold(StaticContext *context) const;

  virtual const StaticResolutionContext &getStaticResolutionContext() const;

protected:
  void setType(ASTNode::whichType t);
  XPath2MemoryManager* getMemoryManager(void) const;

  class CollapseTreeInternalResult : public LazySequenceResult
  {
  public:
    CollapseTreeInternalResult(const ASTNodeImpl *di, int flags, DynamicContext *context);

    void getResult(Sequence &toFill, DynamicContext *context) const;
    std::string asString(DynamicContext *context, int indent) const;

  private:
    int _flags;
    const ASTNodeImpl *_di;
  };

  StaticResolutionContext _src;

private:
  whichType _type;
  XPath2MemoryManager* _memMgr;
};

#endif
