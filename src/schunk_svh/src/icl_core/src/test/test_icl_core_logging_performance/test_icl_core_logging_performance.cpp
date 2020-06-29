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
 * \date    2011-10-17
 *
 */
//----------------------------------------------------------------------
#include <icl_core/BaseTypes.h>
#include <icl_core/internal_raw_debug.h>
#include <icl_core/os_lxrt.h>
#include <icl_core_config/Config.h>
#include <icl_core_logging/Logging.h>
#include <icl_core_thread/Thread.h>

DECLARE_LOG_STREAM(PerformanceTest);
REGISTER_LOG_STREAM(PerformanceTest)

using icl_core::logging::Default;
using icl_core::logging::endl;

int main(int argc, char *argv[])
{
  icl_core::os::lxrtStartup();

  icl_core::config::addParameter(icl_core::config::ConfigParameter("message-count:", "c", "/TestLogging/MessageCount", "Number of messages to be logged."));

  icl_core::logging::initialize(argc, argv);

  size_t message_count = icl_core::config::getDefault<size_t>("/TestLogging/MessageCount", 100000);

  LOGGING_INFO(Default, "Running performance test with " << message_count << " iterations..." << endl);
  for (size_t i = 0; i < message_count; ++i)
  {
    LOGGING_INFO(PerformanceTest, "Test loop " << i << endl);
  }
  LOGGING_INFO(Default, "Performance test finished." << endl);

  icl_core::logging::tLoggingManager::instance().shutdown();
  icl_core::os::lxrtShutdown();

  return 0;
}
