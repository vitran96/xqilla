/*
 * Copyright (c) 2001-2008
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2008
 *     Oracle. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Id$
 */

#ifndef XQUSERFUNCTION_HPP
#define XQUSERFUNCTION_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/functions/FuncFactory.hpp>
#include <xqilla/functions/ExternalFunction.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/schema/DocumentCache.hpp>
#include <xqilla/ast/XQFunction.hpp>
#include <xqilla/ast/StaticAnalysis.hpp>
#include <xqilla/context/impl/VarStoreImpl.hpp>

class XQILLA_API XQUserFunction : public FuncFactory, public LocationInfo
{
public:
  class ArgumentSpec : public LocationInfo
  {
  public:
    ArgumentSpec(const XMLCh *qname, SequenceType *type, XPath2MemoryManager *memMgr)
      : src_(memMgr)
    {
      qname_ = memMgr->getPooledString(qname);
      seqType_ = type;
    }

    const XMLCh *getURI() const { return uri_; }
    const XMLCh *getName() const { return name_; }
    SequenceType *getType() const { return seqType_; }

    bool isUsed() const { return qname_ != 0; }
    void setNotUsed() { qname_ = 0; }

    const StaticAnalysis &getStaticAnalysis() const { return src_; }

    void staticResolution(StaticContext* context);

  private:
    const XMLCh *qname_, *uri_, *name_;
    SequenceType *seqType_;
    StaticAnalysis src_;
  };

  typedef std::vector<ArgumentSpec*,XQillaAllocator<ArgumentSpec*> > ArgumentSpecs;

  class Instance : public XQFunction, public ExternalFunction::Arguments
  {
  public:
    Instance(const XQUserFunction *funcDef, const VectorOfASTNodes& args, XPath2MemoryManager* expr);

    virtual Result getArgument(size_t index, DynamicContext *context) const;

    Result createResult(DynamicContext* context, int flags=0) const;
    virtual void generateEvents(EventHandler *events, DynamicContext *context,
                                bool preserveNS, bool preserveType) const;
    ASTNode* staticResolution(StaticContext* context);
    virtual ASTNode *staticTyping(StaticContext *context);
    virtual PendingUpdateList createUpdateList(DynamicContext *context) const;

    void evaluateArguments(VarStoreImpl &scope, DynamicContext *context) const;

    const XQUserFunction *getFunctionDefinition() const
    {
      return funcDef_;
    }

  protected:
    class FunctionEvaluatorResult : public ResultImpl
    {
    public:
      FunctionEvaluatorResult(const Instance *di, DynamicContext *context);

      Item::Ptr next(DynamicContext *context);
      std::string asString(DynamicContext *context, int indent) const;
    private:
      const Instance *_di;
      bool _toDo;

      VarStoreImpl _scope;
      Result _result;
    };

    class ExternalFunctionEvaluatorResult : public ResultImpl
    {
    public:
      ExternalFunctionEvaluatorResult(const Instance *di);

      Item::Ptr next(DynamicContext *context);
      std::string asString(DynamicContext *context, int indent) const;
    private:
      const Instance *_di;
      bool _toDo;

      Result _result;
    };

    bool addReturnCheck_;
    const XQUserFunction *funcDef_;
  };

  XQUserFunction(const XMLCh *qname, ArgumentSpecs *argSpecs, ASTNode *body, SequenceType *returnType, bool isUpdating, XPath2MemoryManager *mm);

  // from FuncFactory
  virtual ASTNode *createInstance(const VectorOfASTNodes &args, XPath2MemoryManager* expr) const;
  virtual const XMLCh* getName() const { return name_; }
  virtual const XMLCh *getURI() const { return uri_; }
  virtual const XMLCh *getURINameHash() const { return uriname_; }
  virtual size_t getMinArgs() const;
  virtual size_t getMaxArgs() const;

  const ArgumentSpecs* getArgumentSpecs() const { return argSpecs_; }
  const SequenceType* getReturnType() const { return returnType_; }
  bool isUpdating() const { return isUpdating_; }

  /// Resolve URIs, give the function a default static type
  void staticResolutionStage1(StaticContext* context);
  /// Resolve the function body, work out a more static return type
  void staticResolutionStage2(StaticContext* context);
  void staticTyping(StaticContext *context);

  void setFunctionBody(ASTNode* value) { body_ = value; }
  void setModuleDocumentCache(DocumentCache* docCache) { moduleDocCache_ = docCache; }

  const ASTNode *getFunctionBody() const { return body_; }
  const ExternalFunction *getExternalFunction() const { return exFunc_; }
  DocumentCache *getModuleDocumentCache() const { return moduleDocCache_; }

  static const XMLCh XMLChXQueryLocalFunctionsURI[];

protected:
  ASTNode *body_;
  const ExternalFunction *exFunc_;
  const XMLCh *name_, *qname_, *uri_;
  const XMLCh *uriname_;
  SequenceType *returnType_;
  ArgumentSpecs *argSpecs_;
  bool isUpdating_;

  XPath2MemoryManager *memMgr_;
  StaticAnalysis src_;
  bool calculatingSRC_;
  DocumentCache *moduleDocCache_;

  friend class Instance;
};

#endif
