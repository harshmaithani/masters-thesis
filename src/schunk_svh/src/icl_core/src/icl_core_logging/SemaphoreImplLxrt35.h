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
 * \date    2010-06-30
 *
 * \brief   Contains icl_core::logging::SemaphoreImplLxrt35
 *
 * \b icl_core::logging::SemaphoreImplLxrt35
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_LOGGING_SEMAPHORE_IMPL_LXRT35_H_INCLUDED
#define ICL_CORE_LOGGING_SEMAPHORE_IMPL_LXRT35_H_INCLUDED

#include <rtai_posix.h>

#include "icl_core/BaseTypes.h"
#include "SemaphoreImpl.h"

namespace icl_core {
namespace logging {

class SemaphoreImplLxrt35 : public SemaphoreImpl, protected virtual icl_core::Noncopyable
{
public:
  SemaphoreImplLxrt35(size_t initial_value);
  virtual ~SemaphoreImplLxrt35();

  virtual void post();
  virtual bool wait();

private:
  sem_t *m_semaphore;
};

}
}

#endif
