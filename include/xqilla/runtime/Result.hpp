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

#ifndef _RESULT_HPP
#define _RESULT_HPP

#include <string>
#include <xercesc/util/XercesDefs.hpp>

#include <xqilla/framework/Pathan.hpp>
#include <xqilla/items/Item.hpp>
#include <xqilla/runtime/ResultImpl.hpp>
#include <xqilla/ast/StaticResolutionContext.hpp>

class Sequence;
class SequenceType;
class DynamicContext;

/** A reference counting wrapper for the lazily evaluated query result */
class PATHAN_EXPORT Result
{
public:
  Result(const Sequence &seq);
  Result(ResultImpl *impl);
  Result(const Result &o);
  Result &operator=(const Result &o);
  ~Result();

  /// Returns true if the underlying pointer is null
  bool isNull() const;

  /// Get the next item from the iterator. Returns null if the is no next value.
  Item::Ptr next(DynamicContext *context);

  /// Performs iterator specific skip of results
  void skip();

  /// Cast as a specified type. Only works properly before next() has been called.
  Result convertFunctionArg(const SequenceType* sequenceType, const StaticResolutionContext::StaticType &stype, DynamicContext* context);

  /// castAs( X("string") ) asString(). Only works properly before next() has been called.
  const XMLCh* castAsSingleString(DynamicContext* context);

  /** Matches a specified type. Only works properly before next() has been called. Throws
      XPath2TypeMatchException if the match fails. */
  Result matches(const SequenceType* sequenceType, DynamicContext* context);

  /// Perform atomization. Only works properly before next() has been called.
  Result atomize(DynamicContext* context);

  /// Returns the effective boolean value of the sequence. Only works properly before next() has been called.
  bool getEffectiveBooleanValue(DynamicContext* context);

  /// Sorts into document order
  Result sortIntoDocumentOrder(DynamicContext *context);

  /// Method to convert to a Sequence
  Sequence toSequence(DynamicContext *context);

  /// Cast operator to a Sequence. Only works properly before next() has been called.
  operator Sequence();

  /// Debug method to visualise the Result
  std::string asString(DynamicContext *context, int indent = 0) const;

private:
  ResultImpl *_impl;
};

inline Item::Ptr Result::next(DynamicContext *context)
{
  if(_impl) return _impl->next(context);
  return 0;
}

inline void Result::skip()
{
  if(_impl) _impl->skip();
}

inline Result &Result::operator=(const Result &o)
{
  if(o._impl != _impl) {
    if(_impl) _impl->decrementRefCount();
    _impl = o._impl;
    if(_impl) _impl->incrementRefCount();
  }
  return *this;
}

#endif
