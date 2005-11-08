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

#ifndef _QNAME_HPP
#define _QNAME_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <vector>

/*
Represents a Qualified name. Built in the parser.
 */
class XQILLA_API QualifiedName {

public:
	QualifiedName(const XMLCh* qualifiedName, XPath2MemoryManager* memMgr);
	// This constructor should be used on persistent strings (no memory manager involved)
	QualifiedName(const XMLCh* const prefix, const XMLCh* const name);
	QualifiedName(const XMLCh* fullName);
	~QualifiedName();

	const XMLCh* getPrefix() const;
	const XMLCh* getName() const;

	const XMLCh* getFullName(XPath2MemoryManager* memMgr) const;

private:
	const XMLCh* _prefix,*_name;
  bool _bDeleteStrings;
};

#endif
