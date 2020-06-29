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
 */
//----------------------------------------------------------------------
#include "ThreadImplLxrt38.h"

#include <icl_core/internal_raw_debug.h>
#include <icl_core/os_lxrt.h>

#include "Thread.h"
#include "Logging.h"

#define DEFAULT_STACK_SIZE 0x4000

namespace icl_core {
namespace thread {

ThreadImplLxrt38::ThreadImplLxrt38(Thread *thread, const icl_core::String& description,
                                   icl_core::ThreadPriority priority)
  : m_thread_id(0),
    m_thread(thread),
    m_priority(priority),
    m_description(description),
    m_rt_task(NULL),
    m_rt_start_sync(NULL)
{ }

ThreadImplLxrt38::~ThreadImplLxrt38()
{
  // Ensure that the thread is really destroyed.
  join();

  if (m_rt_start_sync == NULL)
  {
    // Nothing to be done here.
  }
  else
  {
    rt_sem_delete(m_rt_start_sync);
    m_rt_start_sync = NULL;
  }
}

void ThreadImplLxrt38::cancel()
{
  if (m_thread_id == 0)
  {
    // Nothing to be done here. The thread has already been destroyed.
  }
  else
  {
    pthread_cancel_rt(m_thread_id);
    pthread_join_rt(m_thread_id, NULL);
    m_thread_id = 0;
    m_rt_task = NULL;
  }
}

bool ThreadImplLxrt38::isHardRealtime() const
{
  return m_priority < 0;
}

bool ThreadImplLxrt38::executesHardRealtime() const
{
  return os::isThisHRT();
}

void ThreadImplLxrt38::join()
{
  if (m_thread_id == 0)
  {
    // Nothing to be done here. The thread has already been destroyed.
  }
  else
  {
    pthread_join_rt(m_thread_id, NULL);
    m_thread_id = 0;
    m_rt_task = NULL;
  }
}

icl_core::ThreadPriority ThreadImplLxrt38::priority() const
{
  return m_priority;
}

bool ThreadImplLxrt38::setHardRealtime(bool hard_realtime)
{
  if (hard_realtime && !os::isThisHRT())
  {
    rt_make_hard_real_time();
    return os::isThisHRT();
  }
  else if (!hard_realtime && os::isThisHRT())
  {
    rt_make_soft_real_time();
    return !os::isThisHRT();
  }
  else
  {
    return false;
  }
}

bool ThreadImplLxrt38::setPriority(icl_core::ThreadPriority /*priority*/)
{
  // TODO: Make this work!
  /*
    if (m_rt_task != NULL) {
    int ret = rt_change_prio(m_rt_task, abs(priority));
    if (ret == 0) {
    m_priority = priority;

    if (priority > 0 && IsHardRealtimeThread()) {
    rt_make_soft_real_time();
    } else if (priority < 0 && !IsHardRealtimeThread()) {
    rt_make_hard_real_time();
    }

    return true;
    }
    }
  */

  return false;
}

bool ThreadImplLxrt38::start()
{
  m_rt_start_sync = rt_typed_sem_init(size_t(this), 2, CNT_SEM | PRIO_Q);
  if (m_rt_start_sync == NULL)
  {
    // We cannot proceed, if this happens!
  }
  else
  {
    if (pthread_create(&m_thread_id, NULL, ThreadImplLxrt38::runThread, this))
    {
      m_thread_id = 0;
      m_rt_task = NULL;

      rt_sem_delete(m_rt_start_sync);
      m_rt_start_sync = NULL;
    }
    else
    {
      rt_sem_wait_barrier(m_rt_start_sync);
    }
  }

  return m_thread_id != 0;
}

icl_core::ThreadId ThreadImplLxrt38::threadId() const
{
  return ::icl_core::ThreadId(m_thread_id);
}

void * ThreadImplLxrt38::runThread(void *arg)
{
  ThreadImplLxrt38 *self = static_cast<ThreadImplLxrt38*>(arg);

  if (self->m_rt_start_sync == NULL)
  {
    // Technically, this can never happen because this condition is
    // already checked in the Start() function. But who knows!
    PRINTF("ERROR: NULL thread start barrier!\n");
  }
  else
  {
    self->m_rt_task = rt_task_init(getpid() + pthread_self_rt(), abs(self->m_priority),
                                   DEFAULT_STACK_SIZE, 0);
    if (self->m_rt_task == NULL)
    {
      PRINTF("ERROR: Cannot initialize LXRT task %lu!\n", self->m_thread_id);
      PRINTF("       Probably another thread with the same name already exists.\n");

      // Let the thread, which started us, continue!
      rt_sem_wait_barrier(self->m_rt_start_sync);
    }
    else
    {
      if (self->m_priority < 0)
      {
        rt_make_hard_real_time();
        if (!rt_is_hard_real_time(rt_buddy()))
        {
          PRINTF("ERROR: Setting thread %lu to hard real-time failed!\n", self->m_thread_id);
        }
        else
        {
          // Everything worked as expected, so no message here.
        }
      }
      else
      {
        // This is a soft realtime thread, so nothing additional has
        // to be done here.
      }

      rt_sem_wait_barrier(self->m_rt_start_sync);

      self->m_thread->runThread();

      // Remark: It does not hurt to call this in a soft realtime
      // thread, so just skip the hard realtime test.
      rt_make_soft_real_time();
    }
  }

  return NULL;
}

}
}
