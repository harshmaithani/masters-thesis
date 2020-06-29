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
 * \date    2009-02-02
 */
//----------------------------------------------------------------------
#include "SemaphoreImplDarwin.h"

#include <mach/mach_init.h>
#include <mach/task.h>

#include "Common.h"

namespace icl_core {
namespace thread {

SemaphoreImplDarwin::SemaphoreImplDarwin(size_t initial_value)
  :m_semaphore(0)
{
  semaphore_create(mach_task_self(), &m_semaphore, SYNC_POLICY_FIFO, initial_value);
}

SemaphoreImplDarwin::~SemaphoreImplDarwin()
{
  semaphore_destroy(mach_task_self(), m_semaphore);
  m_semaphore = 0;
}

void SemaphoreImplDarwin::post()
{
  semaphore_signal(m_semaphore);
}

bool SemaphoreImplDarwin::tryWait()
{
    return wait(icl_core::TimeSpan(0, 0));
}

bool SemaphoreImplDarwin::wait()
{
  kern_return_t res = semaphore_wait(m_semaphore);
  return (res == KERN_SUCCESS);
}

bool SemaphoreImplDarwin::wait(const icl_core::TimeSpan& timeout)
{
    mach_timespec_t timeout_spec = timeout.machTimespec();
    kern_return_t res = semaphore_timedwait(m_semaphore, timeout_spec);
    return (res == KERN_SUCCESS);
}

bool SemaphoreImplDarwin::wait(const icl_core::TimeStamp& timeout)
{
    return wait(impl::getRelativeTimeout(timeout));
}

}
}
