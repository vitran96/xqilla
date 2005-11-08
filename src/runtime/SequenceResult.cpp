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

#include "../config/xqilla_config.h"
#include <sstream>
#include <xqilla/runtime/SequenceResult.hpp>

SequenceResult::SequenceResult(const Sequence &seq)
  : ResultImpl(0),
    seq_(seq)
{
  it_ = seq_.begin();
}

Item::Ptr SequenceResult::next(DynamicContext *context)
{
  if(it_ == seq_.end()) {
    return 0;
  }
  else {
    return *(it_++);
  }
}

Sequence SequenceResult::toSequence(DynamicContext *context)
{
  return seq_;
}

std::string SequenceResult::asString(DynamicContext *context, int indent) const
{
  std::ostringstream oss;
  std::string in(getIndent(indent));

  oss << in << "<sequence/>" << std::endl;

  return oss.str();
}