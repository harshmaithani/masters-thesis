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
 * \date    2008-04-13
 *
 * \brief   Contains icl_core::logging::ThreadImpl
 *
 * \b icl_core::logging::ThreadImpl
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_LOGGING_THREAD_IMPL_H_INCLUDED
#define ICL_CORE_LOGGING_THREAD_IMPL_H_INCLUDED

#include <icl_core/Noncopyable.h>

namespace icl_core {
namespace logging {

class ThreadImpl : protected virtual icl_core::Noncopyable
{
public:
  virtual ~ThreadImpl() {}

  virtual void join() = 0;
  virtual bool start() = 0;
};

}
}

#endif
