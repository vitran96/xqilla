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

#ifndef _RESULTBUFFER_HPP
#define _RESULTBUFFER_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/runtime/ResultImpl.hpp>

class Result;
class ResultBufferImpl;
class Item;

/** A reference counting wrapper for the result buffer */
class XQILLA_API ResultBuffer
{
public:
  ResultBuffer(const Result &result);
  ResultBuffer(ResultBufferImpl *impl);
  ResultBuffer(const ResultBuffer &o);
  ResultBuffer &operator=(const ResultBuffer &o);
  ~ResultBuffer();

  /// Creates a result that returns the same items as the one used to construct this buffer
  Result createResult(DynamicContext *context) const;

  bool isNull() const
  {
    return _impl == 0;
  }

private:
  class BufferedResult : public ResultImpl
  {
  public:
    BufferedResult(ResultBufferImpl *impl, DynamicContext *context);
    ~BufferedResult();

    Item::Ptr next(DynamicContext *context);
    std::string asString(DynamicContext *context, int indent) const;
  private:
    ResultBufferImpl *_impl;
    unsigned int _pos;
  };

  ResultBufferImpl *_impl;
};

#endif