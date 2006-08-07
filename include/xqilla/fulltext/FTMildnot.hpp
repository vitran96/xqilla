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

#ifndef _FTMILDNOT_HPP
#define _FTMILDNOT_HPP

#include <xqilla/fulltext/FTSelection.hpp>

#include <set>

class XQILLA_API FTMildnot : public FTSelection
{
public:
  FTMildnot(FTSelection *left, FTSelection *right, XPath2MemoryManager *memMgr);

  virtual FTSelection *staticResolution(StaticContext *context);
  virtual FTSelection *optimize(FTContext *context, bool execute) const;
  virtual AllMatches::Ptr execute(FTContext *ftcontext) const;

  const FTSelection *getLeft() const { return left_; }
  const FTSelection *getRight() const { return right_; }

private:
  FTSelection *left_, *right_;
};

class FTMildnotMatches : public AllMatches
{
public:
  FTMildnotMatches(const AllMatches::Ptr &left, const AllMatches::Ptr &right)
    : left_(left), right_(right) {}
  Match::Ptr next(DynamicContext *context);

private:
  AllMatches::Ptr left_;
  AllMatches::Ptr right_;
  std::set<unsigned int> badTokens_;
};

#endif