// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// This file is part of FZIs ic_workspace.
//
// This program is free software licensed under the LGPL
// (GNU LESSER GENERAL PUBLIC LICENSE Version 3).
// You can find a copy of this license in LICENSE folder in the top
// directory of the source code.
//
// © Copyright 2014 FZI Forschungszentrum Informatik, Karlsruhe, Germany
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Klaus Uhl <uhl@fzi.de>
 * \date    2011-12-12
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_DISPATCH_OPERATION_H_INCLUDED
#define ICL_CORE_DISPATCH_OPERATION_H_INCLUDED

#include "icl_core_dispatch/ImportExport.h"

namespace icl_core {
//! Dispatching framework.
namespace dispatch {

/** This is the base class for dispatchable operations. It is intended
 *  to be used together with the \c Dispatcher class.
 */
class ICL_CORE_DISPATCH_IMPORT_EXPORT Operation
{
public:
  //! Creates a new operation object.
  Operation();

  //! Destroys an operation object.
  virtual ~Operation();

  /** This methos is called by the dispatcher to perform the
   *  operation's task. It has to be overridden by all subclasses.
   */
  virtual void execute() = 0;
};

}
}

#endif
