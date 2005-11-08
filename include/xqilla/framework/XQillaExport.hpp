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

#ifndef __XQILLAEXPORT_HPP
#define __XQILLAEXPORT_HPP

// The following ifdef block is the standard way of creating macros which
// make exporting from a DLL simpler. All files within this DLL are
// compiled with the XQILLA_APIS symbol defined on the command line.
// this symbol should not be defined on any project that uses this DLL.
// This way any other project whose source files include this file see
// XQILLA_API functions as being imported from a DLL, wheras this DLL
// sees symbols defined with this macro as being exported.

#if defined(WIN32) && !defined(__CYGWIN__)
  #ifdef XQILLA_APIS
    #define XQILLA_API __declspec(dllexport)
  #else
    #define XQILLA_API __declspec(dllimport)
  #endif
  #pragma warning(disable: 4251 4786 4101 4290)
#else
  #define XQILLA_API 
#endif

#endif