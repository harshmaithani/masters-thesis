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
 * \author  Dennis Nienhüser <nienhues@fzi.de>
 * \author  Thomas Schamm <schamm@fzi.de>
 * \date    2009-11-22
 *
 * \brief   Contains tPluginManager
 *
 * \b icl_core::plugin::tPluginManager
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_PLUGIN_T_PLUGIN_MANAGER_H_INCLUDED
#define ICL_CORE_PLUGIN_T_PLUGIN_MANAGER_H_INCLUDED

#include "icl_core/Deprecate.h"
#include "icl_core_plugin/PluginManager.h"

namespace icl_core {
namespace plugin {

template <class T, const char* const plugin_dir>
class ICL_CORE_VC_DEPRECATE tPluginManager : public PluginManager<T, plugin_dir>
{
public:
  //! Singleton instance accessor.
  static PluginManager<T, plugin_dir> *Instance()
  {
    return PluginManager<T, plugin_dir>::instance();
  }

protected:
  //! Protected default constructor.
  tPluginManager()
    : PluginManager<T, plugin_dir>()
  { }
} ICL_CORE_GCC_DEPRECATE;

}
}

#endif
