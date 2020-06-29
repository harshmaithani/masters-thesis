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
 * \date    2011-06-07
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_CONFIG_T_CONFIG_VALUES_H_INCLUDED
#define ICL_CORE_CONFIG_T_CONFIG_VALUES_H_INCLUDED

#include <icl_core/Deprecate.h>

#include "icl_core_config/ConfigValues.h"

namespace icl_core {
namespace config {

typedef ICL_CORE_VC_DEPRECATE impl::ConfigValueIface* tConfigValues[] ICL_CORE_GCC_DEPRECATE;

template <typename T>
class ICL_CORE_VC_DEPRECATE TConfigValue : public ConfigValue<T>
{
public:
  TConfigValue(const icl_core::String& key,
               typename icl_core::ConvertToRef<T>::ToRef value)
    : ConfigValue<T>(key, value)
  { }
  virtual ~TConfigValue() { }
} ICL_CORE_GCC_DEPRECATE;

template <typename T>
class ICL_CORE_VC_DEPRECATE TConfigEnum : public ConfigEnum<T>
{
public:
  TConfigEnum(const icl_core::String& key,
              typename icl_core::ConvertToRef<T>::ToRef value,
              const char * const *descriptions,
              const char *end_marker = NULL)
    : ConfigEnum<T>(key, value, descriptions, end_marker)
  { }
  virtual ~TConfigEnum() { }
} ICL_CORE_GCC_DEPRECATE;

template <typename T>
class ICL_CORE_VC_DEPRECATE TConfigValueDefault : public ConfigValueDefault<T>
{
public:
  TConfigValueDefault(const icl_core::String& key,
                      typename icl_core::ConvertToRef<T>::ToRef value,
                      typename icl_core::ConvertToRef<T>::ToConstRef default_value)
    : ConfigValueDefault<T>(key, value, default_value)
  { }
  virtual ~TConfigValueDefault() { }
} ICL_CORE_GCC_DEPRECATE;

template <typename T>
class ICL_CORE_VC_DEPRECATE TConfigEnumDefault : public ConfigEnumDefault<T>
{
public:
  TConfigEnumDefault(const icl_core::String& key,
                     typename icl_core::ConvertToRef<T>::ToRef value,
                     typename icl_core::ConvertToRef<T>::ToConstRef default_value,
                     const char * const *descriptions,
                     const char *end_marker = NULL)
    : ConfigEnumDefault<T>(key, value, default_value, descriptions, end_marker)
  { }
  virtual ~TConfigEnumDefault() { }
} ICL_CORE_GCC_DEPRECATE;

}
}

#endif
