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

#ifndef _FTWORDS_HPP
#define _FTWORDS_HPP

#include <xqilla/fulltext/FTSelection.hpp>
#include <xqilla/runtime/Result.hpp>

class ASTNode;

class XQILLA_API FTWords : public FTSelection
{
public:
  /// Enumeration representing the way to match words and phrases
  enum FTAnyallOption {
    ANY,
    ANY_WORD,
    ALL,
    ALL_WORDS,
    PHRASE
  };

  FTWords(ASTNode *expr, FTAnyallOption option, XPath2MemoryManager *memMgr);

  virtual FTSelection *staticResolution(StaticContext *context);
  virtual FTSelection *optimize(FTContext *context, bool execute) const;
  virtual AllMatches::Ptr execute(FTContext *ftcontext) const;

  const ASTNode *getExpr() const { return expr_; }
  FTAnyallOption getOption() const { return option_; }

private:
  static FTSelection *optimizeAnyWord(Result strings, FTContext *ftcontext);
  static FTSelection *optimizeAllWords(Result strings, FTContext *ftcontext);
  static FTSelection *optimizePhrase(Result strings, FTContext *ftcontext);
  static FTSelection *optimizeAny(Result strings, FTContext *ftcontext);
  static FTSelection *optimizeAll(Result strings, FTContext *ftcontext);

  ASTNode *expr_;
  FTAnyallOption option_;
};

class XQILLA_API FTWord : public FTSelection
{
public:
  FTWord(const XMLCh *queryString, XPath2MemoryManager *memMgr);

  virtual FTSelection *staticResolution(StaticContext *context);
  virtual FTSelection *optimize(FTContext *context, bool execute) const;
  virtual AllMatches::Ptr execute(FTContext *ftcontext) const;

  const XMLCh *getQueryString() const { return queryString_; }

private:
  const XMLCh *queryString_;
};

class FTStringSearchMatches : public AllMatches
{
public:
  FTStringSearchMatches(const XMLCh *queryString, FTContext *ftcontext);
  Match::Ptr next(DynamicContext *context);
  AllMatches::Ptr optimize();

private:
  const XMLCh *queryString_;
  unsigned int queryPos_;
  TokenStream::Ptr tokenStream_;
};

#endif