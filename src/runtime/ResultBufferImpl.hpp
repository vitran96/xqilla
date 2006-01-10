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

#ifndef _RESULTBUFFERIMPL_HPP
#define _RESULTBUFFERIMPL_HPP

#include <vector>

#include <xqilla/runtime/Result.hpp>

/** A buffer for lazily evaluated query results. This object is not thread safe */
class ResultBufferImpl
{
public:
  /**
   * Do not allocate this object from a memory manager!
   * It must be created using the heap.
   */
  ResultBufferImpl(const Result &result);
  ~ResultBufferImpl();

  /// Increment the reference count
  void incrementRefCount();
  /// Decrement the reference count, deleting if it becomes zero
  void decrementRefCount();

  const Item::Ptr item(unsigned int index, DynamicContext *context);

private:
  ResultBufferImpl(const ResultBufferImpl &);
  ResultBufferImpl &operator=(const ResultBufferImpl &);

  typedef std::vector<Item::Ptr> ItemList;

  unsigned int _refCount;
  Result _result;
  bool _done;
  ItemList _items;
};

#endif
