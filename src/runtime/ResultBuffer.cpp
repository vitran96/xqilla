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

#include "../config/pathan_config.h"
#include <sstream>

#include <xqilla/runtime/ResultBuffer.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/context/DynamicContext.hpp>

#include "ResultBufferImpl.hpp"

ResultBuffer::ResultBuffer(const Result &result)
  : _impl(new ResultBufferImpl(result))
{
  _impl->incrementRefCount();
}

ResultBuffer::ResultBuffer(ResultBufferImpl *impl)
  : _impl(impl)
{
  if(_impl) _impl->incrementRefCount();
}

ResultBuffer::ResultBuffer(const ResultBuffer &o)
  : _impl(o._impl)
{
  if(_impl) _impl->incrementRefCount();
}

ResultBuffer &ResultBuffer::operator=(const ResultBuffer &o)
{
  if(o._impl != _impl) {
    if(_impl) _impl->decrementRefCount();
    _impl = o._impl;
    if(_impl) _impl->incrementRefCount();
  }
  return *this;
}

ResultBuffer::~ResultBuffer()
{
  if(_impl) _impl->decrementRefCount();
}

Result ResultBuffer::createResult(DynamicContext *context) const
{
  if(_impl) return new BufferedResult(_impl, context);
  else return Result(0);
}

ResultBuffer::BufferedResult::BufferedResult(ResultBufferImpl *impl, DynamicContext *context)
  : ResultImpl(context),
    _impl(impl),
    _pos(0)
{
  _impl->incrementRefCount();
}

ResultBuffer::BufferedResult::~BufferedResult()
{
  _impl->decrementRefCount();
}

Item::Ptr ResultBuffer::BufferedResult::next(DynamicContext *context)
{
  return _impl->item(_pos++, context);
}

std::string ResultBuffer::BufferedResult::asString(DynamicContext *context, int indent) const
{
  std::ostringstream oss;
  std::string in(getIndent(indent));

  oss << in << "<bufferedresult/>" << std::endl;

  return oss.str();
}
