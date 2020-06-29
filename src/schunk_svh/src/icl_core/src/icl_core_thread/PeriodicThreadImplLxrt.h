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
 * \date    2009-12-07
 *
 * \brief   Defines icl_core::thread::PeriodicThreadImplLxrt
 *
 * \b icl_core::thread::PeriodicThreadImplLxrt
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_THREAD_PERIODIC_THREAD_IMPL_LXRT_H_INCLUDED
#define ICL_CORE_THREAD_PERIODIC_THREAD_IMPL_LXRT_H_INCLUDED

#include <icl_core/os_lxrt.h>

#if defined(_SYSTEM_LXRT_33_)
# include "icl_core_thread/PeriodicThreadImplLxrt33.h"
#elif defined(_SYSTEM_LXRT_35_)
# include "icl_core_thread/PeriodicThreadImplLxrt35.h"
#elif defined(_SYSTEM_LXRT_38_)
# include "icl_core_thread/PeriodicThreadImplLxrt38.h"
#else
# error "Unsupported RTAI version!"
#endif

namespace icl_core {
namespace thread {

#if defined(_SYSTEM_LXRT_33_)
typedef PeriodicThreadImplLxrt33 PeriodicThreadImplLxrt;
#elif defined(_SYSTEM_LXRT_35_)
typedef PeriodicThreadImplLxrt35 PeriodicThreadImplLxrt;
#elif defined(_SYSTEM_LXRT_38_)
typedef PeriodicThreadImplLxrt38 PeriodicThreadImplLxrt;
#endif

}
}

#endif
