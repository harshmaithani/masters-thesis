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
 * \date    2010-06-16
 *
 */
//----------------------------------------------------------------------

#include <QtCore/QCoreApplication>
#include <QtCore/QString>

#include <icl_core/tString.h>
#include <icl_core_config/Config.h>

#include "UdpLoggingServer.h"

int main(int argc, char *argv[])
{
  icl_core::config::addParameter(
    icl_core::config::ConfigParameter("filename:", "f", "/Filename",
                                       "The filename of the log database."));
  icl_core::config::initialize(argc, argv);
  icl_core::String db_filename;
  if (!icl_core::config::get<icl_core::String>("/Filename", db_filename))
  {
    std::cerr << "No database file specified!" << std::endl << std::endl;
    icl_core::config::Getopt::instance().printHelp();
    return 1;
  }

  QCoreApplication app(argc, argv);
  UdpLoggingServer uls(QString::fromStdString(db_filename));
  return app.exec();
}
