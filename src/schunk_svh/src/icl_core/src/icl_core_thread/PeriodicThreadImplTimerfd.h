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
 * \author  Lars Pfotzer <pfotzer@fzi.de>
 * \date    2010-02-08
 *
 * \brief   Contains icl_core::thread::PeriodicThreadImplTimerfd
 *
 * \b icl_core::thread::PeriodicThreadImplTimerfd
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_THREAD_PERIODIC_THREAD_IMPL_TIMERFD_H_INCLUDED
#define ICL_CORE_THREAD_PERIODIC_THREAD_IMPL_TIMERFD_H_INCLUDED

#include "PeriodicThreadImpl.h"

namespace icl_core {
namespace thread {

class PeriodicThreadImplTimerfd : public PeriodicThreadImpl, protected virtual icl_core::Noncopyable
{
public:
  explicit PeriodicThreadImplTimerfd(const icl_core::TimeSpan& period);
  virtual ~PeriodicThreadImplTimerfd();

  virtual void makePeriodic();
  virtual icl_core::TimeSpan period() const { return m_period; }
  virtual bool setPeriod(const icl_core::TimeSpan& period);
  virtual void waitPeriod();

private:
  struct periodic_info
  {
    int timer_fd;
    unsigned long long wakeups_missed;
  };
  struct periodic_info *m_info;

  icl_core::TimeSpan m_period;
  bool timer_created;

};

}
}

#endif
