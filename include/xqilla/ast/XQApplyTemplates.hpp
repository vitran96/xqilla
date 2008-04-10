/*
 * Copyright (c) 2001-2007
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2007
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

#ifndef XQAPPLYTEMPLATES_HPP
#define XQAPPLYTEMPLATES_HPP

#include <xqilla/ast/XQCallTemplate.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/simple-api/XQQuery.hpp>

class XQILLA_API XQApplyTemplates : public ASTNodeImpl
{
public:
  XQApplyTemplates(ASTNode *expr, TemplateArguments *args, XPath2MemoryManager *mm);

  virtual ASTNode *staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);
  virtual Result createResult(DynamicContext *context, int flags=0) const;

  ASTNode *getExpression() const { return expr_; }
  void setExpression(ASTNode *expr) { expr_ = expr; }
  TemplateArguments *getArguments() const { return args_; }
  void setArguments(TemplateArguments *args) { args_ = args; }
  const UserFunctions &getTemplates() const { return templates_; }

  void evaluateArguments(VarStoreImpl &scope, DynamicContext *context) const;

private:
  ASTNode *expr_;
  TemplateArguments *args_;
  UserFunctions templates_;
};

#endif
