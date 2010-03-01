
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MYEOF = 0,
     _LANG_XPATH2_ = 258,
     _LANG_XQUERY_ = 259,
     _LANG_XQUERY_FULLTEXT_ = 260,
     _LANG_XQUERY_UPDATE_ = 261,
     _LANG_XQUERY_FULLTEXT_UPDATE_ = 262,
     _LANG_XSLT2_ = 263,
     _DOLLAR_ = 264,
     _COLON_EQUALS_ = 265,
     _ASTERISK_ = 266,
     _BAR_ = 267,
     _BANG_EQUALS_ = 268,
     _LESS_THAN_EQUALS_ = 269,
     _GREATER_THAN_ = 270,
     _GREATER_THAN_EQUALS_ = 271,
     _LESS_THAN_LESS_THAN_ = 272,
     _GREATER_THAN_GREATER_THAN_ = 273,
     _COLON_COLON_ = 274,
     _AT_SIGN_ = 275,
     _LSQUARE_ = 276,
     _RSQUARE_ = 277,
     _QUESTION_MARK_ = 278,
     _LESS_THAN_OP_OR_TAG_ = 279,
     _START_TAG_CLOSE_ = 280,
     _END_TAG_CLOSE_ = 281,
     _PI_START_ = 282,
     _XML_COMMENT_START_ = 283,
     _XML_COMMENT_END_ = 284,
     _SLASH_SLASH_ = 285,
     _END_TAG_OPEN_ = 286,
     _PRAGMA_OPEN_ = 287,
     _COMMA_ = 288,
     _PLUS_ = 289,
     _MINUS_ = 290,
     _SLASH_ = 291,
     _EQUALS_ = 292,
     _DOT_ = 293,
     _DOT_DOT_ = 294,
     _LPAR_ = 295,
     _RPAR_ = 296,
     _EMPTY_TAG_CLOSE_ = 297,
     _VALUE_INDICATOR_ = 298,
     _OPEN_QUOT_ = 299,
     _CLOSE_QUOT_ = 300,
     _OPEN_APOS_ = 301,
     _CLOSE_APOS_ = 302,
     _LBRACE_ = 303,
     _RBRACE_ = 304,
     _SEMICOLON_ = 305,
     _HASH_ = 306,
     _INTEGER_LITERAL_ = 307,
     _DECIMAL_LITERAL_ = 308,
     _DOUBLE_LITERAL_ = 309,
     _ATTRIBUTE_ = 310,
     _COMMENT_ = 311,
     _DOCUMENT_NODE_ = 312,
     _NODE_ = 313,
     _PROCESSING_INSTRUCTION_ = 314,
     _SCHEMA_ATTRIBUTE_ = 315,
     _SCHEMA_ELEMENT_ = 316,
     _TEXT_ = 317,
     _EMPTY_SEQUENCE_ = 318,
     _BOUNDARY_SPACE_ = 319,
     _FT_OPTION_ = 320,
     _BASE_URI_ = 321,
     _LAX_ = 322,
     _STRICT_ = 323,
     _IDIV_ = 324,
     _CHILD_ = 325,
     _DESCENDANT_ = 326,
     _SELF_ = 327,
     _DESCENDANT_OR_SELF_ = 328,
     _FOLLOWING_SIBLING_ = 329,
     _FOLLOWING_ = 330,
     _PARENT_ = 331,
     _ANCESTOR_ = 332,
     _PRECEDING_SIBLING_ = 333,
     _PRECEDING_ = 334,
     _ANCESTOR_OR_SELF_ = 335,
     _DOCUMENT_ = 336,
     _NOT_ = 337,
     _SENSITIVE_ = 338,
     _INSENSITIVE_ = 339,
     _DIACRITICS_ = 340,
     _WITHOUT_ = 341,
     _WITHOUT_C_ = 342,
     _STEMMING_ = 343,
     _THESAURUS_ = 344,
     _STOP_ = 345,
     _WILDCARDS_ = 346,
     _ENTIRE_ = 347,
     _CONTENT_ = 348,
     _WORD_ = 349,
     _TYPE_ = 350,
     _START_ = 351,
     _END_ = 352,
     _MOST_ = 353,
     _SKIP_ = 354,
     _COPY_ = 355,
     _VALUE_ = 356,
     _WHITESPACE_ = 357,
     _PI_CONTENT_ = 358,
     _XML_COMMENT_CONTENT_ = 359,
     _EQ_ = 360,
     _NE_ = 361,
     _LT_ = 362,
     _LE_ = 363,
     _GT_ = 364,
     _GE_ = 365,
     _AT_ = 366,
     _QUOT_ATTR_CONTENT_ = 367,
     _APOS_ATTR_CONTENT_ = 368,
     _WHITESPACE_ELEMENT_CONTENT_ = 369,
     _ELEMENT_CONTENT_ = 370,
     _AT_LM_ = 371,
     _ORDERED_ = 372,
     _UNORDERED_ = 373,
     _QNAME_ = 374,
     _XMLNS_QNAME_ = 375,
     _CONSTR_QNAME_ = 376,
     _STRING_LITERAL_ = 377,
     _VARIABLE_ = 378,
     _NCNAME_COLON_STAR_ = 379,
     _STAR_COLON_NCNAME_ = 380,
     _PI_TARGET_ = 381,
     _PRAGMA_CONTENT_ = 382,
     _RETURN_ = 383,
     _FOR_ = 384,
     _IN_ = 385,
     _LET_ = 386,
     _WHERE_ = 387,
     _BY_ = 388,
     _ORDER_ = 389,
     _STABLE_ = 390,
     _ASCENDING_ = 391,
     _DESCENDING_ = 392,
     _EMPTY_ = 393,
     _GREATEST_ = 394,
     _LEAST_ = 395,
     _COLLATION_ = 396,
     _SOME_ = 397,
     _EVERY_ = 398,
     _SATISFIES_ = 399,
     _TYPESWITCH_ = 400,
     _CASE_ = 401,
     _CASE_S_ = 402,
     _AS_ = 403,
     _IF_ = 404,
     _THEN_ = 405,
     _ELSE_ = 406,
     _OR_ = 407,
     _AND_ = 408,
     _INSTANCE_ = 409,
     _OF_ = 410,
     _CASTABLE_ = 411,
     _TO_ = 412,
     _DIV_ = 413,
     _MOD_ = 414,
     _UNION_ = 415,
     _INTERSECT_ = 416,
     _EXCEPT_ = 417,
     _VALIDATE_ = 418,
     _CAST_ = 419,
     _TREAT_ = 420,
     _IS_ = 421,
     _PRESERVE_ = 422,
     _STRIP_ = 423,
     _NAMESPACE_ = 424,
     _ITEM_ = 425,
     _EXTERNAL_ = 426,
     _ENCODING_ = 427,
     _NO_PRESERVE_ = 428,
     _INHERIT_ = 429,
     _NO_INHERIT_ = 430,
     _DECLARE_ = 431,
     _CONSTRUCTION_ = 432,
     _ORDERING_ = 433,
     _DEFAULT_ = 434,
     _COPY_NAMESPACES_ = 435,
     _OPTION_ = 436,
     _XQUERY_ = 437,
     _VERSION_ = 438,
     _IMPORT_ = 439,
     _SCHEMA_ = 440,
     _MODULE_ = 441,
     _ELEMENT_ = 442,
     _FUNCTION_ = 443,
     _FUNCTION_EXT_ = 444,
     _SCORE_ = 445,
     _FTCONTAINS_ = 446,
     _WEIGHT_ = 447,
     _WINDOW_ = 448,
     _DISTANCE_ = 449,
     _OCCURS_ = 450,
     _TIMES_ = 451,
     _SAME_ = 452,
     _DIFFERENT_ = 453,
     _LOWERCASE_ = 454,
     _UPPERCASE_ = 455,
     _RELATIONSHIP_ = 456,
     _LEVELS_ = 457,
     _LANGUAGE_ = 458,
     _ANY_ = 459,
     _ALL_ = 460,
     _PHRASE_ = 461,
     _EXACTLY_ = 462,
     _FROM_ = 463,
     _WORDS_ = 464,
     _SENTENCES_ = 465,
     _PARAGRAPHS_ = 466,
     _SENTENCE_ = 467,
     _PARAGRAPH_ = 468,
     _REPLACE_ = 469,
     _MODIFY_ = 470,
     _FIRST_ = 471,
     _INSERT_ = 472,
     _BEFORE_ = 473,
     _AFTER_ = 474,
     _REVALIDATION_ = 475,
     _WITH_ = 476,
     _WITH_FT_ = 477,
     _NODES_ = 478,
     _RENAME_ = 479,
     _LAST_ = 480,
     _DELETE_ = 481,
     _INTO_ = 482,
     _UPDATING_ = 483,
     _ID_ = 484,
     _KEY_ = 485,
     _TEMPLATE_ = 486,
     _MATCHES_ = 487,
     _NAME_ = 488,
     _CALL_ = 489,
     _APPLY_ = 490,
     _TEMPLATES_ = 491,
     _MODE_ = 492,
     _FTOR_ = 493,
     _FTAND_ = 494,
     _FTNOT_ = 495,
     _XSLT_END_ELEMENT_ = 496,
     _XSLT_STYLESHEET_ = 497,
     _XSLT_TEMPLATE_ = 498,
     _XSLT_VALUE_OF_ = 499,
     _XSLT_TEXT_ = 500,
     _XSLT_APPLY_TEMPLATES_ = 501,
     _XSLT_CALL_TEMPLATE_ = 502,
     _XSLT_WITH_PARAM_ = 503,
     _XSLT_SEQUENCE_ = 504,
     _XSLT_PARAM_ = 505,
     _XSLT_FUNCTION_ = 506,
     _XSLT_CHOOSE_ = 507,
     _XSLT_WHEN_ = 508,
     _XSLT_OTHERWISE_ = 509,
     _XSLT_IF_ = 510,
     _XSLT_VARIABLE_ = 511,
     _XSLT_COMMENT_ = 512,
     _XSLT_PI_ = 513,
     _XSLT_DOCUMENT_ = 514,
     _XSLT_ATTRIBUTE_ = 515,
     _XSLT_NAMESPACE_ = 516,
     _XSLT_ELEMENT_ = 517,
     _XSLT_ANALYZE_STRING_ = 518,
     _XSLT_MATCHING_SUBSTRING_ = 519,
     _XSLT_NON_MATCHING_SUBSTRING_ = 520,
     _XSLT_COPY_OF_ = 521,
     _XSLT_COPY_ = 522,
     _XSLT_FOR_EACH_ = 523,
     _XSLT_OUTPUT_ = 524,
     _XSLT_IMPORT_SCHEMA_ = 525,
     _XSLT_VERSION_ = 526,
     _XSLT_MODE_ = 527,
     _XSLT_NAME_ = 528,
     _XSLT_DOCTYPE_PUBLIC_ = 529,
     _XSLT_DOCTYPE_SYSTEM_ = 530,
     _XSLT_ENCODING_ = 531,
     _XSLT_MEDIA_TYPE_ = 532,
     _XSLT_NORMALIZATION_FORM_ = 533,
     _XSLT_STANDALONE_ = 534,
     _XSLT_EXCLUDE_RESULT_PREFIXES_ = 535,
     _XSLT_NAMESPACE_STR_ = 536,
     _XSLT_SCHEMA_LOCATION_ = 537,
     _XSLT_TUNNEL_ = 538,
     _XSLT_REQUIRED_ = 539,
     _XSLT_OVERRIDE_ = 540,
     _XSLT_COPY_NAMESPACES_ = 541,
     _XSLT_INHERIT_NAMESPACES_ = 542,
     _XSLT_BYTE_ORDER_MARK_ = 543,
     _XSLT_ESCAPE_URI_ATTRIBUTES_ = 544,
     _XSLT_INCLUDE_CONTENT_TYPE_ = 545,
     _XSLT_INDENT_ = 546,
     _XSLT_OMIT_XML_DECLARATION_ = 547,
     _XSLT_UNDECLARE_PREFIXES_ = 548,
     _XSLT_MATCH_ = 549,
     _XSLT_AS_ = 550,
     _XSLT_SELECT_ = 551,
     _XSLT_PRIORITY_ = 552,
     _XSLT_TEST_ = 553,
     _XSLT_SEPARATOR_ = 554,
     _XSLT_NAMESPACE_A_ = 555,
     _XSLT_REGEX_ = 556,
     _XSLT_FLAGS_ = 557,
     _XSLT_METHOD_ = 558,
     _XSLT_CDATA_SECTION_ELEMENTS_ = 559,
     _XSLT_USE_CHARACTER_MAPS_ = 560,
     _XSLT_ELEMENT_NAME_ = 561,
     _XSLT_XMLNS_ATTR_ = 562,
     _XSLT_ATTR_NAME_ = 563,
     _XSLT_TEXT_NODE_ = 564,
     _XSLT_WS_TEXT_NODE_ = 565,
     _HASH_DEFAULT_ = 566,
     _HASH_ALL_ = 567,
     _HASH_CURRENT_ = 568,
     _XML_ = 569,
     _HTML_ = 570,
     _XHTML_ = 571
   };
#endif
/* Tokens.  */
#define MYEOF 0
#define _LANG_XPATH2_ 258
#define _LANG_XQUERY_ 259
#define _LANG_XQUERY_FULLTEXT_ 260
#define _LANG_XQUERY_UPDATE_ 261
#define _LANG_XQUERY_FULLTEXT_UPDATE_ 262
#define _LANG_XSLT2_ 263
#define _DOLLAR_ 264
#define _COLON_EQUALS_ 265
#define _ASTERISK_ 266
#define _BAR_ 267
#define _BANG_EQUALS_ 268
#define _LESS_THAN_EQUALS_ 269
#define _GREATER_THAN_ 270
#define _GREATER_THAN_EQUALS_ 271
#define _LESS_THAN_LESS_THAN_ 272
#define _GREATER_THAN_GREATER_THAN_ 273
#define _COLON_COLON_ 274
#define _AT_SIGN_ 275
#define _LSQUARE_ 276
#define _RSQUARE_ 277
#define _QUESTION_MARK_ 278
#define _LESS_THAN_OP_OR_TAG_ 279
#define _START_TAG_CLOSE_ 280
#define _END_TAG_CLOSE_ 281
#define _PI_START_ 282
#define _XML_COMMENT_START_ 283
#define _XML_COMMENT_END_ 284
#define _SLASH_SLASH_ 285
#define _END_TAG_OPEN_ 286
#define _PRAGMA_OPEN_ 287
#define _COMMA_ 288
#define _PLUS_ 289
#define _MINUS_ 290
#define _SLASH_ 291
#define _EQUALS_ 292
#define _DOT_ 293
#define _DOT_DOT_ 294
#define _LPAR_ 295
#define _RPAR_ 296
#define _EMPTY_TAG_CLOSE_ 297
#define _VALUE_INDICATOR_ 298
#define _OPEN_QUOT_ 299
#define _CLOSE_QUOT_ 300
#define _OPEN_APOS_ 301
#define _CLOSE_APOS_ 302
#define _LBRACE_ 303
#define _RBRACE_ 304
#define _SEMICOLON_ 305
#define _HASH_ 306
#define _INTEGER_LITERAL_ 307
#define _DECIMAL_LITERAL_ 308
#define _DOUBLE_LITERAL_ 309
#define _ATTRIBUTE_ 310
#define _COMMENT_ 311
#define _DOCUMENT_NODE_ 312
#define _NODE_ 313
#define _PROCESSING_INSTRUCTION_ 314
#define _SCHEMA_ATTRIBUTE_ 315
#define _SCHEMA_ELEMENT_ 316
#define _TEXT_ 317
#define _EMPTY_SEQUENCE_ 318
#define _BOUNDARY_SPACE_ 319
#define _FT_OPTION_ 320
#define _BASE_URI_ 321
#define _LAX_ 322
#define _STRICT_ 323
#define _IDIV_ 324
#define _CHILD_ 325
#define _DESCENDANT_ 326
#define _SELF_ 327
#define _DESCENDANT_OR_SELF_ 328
#define _FOLLOWING_SIBLING_ 329
#define _FOLLOWING_ 330
#define _PARENT_ 331
#define _ANCESTOR_ 332
#define _PRECEDING_SIBLING_ 333
#define _PRECEDING_ 334
#define _ANCESTOR_OR_SELF_ 335
#define _DOCUMENT_ 336
#define _NOT_ 337
#define _SENSITIVE_ 338
#define _INSENSITIVE_ 339
#define _DIACRITICS_ 340
#define _WITHOUT_ 341
#define _WITHOUT_C_ 342
#define _STEMMING_ 343
#define _THESAURUS_ 344
#define _STOP_ 345
#define _WILDCARDS_ 346
#define _ENTIRE_ 347
#define _CONTENT_ 348
#define _WORD_ 349
#define _TYPE_ 350
#define _START_ 351
#define _END_ 352
#define _MOST_ 353
#define _SKIP_ 354
#define _COPY_ 355
#define _VALUE_ 356
#define _WHITESPACE_ 357
#define _PI_CONTENT_ 358
#define _XML_COMMENT_CONTENT_ 359
#define _EQ_ 360
#define _NE_ 361
#define _LT_ 362
#define _LE_ 363
#define _GT_ 364
#define _GE_ 365
#define _AT_ 366
#define _QUOT_ATTR_CONTENT_ 367
#define _APOS_ATTR_CONTENT_ 368
#define _WHITESPACE_ELEMENT_CONTENT_ 369
#define _ELEMENT_CONTENT_ 370
#define _AT_LM_ 371
#define _ORDERED_ 372
#define _UNORDERED_ 373
#define _QNAME_ 374
#define _XMLNS_QNAME_ 375
#define _CONSTR_QNAME_ 376
#define _STRING_LITERAL_ 377
#define _VARIABLE_ 378
#define _NCNAME_COLON_STAR_ 379
#define _STAR_COLON_NCNAME_ 380
#define _PI_TARGET_ 381
#define _PRAGMA_CONTENT_ 382
#define _RETURN_ 383
#define _FOR_ 384
#define _IN_ 385
#define _LET_ 386
#define _WHERE_ 387
#define _BY_ 388
#define _ORDER_ 389
#define _STABLE_ 390
#define _ASCENDING_ 391
#define _DESCENDING_ 392
#define _EMPTY_ 393
#define _GREATEST_ 394
#define _LEAST_ 395
#define _COLLATION_ 396
#define _SOME_ 397
#define _EVERY_ 398
#define _SATISFIES_ 399
#define _TYPESWITCH_ 400
#define _CASE_ 401
#define _CASE_S_ 402
#define _AS_ 403
#define _IF_ 404
#define _THEN_ 405
#define _ELSE_ 406
#define _OR_ 407
#define _AND_ 408
#define _INSTANCE_ 409
#define _OF_ 410
#define _CASTABLE_ 411
#define _TO_ 412
#define _DIV_ 413
#define _MOD_ 414
#define _UNION_ 415
#define _INTERSECT_ 416
#define _EXCEPT_ 417
#define _VALIDATE_ 418
#define _CAST_ 419
#define _TREAT_ 420
#define _IS_ 421
#define _PRESERVE_ 422
#define _STRIP_ 423
#define _NAMESPACE_ 424
#define _ITEM_ 425
#define _EXTERNAL_ 426
#define _ENCODING_ 427
#define _NO_PRESERVE_ 428
#define _INHERIT_ 429
#define _NO_INHERIT_ 430
#define _DECLARE_ 431
#define _CONSTRUCTION_ 432
#define _ORDERING_ 433
#define _DEFAULT_ 434
#define _COPY_NAMESPACES_ 435
#define _OPTION_ 436
#define _XQUERY_ 437
#define _VERSION_ 438
#define _IMPORT_ 439
#define _SCHEMA_ 440
#define _MODULE_ 441
#define _ELEMENT_ 442
#define _FUNCTION_ 443
#define _FUNCTION_EXT_ 444
#define _SCORE_ 445
#define _FTCONTAINS_ 446
#define _WEIGHT_ 447
#define _WINDOW_ 448
#define _DISTANCE_ 449
#define _OCCURS_ 450
#define _TIMES_ 451
#define _SAME_ 452
#define _DIFFERENT_ 453
#define _LOWERCASE_ 454
#define _UPPERCASE_ 455
#define _RELATIONSHIP_ 456
#define _LEVELS_ 457
#define _LANGUAGE_ 458
#define _ANY_ 459
#define _ALL_ 460
#define _PHRASE_ 461
#define _EXACTLY_ 462
#define _FROM_ 463
#define _WORDS_ 464
#define _SENTENCES_ 465
#define _PARAGRAPHS_ 466
#define _SENTENCE_ 467
#define _PARAGRAPH_ 468
#define _REPLACE_ 469
#define _MODIFY_ 470
#define _FIRST_ 471
#define _INSERT_ 472
#define _BEFORE_ 473
#define _AFTER_ 474
#define _REVALIDATION_ 475
#define _WITH_ 476
#define _WITH_FT_ 477
#define _NODES_ 478
#define _RENAME_ 479
#define _LAST_ 480
#define _DELETE_ 481
#define _INTO_ 482
#define _UPDATING_ 483
#define _ID_ 484
#define _KEY_ 485
#define _TEMPLATE_ 486
#define _MATCHES_ 487
#define _NAME_ 488
#define _CALL_ 489
#define _APPLY_ 490
#define _TEMPLATES_ 491
#define _MODE_ 492
#define _FTOR_ 493
#define _FTAND_ 494
#define _FTNOT_ 495
#define _XSLT_END_ELEMENT_ 496
#define _XSLT_STYLESHEET_ 497
#define _XSLT_TEMPLATE_ 498
#define _XSLT_VALUE_OF_ 499
#define _XSLT_TEXT_ 500
#define _XSLT_APPLY_TEMPLATES_ 501
#define _XSLT_CALL_TEMPLATE_ 502
#define _XSLT_WITH_PARAM_ 503
#define _XSLT_SEQUENCE_ 504
#define _XSLT_PARAM_ 505
#define _XSLT_FUNCTION_ 506
#define _XSLT_CHOOSE_ 507
#define _XSLT_WHEN_ 508
#define _XSLT_OTHERWISE_ 509
#define _XSLT_IF_ 510
#define _XSLT_VARIABLE_ 511
#define _XSLT_COMMENT_ 512
#define _XSLT_PI_ 513
#define _XSLT_DOCUMENT_ 514
#define _XSLT_ATTRIBUTE_ 515
#define _XSLT_NAMESPACE_ 516
#define _XSLT_ELEMENT_ 517
#define _XSLT_ANALYZE_STRING_ 518
#define _XSLT_MATCHING_SUBSTRING_ 519
#define _XSLT_NON_MATCHING_SUBSTRING_ 520
#define _XSLT_COPY_OF_ 521
#define _XSLT_COPY_ 522
#define _XSLT_FOR_EACH_ 523
#define _XSLT_OUTPUT_ 524
#define _XSLT_IMPORT_SCHEMA_ 525
#define _XSLT_VERSION_ 526
#define _XSLT_MODE_ 527
#define _XSLT_NAME_ 528
#define _XSLT_DOCTYPE_PUBLIC_ 529
#define _XSLT_DOCTYPE_SYSTEM_ 530
#define _XSLT_ENCODING_ 531
#define _XSLT_MEDIA_TYPE_ 532
#define _XSLT_NORMALIZATION_FORM_ 533
#define _XSLT_STANDALONE_ 534
#define _XSLT_EXCLUDE_RESULT_PREFIXES_ 535
#define _XSLT_NAMESPACE_STR_ 536
#define _XSLT_SCHEMA_LOCATION_ 537
#define _XSLT_TUNNEL_ 538
#define _XSLT_REQUIRED_ 539
#define _XSLT_OVERRIDE_ 540
#define _XSLT_COPY_NAMESPACES_ 541
#define _XSLT_INHERIT_NAMESPACES_ 542
#define _XSLT_BYTE_ORDER_MARK_ 543
#define _XSLT_ESCAPE_URI_ATTRIBUTES_ 544
#define _XSLT_INCLUDE_CONTENT_TYPE_ 545
#define _XSLT_INDENT_ 546
#define _XSLT_OMIT_XML_DECLARATION_ 547
#define _XSLT_UNDECLARE_PREFIXES_ 548
#define _XSLT_MATCH_ 549
#define _XSLT_AS_ 550
#define _XSLT_SELECT_ 551
#define _XSLT_PRIORITY_ 552
#define _XSLT_TEST_ 553
#define _XSLT_SEPARATOR_ 554
#define _XSLT_NAMESPACE_A_ 555
#define _XSLT_REGEX_ 556
#define _XSLT_FLAGS_ 557
#define _XSLT_METHOD_ 558
#define _XSLT_CDATA_SECTION_ELEMENTS_ 559
#define _XSLT_USE_CHARACTER_MAPS_ 560
#define _XSLT_ELEMENT_NAME_ 561
#define _XSLT_XMLNS_ATTR_ 562
#define _XSLT_ATTR_NAME_ 563
#define _XSLT_TEXT_NODE_ 564
#define _XSLT_WS_TEXT_NODE_ 565
#define _HASH_DEFAULT_ 566
#define _HASH_ALL_ 567
#define _HASH_CURRENT_ 568
#define _XML_ 569
#define _HTML_ 570
#define _XHTML_ 571




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



