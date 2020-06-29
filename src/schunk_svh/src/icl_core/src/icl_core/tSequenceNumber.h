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
 * \date    2011-04-07
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_T_SEQUENCE_NUMBER_H_INCLUDED
#define ICL_CORE_T_SEQUENCE_NUMBER_H_INCLUDED

#include "icl_core/Deprecate.h"
#include "icl_core/SequenceNumber.h"

namespace icl_core {

template <typename TBase, TBase max_value, TBase min_value = 0, TBase initial_value = min_value>
class ICL_CORE_VC_DEPRECATE tSequenceNumber : public SequenceNumber<TBase, max_value, min_value, min_value>
{
public:

  explicit tSequenceNumber(TBase value = initial_value)
    : SequenceNumber<TBase, max_value, min_value, min_value>(value)
  { }
  tSequenceNumber(const tSequenceNumber& other)
    : SequenceNumber<TBase, max_value, min_value, min_value>(other)
  { }

} ICL_CORE_GCC_DEPRECATE;

}

#endif
