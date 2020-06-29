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
 * \author  Kay-Ulrich Scholl <scholl@fzi.de>
 * \author  Klaus Uhl <uhl@fzi.de>
 * \date    2010-07-01
 *
 * \brief   Contains icl_core::thread::ThreadImpl for RTAI/LXRT 3.5
 *
 * \b icl_core::thread::ThreadImpl for RTAI/LXRT 3.5
 *
 * Wrapper class for thread implementation.
 * Uses system dependent tTheradImpl class.
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_THREAD_THREAD_IMPL_LXRT35_H_INCLUDED
#define ICL_CORE_THREAD_THREAD_IMPL_LXRT35_H_INCLUDED

#include <rtai_posix.h>

#include <icl_core/os_thread.h>

#include "icl_core_thread/ThreadImpl.h"

namespace icl_core {
namespace thread {

class Thread;

/*! Implements thread functionality for RTAI/LXRT systems. Have a look
 *  at documentation of basic class Thread for informations about the
 *  specific functions.
 */
class ThreadImplLxrt35 : public ThreadImpl, protected virtual icl_core::Noncopyable
{
public:
  ThreadImplLxrt35(Thread *thread, const icl_core::String& description,
                   icl_core::ThreadPriority priority);

  virtual ~ThreadImplLxrt35();

  virtual void cancel();
  virtual icl_core::String getDescription() const { return m_description; }
  virtual bool isHardRealtime() const;
  virtual bool executesHardRealtime() const;
  virtual void join();
  virtual icl_core::ThreadPriority priority() const;
  virtual void setDescription(const icl_core::String& description) { m_description = description; }
  virtual bool setHardRealtime(bool hard_realtime);
  virtual bool setPriority(icl_core::ThreadPriority priority);
  virtual bool start();
  virtual icl_core::ThreadId threadId() const;

private:
  static void *runThread(void *arg);

  pthread_t m_thread_id;
  Thread *m_thread;
  ThreadPriority m_priority;
  icl_core::String m_description;

  RT_TASK *m_rt_task;

  pthread_barrier_t *m_rt_start_sync;
};

}
}

#endif
