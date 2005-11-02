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

#ifndef _DATATYPELOOKUP_HPP
#define _DATATYPELOOKUP_HPP

#include <xqilla/framework/Pathan.hpp>
#include <xqilla/items/AnyAtomicType.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/RefHashTableOf.hpp>

class DatatypeFactory;
class DocumentCache;

class PATHAN_EXPORT DatatypeLookup
{
public:
  DatatypeLookup(const DocumentCache* dc, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr);
  virtual ~DatatypeLookup();

  ///returns the appropriate Datatype object
  const DatatypeFactory* lookupDatatype(AnyAtomicType::AtomicObjectType typeIndex) const;

  ///returns the appropriate Datatype object
  const DatatypeFactory* lookupDatatype(const XMLCh* typeURI, const XMLCh* typeName, bool &isPrimitive) const;

  DatatypeFactory *getAnySimpleTypeFactory() const;
  DatatypeFactory *getAnyURIFactory() const;
  DatatypeFactory *getBase64BinaryFactory() const;
  DatatypeFactory *getBooleanFactory() const;
  DatatypeFactory *getDateFactory() const;
  DatatypeFactory *getDateTimeFactory() const;
  DatatypeFactory *getDecimalFactory() const;
  DatatypeFactory *getDoubleFactory() const;
  DatatypeFactory *getDurationFactory() const;
  DatatypeFactory *getFloatFactory() const;
  DatatypeFactory *getGDayFactory() const;
  DatatypeFactory *getGMonthFactory() const;
  DatatypeFactory *getGMonthDayFactory() const;
  DatatypeFactory *getGYearFactory() const;
  DatatypeFactory *getGYearMonthFactory() const;
  DatatypeFactory *getHexBinaryFactory() const;
  DatatypeFactory *getNotationFactory() const;
  DatatypeFactory *getQNameFactory() const;
  DatatypeFactory *getStringFactory() const;
	DatatypeFactory *getTimeFactory() const;
  DatatypeFactory *getUntypedAtomicFactory() const;

private:
  DatatypeLookup & operator= (const DatatypeLookup& r);
  DatatypeLookup(const DatatypeLookup &other);

  // add a primitive datatype to the table
  void insertDatatype(DatatypeFactory *datatype);
    
private:
  DatatypeFactory *anySimpleType_;
  DatatypeFactory *anyURI_;
  DatatypeFactory *base64Binary_;
  DatatypeFactory *boolean_;
  DatatypeFactory *date_;
  DatatypeFactory *dateTime_;
  DatatypeFactory *decimal_;
  DatatypeFactory *double_;
  DatatypeFactory *duration_;
  DatatypeFactory *float_;
  DatatypeFactory *gDay_;
  DatatypeFactory *gMonth_;
  DatatypeFactory *gMonthDay_;
  DatatypeFactory *gYear_;
  DatatypeFactory *gYearMonth_;
  DatatypeFactory *hexBinary_;
  DatatypeFactory *notation_;
  DatatypeFactory *qname_;
  DatatypeFactory *string_;
	DatatypeFactory *time_;
  DatatypeFactory *untypedAtomic_;

  XERCES_CPP_NAMESPACE_QUALIFIER RefHashTableOf< DatatypeFactory > fDatatypeTable;
    
  const DocumentCache *fDocumentCache;

  XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* fMemMgr;
};

#endif 
