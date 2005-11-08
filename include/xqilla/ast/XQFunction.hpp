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

#ifndef _XQFUNCTION_HPP
#define _XQFUNCTION_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/ASTNodeImpl.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/context/ItemFactory.hpp>

#include <xercesc/util/XMLUniDefs.hpp>      // because every implementation will use these to define the function name
#include <vector>

class SequenceType;

class XQILLA_API XQFunction : public ASTNodeImpl
{

public:
  XQFunction(const XMLCh* name, unsigned int argsFrom, unsigned int argsTo, const char* paramDecl, const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  virtual ~XQFunction();

  const XMLCh* getFunctionURI()const;
  const XMLCh* getFunctionName()const;
  const XMLCh* getFunctionSignature() const;
  const VectorOfASTNodes &getArguments() const;
  
  static const XMLCh XMLChFunctionURI[];

  /** casts the expression given as a parameter into the appropriate type and returns the guaranteed correctly typed objects in a sequence  */
  virtual Result getParamNumber(unsigned int number, DynamicContext* context, int flags=0) const;

  /** returns the number of parameters passed into the function */
  unsigned int getNumArgs() const;

protected:
  
  /** casts the expression given as a parameter into the specified type and returns the guaranteed correctly typed objects in a sequence  */
  virtual Result getParamNumber(unsigned int paramNumber, unsigned int signatureNumber, DynamicContext* context, int flags=0) const;

  /** Helper method, produces a single ATStringOrDerived from the output of getParamNumber(). If getParamNumber() returns anything other than a single string, an exception is thrown. */
  ATStringOrDerived::Ptr getStringParam(unsigned int number, DynamicContext* context, int flags=0) const;

  static const unsigned int UNLIMITED;

  //parse the supplied string of comma separated arguments into vector of SequenceTypes
  static std::vector< SequenceType* >* parseParamDecl(const char* paramString);

  const XMLCh *_fName, *_fURI, *_signature;
  const unsigned int _nArgsFrom, _nArgsTo;

  const std::vector<SequenceType*>* _paramDecl;

  VectorOfASTNodes _args; // The real store for arguments 

};

#endif