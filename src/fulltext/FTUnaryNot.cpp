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

#include "../config/xqilla_config.h"
#include <xqilla/fulltext/FTUnaryNot.hpp>
#include <xqilla/context/DynamicContext.hpp>

FTUnaryNot::FTUnaryNot(FTSelection *arg, XPath2MemoryManager *memMgr)
    : FTSelection(FTSelection::UNARY_NOT, memMgr),
      arg_(arg)
{
}

FTSelection *FTUnaryNot::staticResolution(StaticContext *context)
{
  arg_ = arg_->staticResolution(context);
  src_.add(arg_->getStaticResolutionContext());

  return this;
}

FTSelection *FTUnaryNot::optimize(FTContext *ftcontext, bool execute) const
{
  XPath2MemoryManager *mm = ftcontext->context->getMemoryManager();

  FTSelection *newarg = arg_->optimize(ftcontext, execute);
  if(newarg == 0) return 0;

  return new (mm) FTUnaryNot(newarg, mm);
}

AllMatches::Ptr FTUnaryNot::execute(FTContext *ftcontext) const
{
  return new FTUnaryNotMatches(arg_->execute(ftcontext));
}

Match::Ptr FTUnaryNotMatches::next(DynamicContext *context)
{
  // TBD need to check for StringInclude / StringExclude contradictions

  if(toDo_) {
    toDo_ = false;

    Match::Ptr result = new Match();

    if(arg_.notNull()) {
      Match::Ptr match(0);
      while((match = arg_->next(context)).notNull()) {
        result->addStringExcludes(match->getStringIncludes());
        result->addStringIncludes(match->getStringExcludes());
      }
    }

    arg_ = 0;
    return result;
  }
  return 0;
}