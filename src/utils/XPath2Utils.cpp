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

#include "../config/xqilla_config.h"
#include <assert.h>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLUri.hpp>
#include <xercesc/framework/XMLBuffer.hpp>

#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/utils/XPath2Utils.hpp>
#include <xqilla/utils/XPath2NSUtils.hpp>
#include "../exceptions/MiscException.hpp"
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/items/Node.hpp>

#include <xqilla/mapm/m_apm.h>

#if defined(WIN32) && !defined(__CYGWIN__)
#define snprintf _snprintf
#endif

XERCES_CPP_NAMESPACE_USE;

const XMLCh* XPath2Utils::escapeURI(const XMLCh* const str, bool escapeRes, XPath2MemoryManager* memMgr)
{

  if(XMLString::stringLen(str) == 0) {
    return 0;
  }
	XMLBuffer buf(1023, memMgr);

  const XMLCh *cptr; 

  for (cptr = str; *cptr; cptr++) {
    // here we compare 16-bit XMLCh's to zero-padded 8-bit chars, so it 
    // magically works 
    if ((*cptr >= 'A' && *cptr <= 'Z') ||
        (*cptr >= 'a' && *cptr <= 'z') ||
        (*cptr >= '0' && *cptr <= '9') ||
        *cptr == '%' || *cptr == '#' || 
        *cptr == '-' || *cptr == '_' || *cptr == '.' || 
        *cptr == '!' || *cptr == '~' || *cptr == '*' ||
        *cptr == '\''|| *cptr == '(' || *cptr == ')' ||
        (!escapeRes && 
         (*cptr == ';' || *cptr == '/' || *cptr == '?' ||
          *cptr == ':' || *cptr == '@' || *cptr == '&' ||
          *cptr == '=' || *cptr == '+' || *cptr == '$' ||
          *cptr == ',' || *cptr == '[' || *cptr == ']' ))) {
      
      buf.append(*cptr);
      
    } else {
      
      buf.append(X("%"));
      // if the upper 8 bits of the XMLCh are less than 10 (covers all of 8-bit ascii)
      if ((*cptr >> 4) < 10)
        buf.append((XMLCh)('0' + (*cptr >> 4)));
      else // covers extended ascii
        buf.append((XMLCh)('A' - 10 + (*cptr >> 4)));

      // bitwise-and the 16-bit XMLCh with octal F, 11111111
      // we are checking the lower 8-bits
      if ((*cptr & 0xF) < 10)
        buf.append((XMLCh)('0' + (*cptr & 0xF)));
      else
        buf.append((XMLCh)('A' - 10 + (*cptr & 0xF)));
    }
      
  }//for  

  return memMgr->getPooledString(buf.getRawBuffer());
}

bool XPath2Utils::isValidURI(const XMLCh* const str, MemoryManager* memMgr)
{
  // XMLSchema specs say: "Spaces are, in principle, allowed in the lexical space of anyURI, however, 
  // their use is highly discouraged (unless they are encoded by %20)"
  // Xerces complains if a space is found, so let's encode it
  const XMLCh escSpace[]={ chPercent, chDigit_2, chDigit_0, chNull };
  XMLBuffer buff(1023, memMgr);
  const XMLCh* pCursor=str;
  while(*pCursor)
  {
    if(*pCursor==chSpace)
      buff.append(escSpace);
    else
      buff.append(*pCursor);
    pCursor++;
  }
  return XMLUri::isValidURI(true, buff.getRawBuffer());
}

const XMLCh* XPath2Utils::concatStrings(const XMLCh* src1, const XMLCh src, XPath2MemoryManager* memMgr) {
  XMLCh dummy[2] = {src, chNull};
  return XPath2Utils::concatStrings(src1, dummy, memMgr);
}

const XMLCh* XPath2Utils::concatStrings(const XMLCh* src1, const XMLCh* src2, XPath2MemoryManager* memMgr) {

  XMLBuffer buffer(1023, memMgr);
  buffer.set(src1);
  buffer.append(src2);

  return memMgr->getPooledString(buffer.getRawBuffer());
}

const XMLCh* XPath2Utils::concatStrings(const XMLCh* src1, const XMLCh* src2, const XMLCh* src3, XPath2MemoryManager* memMgr) {

  XMLBuffer buffer(1023, memMgr);
  buffer.set(src1);
  buffer.append(src2);
  buffer.append(src3);

  return memMgr->getPooledString(buffer.getRawBuffer());
}

const XMLCh* XPath2Utils::asStr(const XMLCh ch, XPath2MemoryManager* memMgr) {

  XMLCh newStr[2] = {ch, chNull};
  return memMgr->getPooledString(newStr);
}

const XMLCh* XPath2Utils::subString(const XMLCh* src, unsigned int offset, unsigned int count, XPath2MemoryManager* memMgr) {

  if (src == 0) {
    XQThrow2(MiscException,X("XPath2Utils:subString"),X("Cannot take substring of null string"));
  }

	XMLCh *newStr = new XMLCh [ count + 1 ];
  XMLString::subString(newStr, src, offset, offset + count);
  const XMLCh* retval=memMgr->getPooledString(newStr);
  delete[] newStr;
  return retval;
}

const XMLCh* XPath2Utils::deleteData( const XMLCh* const target, unsigned int offset, unsigned int count, XPath2MemoryManager* memMgr) {

  if (target == 0) {
    return 0;
  }

  unsigned int targetSize = XMLString::stringLen(target); 
  unsigned int newSize =  targetSize - count;
  AutoDeleteArray<XMLCh> stringGuard(new XMLCh [newSize + 1]);
  XMLCh *newString = stringGuard;

  XMLString::copyNString(newString, target, offset);// * sizeof(XMLCh));
  XMLString::copyNString(newString + offset, target + offset + count, ( targetSize - offset - count));//*sizeof(XMLCh));
  newString[newSize] = 0;
  const XMLCh* retval = memMgr->getPooledString(newString);
  return retval;
}

const XMLCh* XPath2Utils::toLower( const XMLCh* const target, XPath2MemoryManager* memMgr) {
  XMLCh *newStr = XMLString::replicate(target);
  XMLString::lowerCase(newStr);
  const XMLCh* retval=memMgr->getPooledString(newStr);
  XMLString::release(&newStr);
  return retval;
}

const XMLCh* XPath2Utils::toUpper( const XMLCh* const target, XPath2MemoryManager* memMgr) {
  XMLCh *newStr = XMLString::replicate(target);
  XMLString::upperCase(newStr);
  const XMLCh* retval=memMgr->getPooledString(newStr);
  XMLString::release(&newStr);
  return retval;
}

const XMLCh* XPath2Utils::toCollapsedWS(const XMLCh* const target, XPath2MemoryManager* memMgr) {
  XMLCh *newStr = XMLString::replicate(target);
  XMLString::collapseWS(newStr);
  const XMLCh* retval=memMgr->getPooledString(newStr);
  XMLString::release(&newStr);
  return retval;
}

const XMLCh* XPath2Utils::normalizeEOL(const XMLCh* const src, XPath2MemoryManager* memMgr) {
    int len=XMLString::stringLen(src);
	int j=0;
    XMLCh* dst=(XMLCh*)memMgr->allocate((len+1)*sizeof(XMLCh*));
    // A.2.3 End-of-Line Handling
    // For [XML 1.0] processing, all of the following must be translated to a single #xA character:
    //  1. the two-character sequence #xD #xA
    //  2. any #xD character that is not immediately followed by #xA.
	for(int i=0;i<len;i++)
	{
        if (src[i]== chCR && i<len && src[i+1]== chLF)
        {
			dst[j++]=chLF;
            i++;
        }
        else if(src[i]== chCR)
			dst[j++]=chLF;
        else
            dst[j++]=src[i];
    }
	dst[j++]=0;
    return dst;
}

std::vector<const XMLCh*> XPath2Utils::getVal(const XMLCh* values, XPath2MemoryManager* memMgr){

  std::vector<const XMLCh*> valList;
  bool munchWS = true; // munch initial WS
  unsigned int start = 0;

  
  /* XPath requires this bizarre WS separated splitting of the string, as the
     string can hold many id's. */
  int valuesLen = XMLString::stringLen(values);
  

  
  for(int i = 0; i < valuesLen; i++) {
    switch(values[i]) {
    case 0x0020:
    case 0x0009:
    case 0x000d:
    case 0x000a: {
      if(!munchWS) {
	      munchWS = true;
	      // Found the end of a value, so add it to a vector.
	      valList.push_back(subString(values, start, i-start, memMgr));
      }
      break;
    }
    default: {
      if(munchWS) {
	      //found the start of an ID
	      start = i;
	      munchWS = false;
      }
    }
    
    }
  }
  if(!munchWS) {
    // Found the end of a value, so add it to the list of values.
    valList.push_back(subString(values, start, valuesLen-start, memMgr));
  }
  return valList;
}

bool XPath2Utils::containsString(std::vector<const XMLCh*> values, const XMLCh* val) { 
  for (std::vector<const XMLCh*>::const_iterator it=values.begin();it!=values.end();it++)
    if (XPath2Utils::equals(val, *it))
      return true;
  return false;
}
