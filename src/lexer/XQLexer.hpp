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

#ifndef XQLEXER_H
#define XQLEXER_H

// #define XQ_DEBUG_LEXER 1

#define YY_CHAR unsigned short

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLChar.hpp>

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/simple-api/XQilla.hpp>

typedef struct yyltype
{
  int first_line;
  int first_column;

  int last_line;
  int last_column;

  int first_offset;
  int last_offset;
} yyltype;
#define YYLTYPE yyltype
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1

#define YY_USER_ACTION  userAction(yytext, yyleng);

#define YYLLOC_DEFAULT(Current, Rhs, N)         \
  do                  \
    if (N)                \
    {                \
      (Current).first_line   = (Rhs)[1].first_line;  \
      (Current).first_column = (Rhs)[1].first_column;  \
      (Current).last_line    = (Rhs)[N].last_line;    \
      (Current).last_column  = (Rhs)[N].last_column;  \
      (Current).first_offset = (Rhs)[1].first_offset;  \
      (Current).last_offset  = (Rhs)[N].last_offset;   \
    }                \
    else                \
    {                \
      (Current).first_line   = (Current).last_line   =    \
        (Rhs)[0].last_line;        \
      (Current).first_column = (Current).last_column =    \
        (Rhs)[0].last_column;        \
      (Current).first_offset = (Current).last_offset =    \
        (Rhs)[0].last_offset;        \
    }                \
  while (0)

#ifndef yyFlexLexer
#define yyFlexLexer xqFlexLexer
#include "FlexLexer.h"
#endif

#include <xercesc/util/BitSet.hpp>
#include <xercesc/util/RefHashTableOf.hpp>
#include <xqilla/simple-api/XQQuery.hpp>
#include <xqilla/context/DynamicContext.hpp>

#ifndef YYSTYPE
#include <xqilla/ast/ASTNode.hpp>
#include <xqilla/ast/TupleNode.hpp>
#include <xqilla/ast/OrderByTuple.hpp>
#include <xqilla/ast/XQNav.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/parser/QName.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/ast/XQTypeswitch.hpp>
#include <xqilla/ast/XQPredicate.hpp>
#include <xqilla/fulltext/FTSelection.hpp>
#include <xqilla/fulltext/FTWords.hpp>
#include <xqilla/fulltext/FTOption.hpp>
#include <xqilla/fulltext/FTRange.hpp>
#include <xqilla/update/UTransform.hpp>

typedef union {
  XMLCh* str;
  ASTNode* astNode;
  XQUserFunction* functDecl;
  XQUserFunction::ArgumentSpec* argSpec;
  XQUserFunction::ArgumentSpecs* argSpecs;
  NodeTest *nodeTest;
  XQStep::Axis axis;
  QualifiedName *qName;
  SequenceType* sequenceType;
  SequenceType::OccurrenceIndicator occurrence;
  SequenceType::ItemType* itemType;
  VectorOfASTNodes* itemList;
  VectorOfPredicates* predicates;
  TupleNode *tupleNode;
  CopyBinding* copyBinding;
  VectorOfCopyBinding* copyBindingList;
  XQTypeswitch::Case *caseClause;
  XQTypeswitch::Cases *caseClauses;
  OrderByTuple::Modifiers orderByModifier;
  VectorOfStrings* stringList;
  FTSelection *ftselection;
  FTWords::FTAnyallOption ftanyalloption;
  FTOption *ftoption;
  VectorOfFTOptions *ftoptionlist;
  FTRange ftrange;
  FTOption::FTUnit ftunit;
  bool boolean;
} yystype;
#define YYSTYPE yystype
#define YYSTYPE_IS_DECLARED 1
#define YYSTYPE_IS_TRIVIAL 1

#endif  // #ifndef YYSTYPE

#include "../parser/XQParser.hpp"  // to be included *after* defining YYSTYPE and YYLTYPE

class XQILLA_API XQLexer : public yyFlexLexer
{
public:
  XQLexer(XPath2MemoryManager* memMgr, const XMLCh *queryFile, const XMLCh* query, XQilla::Language lang);

  // Implemented in XQLexer.cpp, output of XQLexer.l
  int yylex();
  int yylex(YYSTYPE* pYYLVAL, YYLTYPE* pYYLOC);

  const XMLCh* getQueryString() { return m_szQuery; }
  void setGenerateErrorException(bool bEnable) { m_bGenerateErrorException=bEnable; }

  int error(const char* message)
  {
    Error(message, m_lineno, m_columnno);
    return 0;
  }

  int error(const yyltype &pos, const char* message)
  {
    Error(message, pos.first_line, pos.first_column);
    return 0;
  }

  int error(XQilla::Language lang, const char* where, unsigned int line, unsigned int column)
  {
    Error(lang, where, line, column);
    return 0;
  }

  XQilla::Language getLanguage() const { return m_language; }
  bool isXQuery() const { return (m_language & XQilla::XPATH2) == 0; }
  bool isXPath() const { return (m_language & XQilla::XPATH2) != 0; }
  bool isFullText() const { return (m_language & XQilla::FULLTEXT) != 0; }
  bool isUpdate() const { return (m_language & XQilla::UPDATE) != 0; }

  void undoLessThan();

protected:
  // For look ahead
  XQLexer(const XQLexer *other);

  virtual int LexerInput(YY_CHAR* buf, int max_size);
  virtual void LexerOutput(const YY_CHAR* buf, int size);
  virtual void LexerError(const char* msg);
  virtual void yy_pop_state();

  void Error(const char* msg, int line, int col);
  void Error(XQilla::Language lang, const char *where, unsigned int line, unsigned int col);

  void userAction(YY_CHAR* text, int length);
  void undoUserAction();

  int lookAhead();
    
  void beginComment();
  void endComment();
  bool isCommentClosed();

  XMLCh *allocate_string(const XMLCh* src);
  XMLCh *allocate_string(const XMLCh* src, int len);
  XMLCh *allocate_string_and_unescape(XMLCh toBeUnescaped, const XMLCh* src, int len);
  XMLCh *allocate_string_and_unescape(XMLCh *src, int len, XMLCh quoteChar, bool unescapeBrace);

  YYSTYPE yylval;
  YYLTYPE yyloc;

  bool firstToken_;

  const XMLCh* m_szQueryFile;
  const XMLCh* m_szQuery;
  unsigned int m_nLength;
  int m_position,m_index;
  XPath2MemoryManager* m_memMgr;
  int m_lineno,m_columnno;

  int m_nOpenComments;
  bool m_bGenerateErrorException;

  XQilla::Language m_language;
};

class XQParserArgs
{
public:
  XQParserArgs()
    : _lexer(0), _context(0), _query(0), _flags(32), _namespaceDecls(13) {}

  XQLexer* _lexer;
  DynamicContext* _context;
  XQQuery* _query;
  XERCES_CPP_NAMESPACE_QUALIFIER BitSet _flags;
  XERCES_CPP_NAMESPACE_QUALIFIER RefHashTableOf<XMLCh> _namespaceDecls;
};

namespace XQParser {
  extern int yyparse(void *);
  extern int yydebug;
}


#endif

