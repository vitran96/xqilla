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

#if !defined(AFXQ_COLLATION_H__6BA76C4A_0A5B_480B_9870_86A89A118100__INCLUDED_)
#define AFXQ_COLLATION_H__6BA76C4A_0A5B_480B_9870_86A89A118100__INCLUDED_

#include <xqilla/framework/XQillaExport.hpp>
#include <xercesc/util/XercesDefs.hpp>

class Sequence;
class DynamicContext;

class XQILLA_API Collation
{
public:
  virtual ~Collation() {};

  virtual const XMLCh* getCollationName() const = 0;
  virtual Sequence sort(Sequence data, const DynamicContext* context) const = 0;
  virtual int compare(const XMLCh* const string1, const XMLCh* const string2) const = 0;

protected:
  Collation() {}
};

#endif // !defined(AFXQ_COLLATION_H__6BA76C4A_0A5B_480B_9870_86A89A118100__INCLUDED_)