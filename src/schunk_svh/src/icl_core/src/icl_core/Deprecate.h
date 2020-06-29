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
 * \date    2010-06-30
 *
 * \brief   Contains macros to deprecate classes, types, functions and variables.
 *
 * Deprecation warnings can be disabled by compiling with the
 * ICL_CORE_NO_DEPRECATION macro defined.
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_DEPRECATE_H_INCLUDED
#define ICL_CORE_DEPRECATE_H_INCLUDED

// Define deprecation macros for Visual Studio.
#if defined(_MSC_VER) && !defined(ICL_CORE_NO_DEPRECATION)
# define ICL_CORE_VC_DEPRECATE __declspec(deprecated)
# define ICL_CORE_VC_DEPRECATE_COMMENT(arg) __declspec(deprecated(arg))
#else
# define ICL_CORE_VC_DEPRECATE
# define ICL_CORE_VC_DEPRECATE_COMMENT(arg)
#endif

// Define deprecation macros for GCC.
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)) && !defined(ICL_CORE_NO_DEPRECATION)
# define ICL_CORE_GCC_DEPRECATE __attribute__((deprecated))
# if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#  define ICL_CORE_GCC_DEPRECATE_COMMENT(arg) __attribute__((deprecated(arg)))
# else
#  define ICL_CORE_GCC_DEPRECATE_COMMENT(arg) __attribute__((deprecated))
# endif
#else
# define ICL_CORE_GCC_DEPRECATE
# define ICL_CORE_GCC_DEPRECATE_COMMENT(arg)
#endif

// Special comment for deprecation due to obsolete style.
#define ICL_CORE_VC_DEPRECATE_STYLE ICL_CORE_VC_DEPRECATE_COMMENT("Please follow the new Coding Style Guidelines.")
#define ICL_CORE_GCC_DEPRECATE_STYLE ICL_CORE_GCC_DEPRECATE_COMMENT("Please follow the new Coding Style Guidelines.")

// Special comment for deprecation due to obsolete style which
// provides the name of the function that superseded the obsolete one.
#define ICL_CORE_VC_DEPRECATE_STYLE_USE(arg) ICL_CORE_VC_DEPRECATE_COMMENT("Please follow the new Coding Style Guidelines and use " #arg " instead.")
#define ICL_CORE_GCC_DEPRECATE_STYLE_USE(arg) ICL_CORE_GCC_DEPRECATE_COMMENT("Please follow the new Coding Style Guidelines and use " #arg " instead.")

#endif
