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

#ifndef XQCONTEXTIMPL_H
#define XQCONTEXTIMPL_H

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/impl/VarStoreImpl.hpp>
#include <xqilla/schema/DocumentCache.hpp>
#include <xqilla/ast/ASTNode.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/simple-api/XQilla.hpp>
#include <xqilla/framework/ProxyMemoryManager.hpp>

#include <xercesc/util/ValueHashTableOf.hpp>

class XQillaConfiguration;
class FunctionLookup;

class XQILLA_API XQContextImpl : public DynamicContext
{
public:
  XQContextImpl(XQillaConfiguration *conf, XQilla::Language language,
                XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memMgr =
                XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::fgMemoryManager);
  ~XQContextImpl();

  virtual DynamicContext *createModuleContext(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *memMgr =
                                              XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::fgMemoryManager) const;
  virtual DynamicContext *createModuleDynamicContext(const DynamicContext* moduleCtx, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *memMgr =
                                                     XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::fgMemoryManager) const;
  virtual DynamicContext *createDynamicContext(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager *memMgr =
                                               XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::fgMemoryManager) const;

  virtual XQillaConfiguration *getConfiguration() const { return _conf; }

  virtual XQilla::Language getLanguage() const;

  //////////////////////////////////////
  // XQuery Static Context Accessors  //
  //////////////////////////////////////

  /**
   * Overrides the inherited method, and disowns any output
   * document that was created with the previous memory manager.
   */
  virtual void setMemoryManager(XPath2MemoryManager *memMgr);

  /** Binds a prefix to a namespace URI */
  virtual void setNamespaceBinding(const XMLCh* prefix, const XMLCh* uri);

  /** Set the policy for boundary space */
  virtual void setPreserveBoundarySpace(bool value);
  /** Get the policy for boundary space */
  virtual bool getPreserveBoundarySpace() const;

  //////////////////////////////////////
  // XQuery Dynamic Context Accessors //
  //////////////////////////////////////

  virtual void testInterrupt() const;

  //////////////////////////////////
  // Dynamic Context Accessors    //
  //////////////////////////////////

  /** Resets the dynamic context, as if it had never been used */
  virtual void clearDynamicContext();

  virtual SequenceBuilder *createSequenceBuilder() const;

  /** Returns the ItemFactory for this context, which is used to create XQilla items and other objects. */
  virtual ItemFactory *getItemFactory() const;
  /** Sets the ItemFactory for this context */
  virtual void setItemFactory(ItemFactory *factory);

  /** Get the context Item */
  virtual Item::Ptr getContextItem() const;
  /** Set the context item to item */
  virtual void setContextItem(const Item::Ptr &item);

  /** Get the context position */
  virtual unsigned int getContextPosition() const;
  /** Set the context position */
  virtual void setContextPosition(unsigned int pos);

  /** Get the context size */
  virtual unsigned int getContextSize() const;
  /** Set the context size */
  virtual void setContextSize(unsigned int size);

  virtual const VariableStore* getVariableStore() const;
  virtual void setVariableStore(const VariableStore *store);
  virtual const VariableStore* getGlobalVariableStore() const;
  virtual void setGlobalVariableStore(const VariableStore *store);
  virtual void setExternalVariable(const XMLCh *namespaceURI, const XMLCh *name, const Sequence &value);
  virtual void setExternalVariable(const XMLCh *qname, const Sequence &value);

  /** Return the current time */
  virtual time_t getCurrentTime() const;
  /** Set the current time */
  virtual void setCurrentTime(time_t newTime);

  /** Return the implicit timezone for this system.*/
  virtual ATDurationOrDerived::Ptr getImplicitTimezone() const;
  /** Set the implicit timezone */
  virtual void setImplicitTimezone(const ATDurationOrDerived::Ptr &timezoneAsDuration);

  /**
     Register a callback object for resolving URIs. Multiple URIResolver
     objects can be registered with the DynamicContext at the same time.
     The most recently added URIResolver will be called first, and if it
     returns NULL, subsequent ones will be called - ending in a call to
     the fallback routines.

     If "adopt" is false, the DynamicContext will not
     adopt this object, making the user responsible for making sure that the
     URIResolver object's lifespan matches or exceeds the life of the
     DynamicContext.
  */
  virtual void registerURIResolver(URIResolver *resolver, bool adopt);
  /** Returns the default URIResolver */
  virtual URIResolver *getDefaultURIResolver() const;
  /** Sets the default URIResolver */
  virtual void setDefaultURIResolver(URIResolver *resolver, bool adopt);

  /* Resolve the given uri (and baseUri) to a DOMDocument. If the uri
     is relative, the base uri is obtained from the context. */
  virtual Sequence resolveDocument(const XMLCh* uri, const LocationInfo *location);
  /* Resolve the given uri (and baseUri) to a list of DOMNode objects. If
     the uri is relative, the base uri is obtained from the context. */
  virtual Sequence resolveCollection(const XMLCh* uri, const LocationInfo *location);
  virtual Sequence resolveDefaultCollection();

  /** Creates a new UpdateFactory, used for performing updates.
      Caller owns the returned object, and should delete it */
  virtual UpdateFactory *createUpdateFactory() const;

  //////////////////////////////////
  // Static Context Accessors     //
  //////////////////////////////////

  /** Get the static type of the context item */
  virtual const StaticType &getContextItemType() const;
  /** Set the static type of the context item */
  virtual void setContextItemType(const StaticType &st);

  /** Get the current XPath 1.0 compatibility mode */
  virtual bool getXPath1CompatibilityMode() const;
  /** Set the current XPath 1.0 compatibility mode */
  virtual void setXPath1CompatibilityMode(bool newMode);

  /** Get the NS resolver */
  virtual const XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathNSResolver* getNSResolver() const;
  /** returns the URI that is bound in prefix in the current scope or zero
      length string otherwise */
  virtual const XMLCh* getUriBoundToPrefix(const XMLCh* prefix, const LocationInfo *location) const;
  /** returns the prefix that is bound in uri in the current scope or zero
      length string otherwise */
  virtual const XMLCh* getPrefixBoundToUri(const XMLCh* uri) const;
  /** Set the NS resolver */
  virtual void setNSResolver(const XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathNSResolver* resolver);

  /** get the value of the default namespace for elements and types */
  virtual const XMLCh* getDefaultElementAndTypeNS() const;
  /** set the value of the default namespace for elements and types */
  virtual void setDefaultElementAndTypeNS(const XMLCh* newNS);

  /** Return the default namespace for functions */
  virtual const XMLCh* getDefaultFuncNS() const;
  /** Set the default namespace for functions */
  virtual void setDefaultFuncNS(const XMLCh* newNS);

  /** retrieve the repository for the grammars **/
  virtual const DocumentCache* getDocumentCache() const;
  /** sets the repository for the grammars **/
  virtual void setDocumentCache(DocumentCache* docCache);
  /** returns the validated node */
  virtual Node::Ptr validate(const Node::Ptr &node, DocumentCache::ValidationMode valMode);
  /** returns true if the type represented by uri:typename is an instance of uriToCheck:typeNameToCheck
   *
   * ie: to check
   * xs:integer instance of xs:decimal,
   * call
   * isTypeOrDerivedFromType("xs", "integer", "xs", "decimal")
   * (except of course, call with URIs, not prefixes!)
   */
  virtual bool isTypeOrDerivedFromType(const XMLCh* const uri, const XMLCh* const typeName, const XMLCh* const uriToCheck, const XMLCh* const typeNameToCheck) const;
  /**
   * Sets the XMLEntityResolver that is used by Xerces when it is used
   * to parse documents. This affects the behaviour of XQilla whenever
   * it retrieves a DTD or XML Schema grammar.
   */
  virtual void setXMLEntityResolver(XERCES_CPP_NAMESPACE_QUALIFIER XMLEntityResolver* const handler);
  /** Returns the entity resolver currently set */
  virtual XERCES_CPP_NAMESPACE_QUALIFIER XMLEntityResolver* getXMLEntityResolver() const;

  /** Register a callback object for resolving module URIs */
  virtual void setModuleResolver(ModuleResolver *resolver);
  /** Returns the module resolver currently set */
  virtual ModuleResolver *getModuleResolver() const;
  /* Retrieve a list of locations for the given module URI */
  virtual VectorOfStrings* resolveModuleURI(const XMLCh* uri) const;

  /** add the location for the grammar of a specific namespace **/
  virtual void addSchemaLocation(const XMLCh* uri, VectorOfStrings* locations, const LocationInfo *location);

  /** get the variable type store */
  virtual VariableTypeStore* getVariableTypeStore();

  /** adds a custom function to the function table */
  virtual void addCustomFunction(FuncFactory *func);
  /** returns a function object with the given uri, localname and number of arguments triple */
  virtual ASTNode *lookUpFunction(const XMLCh *uri, const XMLCh* name, const VectorOfASTNodes &v) const;

  /** adds an external function implementation to the function table */
  virtual void addExternalFunction(const ExternalFunction *func);
  /** returns an external function implementation for the given uri and localname */
  virtual const ExternalFunction *lookUpExternalFunction(const XMLCh *uri, const XMLCh *name, unsigned int numArgs) const;

  /** Get the implementation for the specified collation */
  virtual Collation* getCollation(const XMLCh* const URI, const LocationInfo *location) const;
  /** Add a collation */
  virtual void addCollation(Collation* collation);

  /** Get the default collation */
  virtual Collation* getDefaultCollation(const LocationInfo *location) const;
  /** Specify which collation is the default one */
  virtual void setDefaultCollation(const XMLCh* const URI);

  /** Return the construction mode */
  virtual ConstructionMode getConstructionMode() const;
  /** Set the construction mode */
  virtual void setConstructionMode(ConstructionMode newMode);

  /** Return the ordering method for node sets */
  virtual NodeSetOrdering getNodeSetOrdering() const;
  /** Set the ordering method for node sets */
  virtual void setNodeSetOrdering(NodeSetOrdering newOrder);

  /** Return the base URI */
  virtual const XMLCh* getBaseURI() const;
  /** Set the base URI */
  virtual void setBaseURI(const XMLCh* newURI);

  /** Return the default ordering mode for FLWOR blocks */
  virtual FLWOROrderingMode getDefaultFLWOROrderingMode() const;
  /** Set the default ordering mode for FLWOR blocks */
  virtual void setDefaultFLWOROrderingMode(FLWOROrderingMode newMode);

  /** Set the policy for namespace inheritance */
  virtual void setInheritNamespaces(bool value);
  /** Get the policy for namespace inheritance */
  virtual bool getInheritNamespaces() const;

  /** Set the policy for namespace copy */
  virtual void setPreserveNamespaces(bool value);
  /** Get the policy for namespace copy */
  virtual bool getPreserveNamespaces() const;

  /** Set the revalidation mode */
  virtual void setRevalidationMode(DocumentCache::ValidationMode mode);
  /** Get the revalidation mode */
  virtual DocumentCache::ValidationMode getRevalidationMode() const;

  /** Set the listener for warning and trace messages */
  virtual void setMessageListener(MessageListener *listener);
  /** Gets the listener for warning and trace messages */
  virtual MessageListener *getMessageListener() const;

  /////////////////////////////////////////
  //  XQilla context specific accessors  //
  /////////////////////////////////////////

  virtual const XMLCh *allocateTempVarName();

  /** Get the memory manager */
  virtual XPath2MemoryManager* getMemoryManager() const;

protected:
  XQillaConfiguration *_conf;
  XQilla::Language _language;

  // The memory manager used to create this context
  XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* _createdWith;

  // used for managing the memory of objects inside this context
  ProxyMemoryManager _internalMM;

  ////////////////////////////////
  //  Static Context variables  //
  ////////////////////////////////

  /** Static type of the context item */
  StaticType _contextItemType;

  /** XPath 1.0 compatibility mode. This value is true if rules for
   * backward compatibility with XPath Version 1.0 are in effect;
   * otherwise it is false */
  bool _xpath1Compatibility;

  /** In-scope namespaces. This is a set of  (prefix, URI) pairs.
   * The in-scope namespaces are used for resolving prefixes used
   * in QNames within the expression */
  const XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathNSResolver* _nsResolver;

  /** The original (global scope) DOMXPathNSResolver */
  const XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathNSResolver* _globalNSResolver;

  /** Default element/type namespace. This is a namespace URI or "none". This
   * namespace is used for any unprefixed QName appearing in a
   * position where an element or type name is expected. */
  const XMLCh* _defaultElementNS;

  /** Default function namespace. This is a namespace URI.
   * This namespace URI is used for any unprefixed QName appearing
   * as the function name in a function call. */
  const XMLCh* _functionNS;

  /** In-scope schema definitions. This is a generic term for all
   * the element, attribute, and type definitions that are in scope
   * during processing of an expression. */
  DocumentCache* _docCache;

  /** In-scope variable types. This is a set of  (QName, type) pairs.
   * It defines the set of variables that have been declared and are
   * available for reference within the expression. The QName
   * represents the name of the variable, and the type represents its
   * static data type */
  VariableTypeStore* _varTypeStore;

  /** In-scope functions. This part of the  static context defines the
   * set of functions that are available to be called from within an
   * expression. Each function is uniquely identified by its QName and
   * its arity (number of parameters). The  static context maps the QName
   * and arity into a function signature and a function definition. The
   * function signature specifies the static types of the function
   * parameters and the function result. */
  FunctionLookup* _functionTable;

  /** In-scope collations. This is a set of  (URI, collation) pairs. It
   * defines the names of the collations that are available for use in
   * function calls that take a collation name as an argument. A collation
   * may be regarded as an object that supports two functions: a function
   * that given a set of strings, returns a sequence containing those strings
   * in sorted order; and a function that given two strings, returns true if
   * they are considered equal, and false if not. */
  std::vector<Collation*, XQillaAllocator<Collation*> > _collations;

  /** Default collation. This is a collation. This collation is used by
   * string comparison functions when no explicit collation is specified. */
  const XMLCh* _defaultCollation;

  /** Construction mode. The construction mode governs the behavior of
   *  element constructors. If construction mode is preserve, the type
   *  of a constructed element node is xs:anyType, and the attributes
   *  and descendants of the constructed element retain their original
   *  types. If construction mode is strip, the type of the constructed
   *  element node and all its descendants is xdt:untyped, and attributes
   *  of the constructed element have type xdt:untypedAtomic */
  ConstructionMode _constructionMode;

  /** Ordering mode, which has the value ordered or unordered, affects
   *  the ordering of the result sequence returned by path expressions,
   *  union, intersect, and except expressions, and FLWOR expressions
   *  that have no order by clause. */
  NodeSetOrdering _ordering;

  /** Default ordering for empty sequences. This component controls whether an 
   *  empty sequence is interpreted as the greatest value or as the least value 
   *  during processing of an order by clause in a FLWOR expression, as described 
   *  in 3.8.3 Order By and Return Clauses.] Its value may be greatest or least. */
  FLWOROrderingMode _flworOrderingMode;

  /** Boundary-space policy. This component controls the processing of boundary 
   *  whitespace  by element constructors, as described in 3.7.1.4 Whitespace 
   *  in Element Content.] Its value may be preserve or strip. */
  bool _bPreserveBoundarySpace;

  /** Copy-namespaces mode. This component controls the namespace bindings 
   *  that are assigned when an existing element node is copied by an element 
   *  constructor, as described in 3.7.1 Direct Element Constructors. Its value 
   *  consists of two parts: preserve or no-preserve, and inherit or no-inherit. */
  bool _bPreserveNamespaces,
       _bInheritNamespaces;

  /** The revalidation mode for XQuery Update */
  DocumentCache::ValidationMode _revalidationMode;

  /** The message listener, for warnings and trace messages */
  MessageListener *_messageListener;

  /** Base URI. This is an absolute URI, used when necessary in the
   * resolution of relative URIs (for example, by the fn:resolve- uri
   * function.) The base URI is always provided by the external environment. */
  const XMLCh* _baseURI;

  /////////////////////////////////
  //  Dynamic Context Variables  //
  /////////////////////////////////

  /** The context item is the item currently being processed. */
  Item::Ptr _contextItem;

  /** The context position is the position of  the context item within
   * the sequence of items currently being processed. */
  unsigned int _contextPosition;

  /** The context size is the number of items in the sequence of
   * items currently being processed. */
  unsigned int _contextSize;

  /** In-scope variable values. This is a set of  (QName, Sequence) pairs.
   * It defines the set of variables that have been declared and are
   * available for reference within the expression. The QName
   * represents the name of the variable, and the Sequence represents its
   * value */
  const VariableStore *_varStore;
  const VariableStore *_globalVarStore;
  VarStoreImpl _defaultVarStore;

  /** Current date and time. This information  represents an
   * implementation-dependent point in time during processing of a query
   * or transformation */
  time_t _currentTime;

  /** Implicit timezone. This is the timezone to be used when a date,
   * time, or dateTime value that does not have a timezone is used in a
   * comparison or in any other operation. This value is an instance of
   * xdt:dayTimeDuration */
  ATDurationOrDerived::Ptr _implicitTimezone;

  /** For each atomic type in the in-scope type  definitions, there is 
   * a constructor function in the in-scope functions. Constructor 
   * functions are discussed in 3.10.4 Constructor Functions */
  ItemFactory* _itemFactory;

  ////////////////////////////////////////
  //  XQilla Context specific variables //
  ////////////////////////////////////////

  struct ResolverEntry {
    ResolverEntry() : resolver(0), adopt(false) {}
    ResolverEntry(URIResolver *r, bool a) : resolver(r), adopt(a) {}
    URIResolver *resolver;
    bool adopt;
  };

  /// A stack of URIResolver pointers
  std::vector<ResolverEntry, XQillaAllocator<ResolverEntry> > _resolvers;
  ResolverEntry _defaultResolver;

  ModuleResolver *_moduleResolver;

  unsigned int _tmpVarCounter;

  // used for memory management in expression evaluation
  XPath2MemoryManager* _memMgr;
};

#endif
