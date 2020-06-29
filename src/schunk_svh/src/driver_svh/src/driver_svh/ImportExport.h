// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// This file is part of the SCHUNK SVH Driver suite.
//
// This program is free software licensed under the LGPL
// (GNU LESSER GENERAL PUBLIC LICENSE Version 3).
// You can find a copy of this license in LICENSE folder in the top
// directory of the source code.
//
// © Copyright 2014 SCHUNK Mobile Greifsysteme GmbH, Lauffen/Neckar Germany
// © Copyright 2014 FZI Forschungszentrum Informatik, Karlsruhe, Germany
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Lars Pfotzer
 * \date    2014-01-30
 *
 * Defines used for windows DLL support.
 */
//----------------------------------------------------------------------
#ifndef DRIVER_SVH_IMPORT_EXPORT_H_INCLUDED
#define DRIVER_SVH_IMPORT_EXPORT_H_INCLUDED

#if defined(_SYSTEM_WIN32_) && !defined(_IC_STATIC_)
#  pragma warning ( disable : 4251 )

# if defined DRIVER_SVH_EXPORT_SYMBOLS
#  define DRIVER_SVH_IMPORT_EXPORT __declspec(dllexport)
# else
#  define DRIVER_SVH_IMPORT_EXPORT __declspec(dllimport)
# endif

#elif defined(__GNUC__) && (__GNUC__ > 3) && !defined(_IC_STATIC_)

# define DRIVER_SVH_IMPORT_EXPORT __attribute__ ((visibility("default")))

#else

# define DRIVER_SVH_IMPORT_EXPORT

#endif

#endif
