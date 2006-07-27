/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Sleepycat Software. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id$
 */

#include "../config/xqilla_config.h"
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xqilla/framework/XPath2MemoryManagerImpl.hpp>

#include <xqilla/utils/XQillaPlatformUtils.hpp>
#include "../dom-api/XQillaImplementation.hpp"
#include <xqilla/items/impl/ATDecimalOrDerivedImpl.hpp>
#include <xqilla/items/impl/ATDoubleOrDerivedImpl.hpp>
#include <xqilla/items/impl/ATFloatOrDerivedImpl.hpp>

#include <xqilla/mapm/m_apm.h>
#include "DateUtils.hpp"

XERCES_CPP_NAMESPACE_USE;

static int gInitFlag = 0;

void XQillaPlatformUtils::initialize(MemoryManager *memMgr) {
  //  Make sure we haven't already been initialized. Note that this is not
  //  thread safe and is not intended for that.
  if(gInitFlag++ == 0) {
    XMLPlatformUtils::Initialize(XMLUni::fgXercescDefaultLocale, 0, 0, memMgr);
    XQillaImplementation::initialize();
    m_apm_mt_initialize();
    DateUtils::initialize();
  }
}

void XQillaPlatformUtils::terminate() {
  if(gInitFlag == 0) {
    return;
  }

  if(--gInitFlag == 0) {
    m_apm_free_all_mem_mt();
    DateUtils::terminate();
    m_apm_mt_terminate();
    XQillaImplementation::terminate();
    XMLPlatformUtils::Terminate();
  }
}

void XQillaPlatformUtils::enableExtendedPrecision(bool bEnable)
{
    if(bEnable)
    {
        ATDecimalOrDerivedImpl::g_nSignificantDigits=50;
        ATFloatOrDerivedImpl::g_nSignificantDigits=25;
        ATDoubleOrDerivedImpl::g_nSignificantDigits=25;
    }
    else
    {
        ATDecimalOrDerivedImpl::g_nSignificantDigits=18;
        ATFloatOrDerivedImpl::g_nSignificantDigits=7;
        ATDoubleOrDerivedImpl::g_nSignificantDigits=16;
    }
}
