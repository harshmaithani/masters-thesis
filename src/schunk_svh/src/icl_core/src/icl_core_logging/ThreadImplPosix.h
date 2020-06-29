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
 * \brief   Contains icl_core::logging::ThreadImplPosix
 *
 * \b icl_core::logging::ThreadImplPosix
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_LOGGING_THREAD_IMPL_POSIX_H_INCLUDED
#define ICL_CORE_LOGGING_THREAD_IMPL_POSIX_H_INCLUDED

#include <pthread.h>

#include <icl_core/os_thread.h>

#include "ThreadImpl.h"

namespace icl_core {
namespace logging {

class Thread;

class ThreadImplPosix : public ThreadImpl, protected virtual icl_core::Noncopyable
{
public:
  ThreadImplPosix(Thread *thread, icl_core::ThreadPriority priority);
  virtual ~ThreadImplPosix();

  virtual void join();
  virtual bool start();

private:
  static void *runThread(void *arg);

  pthread_t m_thread_id;
  Thread *m_thread;
  icl_core::ThreadPriority m_priority;
};

}
}

#endif
