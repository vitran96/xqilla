/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Oracle. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#ifndef _STATICANALYSIS_HPP
#define _STATICANALYSIS_HPP

#include <string>

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/StaticType.hpp>

#include <xercesc/util/RefHash2KeysTableOf.hpp>
#include <xercesc/util/StringPool.hpp>

#include <vector>

class XPath2MemoryManager;

typedef XERCES_CPP_NAMESPACE_QUALIFIER RefHash2KeysTableOf<int> VariableAccessSet;
typedef XERCES_CPP_NAMESPACE_QUALIFIER RefHash2KeysTableOfEnumerator<int> VariableAccessSetEnumerator;

/**
 * Records access to various parts of the context during static resolution.
 */
class XQILLA_API StaticAnalysis
{
public:
  StaticAnalysis(XPath2MemoryManager* memMgr);
  StaticAnalysis(const StaticAnalysis &o, XPath2MemoryManager* memMgr);

  void copy(const StaticAnalysis &o);

  /// Clears all the information in this StaticAnalysis
  void clear();

  /** Overrides all the other flags, and never allows this sub-expression
      to be constant folded. */
  void forceNoFolding(bool value);
  bool isNoFoldingForced() const;

  void contextItemUsed(bool value);
  void contextPositionUsed(bool value);
  void contextSizeUsed(bool value);
  bool isContextItemUsed() const;
  bool isContextPositionUsed() const;
  bool isContextSizeUsed() const;
  /** Returns true if any of the context item flags have been used */
  bool areContextFlagsUsed() const;

  void currentTimeUsed(bool value);
  void implicitTimezoneUsed(bool value);

  void availableDocumentsUsed(bool value);
  void availableCollectionsUsed(bool value);
  bool areDocsOrCollectionsUsed() const;

  void variableUsed(const XMLCh *namespaceURI, const XMLCh *name);
  bool removeVariable(const XMLCh *namespaceURI, const XMLCh *name);
  bool isVariableUsed(const XMLCh *namespaceURI, const XMLCh *name) const;
  std::vector<std::pair<const XMLCh*, const XMLCh*> > variablesUsed() const;

  /** Sets the members of this StaticAnalysis from the given StaticAnalysis */
  void add(const StaticAnalysis &o);
  void addExceptContextFlags(const StaticAnalysis &o);

  /** Returns true if flags are set, or variables have been used */
  bool isUsed() const;
  bool isUsedExceptContextFlags() const;

  void creative(bool value);
  bool isCreative() const;

  void updating(bool value);
  bool isUpdating() const;
  void possiblyUpdating(bool value);
  bool isPossiblyUpdating() const;

  /**
   * Properties that allow optimisation regarding sorting or not.
   * The values are OR'd as flags, so they must be distinct bits
   */
  enum Properties {
    DOCORDER     = 0x001, ///< Results are returned in document order
    PEER         = 0x002, ///< Results do not appear in the descendants of other results
    SUBTREE      = 0x004, ///< Results are members of the set of descendants of the context node
    GROUPED      = 0x008, ///< Results are grouped by the document they come from
    SAMEDOC      = 0x010, ///< Results are from the same document as the context node
    ONENODE      = 0x020, ///< Only ever returns one node
    SELF         = 0x040, ///< Only ever returns the context node
    FORWARDREF   = 0x080, ///< This is a forward reference for a global variable that is declared later
    UNDEFINEDVAR = 0x100  ///< This is a variable that has been undefined
  };

  unsigned int getProperties() const;
  void setProperties(unsigned int props);

  const StaticType &getStaticType() const;
  StaticType &getStaticType();

  std::string toString() const;

private:
  StaticAnalysis(const StaticAnalysis &o);
  StaticAnalysis &operator=(const StaticAnalysis &o);

  bool _contextItem;
  bool _contextPosition;
  bool _contextSize;
  bool _currentTime;
  bool _implicitTimezone;
  bool _availableDocuments;
  bool _availableCollections;
  bool _forceNoFolding;
  bool _creative;
  bool _updating;
  bool _possiblyUpdating;

  unsigned int _properties;
  StaticType _staticType;

  VariableAccessSet _dynamicVariables;
  XERCES_CPP_NAMESPACE_QUALIFIER XMLStringPool _uriPool;
  XPath2MemoryManager* _memMgr;
};

#endif