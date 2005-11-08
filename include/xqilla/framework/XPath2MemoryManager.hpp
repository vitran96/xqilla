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

#ifndef __XPATH2MEMORYMANAGER_HPP
#define __XPATH2MEMORYMANAGER_HPP

#include <algorithm>

#include <xqilla/framework/XQillaExport.hpp>

#include <xercesc/framework/MemoryManager.hpp>

XERCES_CPP_NAMESPACE_BEGIN
class DOMNode;
class XMLGrammarPool;
XERCES_CPP_NAMESPACE_END

class VariableStore;
class VariableTypeStore;
class FunctionLookup;
class DynamicContext;
class Collation;
class CollationHelper;
class XQillaNSResolver;
class ATDecimalOrDerived;
class StringPool;

class XQILLA_API XPath2MemoryManager : public XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager
{
public:
  virtual ~XPath2MemoryManager() {}

  /** Use with extreme caution! */
  virtual void reset() = 0;
  
  /** Returns a copy of the given string */ 
  virtual const XMLCh* getPooledString(const XMLCh *src) = 0;
  virtual const XMLCh* getPooledString(const char *src) = 0;

  // from MemoryManager
  virtual void* allocate(size_t numElements) = 0;
  virtual void deallocate(void* p) = 0;
  
  /** create a collation */
  virtual Collation* createCollation(CollationHelper* helper) = 0;

  /** create a resolver */
  virtual XQillaNSResolver* createNSResolver(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode *resolverNode) = 0;
  
  /** create a store for variables */
  virtual VariableStore* createVariableStore() = 0;

  /** create a store for variables */
  virtual VariableTypeStore* createVariableTypeStore() = 0;

  /** create a function table */
  virtual FunctionLookup* createFunctionTable() = 0;

  /** create a ATDecimalOrDerived for the given integer */
  virtual ATDecimalOrDerived* createInteger(int value) = 0;

  virtual void dumpStatistics() const = 0;
  virtual unsigned long getAllocatedObjectCount() const = 0;
  virtual unsigned long getTotalAllocatedMemory() const = 0;
  virtual const StringPool *getStringPool() const = 0;
};//XPath2MemoryManager

template <class _Tp>
class XQillaAllocator
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef _Tp* pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp& reference;
  typedef const _Tp& const_reference;
  typedef _Tp value_type;

  template <class _Tp1> struct rebind {
    typedef XQillaAllocator<_Tp1> other;
  };

  XQillaAllocator(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr)
  {
    _memMgr=memMgr;
  }

  // define a copy constructor, because we don't want to copy the singleton object
  XQillaAllocator(const XQillaAllocator<_Tp>& o)
  {
    _memMgr=o._memMgr;
  }

  pointer allocate(size_t _n, const void* = 0)
  {
    if(_n==1)
      return (pointer)_singleton;
    //std::cout << "XQillaAllocator::allocate(" << _n << ")" << std::endl;
    if(_memMgr)
      return _n != 0 ? static_cast<pointer>(_memMgr->allocate(_n*sizeof(_Tp))) : 0;
    else
      return _n != 0 ? static_cast<pointer>(malloc(_n*sizeof(_Tp))) : 0;        
  }

  void deallocate(void* _p, size_t _n)
  {
    //std::cout << "XQillaAllocator::deallocate(" << _n << ")" << std::endl;
    if(_p) {
      if(_p!=_singleton) {
        if(_memMgr)
          _memMgr->deallocate(_p);
        else
          free(_p);
      }
  }
  }

  void construct(pointer _p, const_reference _v)
  {
    new ((void *)_p) _Tp(_v); 
  }

  void destroy(pointer _p)
  {
    _p->~_Tp();
  }

  size_type max_size() const
  {
    return 0xFFFFFFFF;
  }
    
  size_type max_size(size_type) const
  {
    return 0xFFFFFFFF;
  }
    
protected:
  char _singleton[sizeof(_Tp)];
  XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* _memMgr;
};

// ---------------------------------------------------------------------------
//
//  Operator new.  Global overloaded version, lets any object be allocated on
//                 the heap owned by a MemoryManager.
//
// ---------------------------------------------------------------------------
inline void * operator new(size_t amt, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr)
{
    void *p = memMgr->allocate(amt);
    return p;
}

inline void operator delete(void* ptr, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr)
{
  memMgr->deallocate(ptr);
}

template<class TYPE>
class AutoRelease
{
public:
  AutoRelease(TYPE *p)
    : _p(p) {}
  ~AutoRelease()
  {
    _p->release();
  }

  TYPE &operator*() const
  {
    return *_p;
  }
  TYPE *operator->() const
  {
    return _p;
  }

  operator TYPE*() const
  {
    return _p;
  }

private:
  AutoRelease(const AutoRelease<TYPE> &);
  AutoRelease<TYPE> &operator=(const AutoRelease<TYPE> &);

  TYPE *_p;
};

template<class TYPE>
class AutoDelete
{
public:
  AutoDelete(TYPE *p)
    : _p(p) {}
  ~AutoDelete()
  {
    delete _p;
  }

  TYPE &operator*() const
  {
    return *_p;
  }
  TYPE *operator->() const
  {
    return _p;
  }

  operator TYPE*() const
  {
    return _p;
  }

private:
  AutoDelete(const AutoDelete<TYPE> &);
  AutoDelete<TYPE> &operator=(const AutoDelete<TYPE> &);

  TYPE *_p;
};

template<class TYPE>
class AutoDeallocate
{
public:
	AutoDeallocate(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *mmgr, size_t size = sizeof(TYPE))
		: p_(0), mmgr_(mmgr) {
		p_ = (TYPE*)mmgr_->allocate(size);
	}
	AutoDeallocate(TYPE *p, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *mmgr)
		: p_(p), mmgr_(mmgr) {}
	~AutoDeallocate()
	{
		mmgr_->deallocate((void*)p_);
	}

	TYPE &operator*() const
	{
		return *p_;
	}
	TYPE *operator->() const
	{
		return p_;
	}

	operator TYPE*() const
	{
		return p_;
	}

private:
	AutoDeallocate(const AutoDeallocate<TYPE> &);
	AutoDeallocate<TYPE> &operator=(const AutoDeallocate<TYPE> &);

	TYPE *p_;
	XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *mmgr_;
};

#endif //__XPATH2MEMORYMANAGER_HPP
