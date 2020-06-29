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
 * \date    2012-02-15
 *
 */
//----------------------------------------------------------------------
#include "icl_core_dispatch/CallbackOperation.h"

namespace icl_core {
namespace dispatch {

CallbackOperation::CallbackOperation(boost::function<void ()> const & callback)
  : m_callback(callback)
{
}

CallbackOperation::~CallbackOperation()
{
}

void CallbackOperation::execute()
{
  m_callback();
}

}}
