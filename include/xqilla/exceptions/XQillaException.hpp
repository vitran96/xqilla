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

#ifndef __XQILLAEXCEPTION_HPP
#define __XQILLAEXCEPTION_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xercesc/dom/DOMXPathException.hpp>
#include <xercesc/util/XMLString.hpp>

/**
 * The <code>XQillaException</code> interface extends the <code>DOMXPathException</code>
 * allowing an additional exception of type <code>RUNTIME_ERR</code> to be thrown.
 * @since DOM Level 3
 */
class XQILLA_API XQillaException: public XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathException
{
public:
  // -----------------------------------------------------------------------
  //  Constructors
  // -----------------------------------------------------------------------
  /** @name Constructors */
  //@{
  /**
   * Constructor which takes an error code and a message.
   *
   * @param code The error code which indicates the exception
   * @param message The string containing the error message
   */
  XQillaException(short code, const XMLCh* message): 
      XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathException(code, XERCES_CPP_NAMESPACE_QUALIFIER XMLString::replicate(message)) {};

  /**
   * Copy constructor.
   *
   * @param other The object to be copied.
   */
  XQillaException(const XQillaException &other);
  //@}

  // -----------------------------------------------------------------------
  //  Destructors
  // -----------------------------------------------------------------------
  /** @name Destructor */
  //@{
  /**
   * Destructor for XQillaException.
   *
   */
  virtual ~XQillaException();
  //@}
  
  //@{
  /**
   * ExceptionCode
   * RUNTIME_ERR If XQilla encounters a runtime exception
   */
  enum valExtension {
     RUNTIME_ERR = 53
   };
  //@}

  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------
  
  /** @name Getter methods */
  //@{  

  /**
   * Returns the code associated with this exception.
   *
   * @return the exception code
   */
  virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMXPathException::ExceptionCode getCode(void) const;
  
  /**
   * Returns the string representing the exception's error message.
   *
   * @return the error message
   */
  virtual const XMLCh* getString(void) const;
  //@}
  
  /** @name Getter methods */
  //@{  
  /**
   * Statically returns whether or not XQillaExceptions have debug on
   *
   * @return debug
   */
  static bool getDebug(void);
  //@}

  // -----------------------------------------------------------------------
  //  Setter methods
  // -----------------------------------------------------------------------
  
  /** @name Setter methods */
  //@{
  /** Set the 'debug' flag
   *
   * This method allows users to enable or disable debug on XQillaExceptions.
   *
   * @param debug The value specifying whether or not debug is enabled
   */
  static void setDebug(bool flag);
  //@}

private:
  static bool _debug;
};//XQillaException

#endif //__XQILLAEXCEPTION_HPP
