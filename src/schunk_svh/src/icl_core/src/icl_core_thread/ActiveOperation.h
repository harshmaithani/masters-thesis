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
 * \date    2011-06-06
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_THREAD_ACTIVE_OPERATION_H_INCLUDED
#define ICL_CORE_THREAD_ACTIVE_OPERATION_H_INCLUDED

#include "icl_core_thread/ImportExport.h"

namespace icl_core {
namespace thread {

/*! An abstract base class for active object operations.
 */
struct ICL_CORE_THREAD_IMPORT_EXPORT ActiveOperation
{
  virtual ~ActiveOperation() {}

  /*! This method has to be implemented by subclasses.  It has to call
   *  the function implementing the active operation.
   */
  virtual void invoke() = 0;
};

}
}

#endif
