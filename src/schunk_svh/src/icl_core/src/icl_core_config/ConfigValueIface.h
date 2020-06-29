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
 * \date    2010-04-28
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_CONFIG_CONFIG_VALUE_IFACE_H_INCLUDED
#define ICL_CORE_CONFIG_CONFIG_VALUE_IFACE_H_INCLUDED

#include <icl_core/BaseTypes.h>

namespace icl_core {
namespace config {

namespace impl {
/*! Abstract interface for reading configuration parameters.
 */
class ConfigValueIface
{
public:
  virtual ~ConfigValueIface() { }

  virtual bool get(std::string const & prefix = "",
                   icl_core::logging::LogStream& log_stream = icl_core::logging::Nirwana::instance()) const = 0;
  virtual icl_core::String key() const = 0;
  virtual icl_core::String stringValue() const = 0;
};

}}}

#endif
