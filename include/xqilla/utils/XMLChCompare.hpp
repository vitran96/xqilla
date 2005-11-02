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

#ifndef _XMLCHCOMPARE_HPP
#define _XMLCHCOMPARE_HPP

#include <xqilla/framework/Pathan.hpp>
#include <algorithm>
#include <xercesc/util/XercesDefs.hpp>

class PATHAN_EXPORT QNameSort {
public:
    bool operator() (const std::pair<XMLCh*, XMLCh *> lhs, const std::pair<XMLCh*, XMLCh *> rhs) const;
};

class PATHAN_EXPORT XMLChSort {
public:
    bool operator() (const XMLCh* lhs, const XMLCh* rhs) const;
};

#endif
