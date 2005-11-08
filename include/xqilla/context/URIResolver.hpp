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

#ifndef _URIRESOLVER_HPP
#define _URIRESOLVER_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xercesc/util/XercesDefs.hpp>

class DynamicContext;
class Sequence;

XERCES_CPP_NAMESPACE_BEGIN
class DOMDocument;
class DOMNodeList;
XERCES_CPP_NAMESPACE_END

/** 
 * This is an abstract class used to resolve URIs in different ways
**/
class XQILLA_API URIResolver {
  public:
    /* virtual destructor, does nothing */
    virtual ~URIResolver() {};      

    /* Resolve the given uri (and baseUri) to a Sequence (reference parameter). If the uri
       is relative, the base uri can be obtained from the context. If the uri is not handled
       by this URIResolver, returns false, otherwise returns true. */
    virtual bool resolveDocument(Sequence &result, const XMLCh* uri, DynamicContext* context) = 0;

    /* Resolve the given uri (and baseUri) to a Sequence (reference parameter). If the uri
       is relative, the base uri can be obtained from the context. If the uri is not handled
       by this URIResolver, returns false, otherwise returns true. */
    virtual bool resolveCollection(Sequence &result, const XMLCh* uri, DynamicContext* context) = 0;

    /* Resolve the default collection. If it is not defined, returns false, otherwise returns true. */
    virtual bool resolveDefaultCollection(Sequence &result, DynamicContext* context) = 0;
};
#endif // _URIRESOLVER_HPP