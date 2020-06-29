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
 * \author  Lars Pfotzer <pfotzer@fzi.de>
 * \date    2011-02-16
 *
 * \brief   Contains SequenceNumber
 *
 * \b SequenceNumber
 *
 * Implements a sequence number with a maximum value.
 *
 */
//----------------------------------------------------------------------

#include "SequenceNumber.h"

namespace icl_core {

////////////// DEPRECATED VERSIONS //////////////
#ifdef _IC_BUILDER_DEPRECATED_STYLE_

/*!
 * Get the maximum sequence number value.
 * \deprecated Obsolete coding style.
 */
template <typename TBase, TBase max_value, TBase min_value, TBase initial_value>
TBase SequenceNumber<TBase, max_value, min_value, initial_value>::MaxValue()
{
  return max_value;
}

/*!
 * Get the minimum sequence number value.
 * \deprecated Obsolete coding style.
 */
template <typename TBase, TBase max_value, TBase min_value, TBase initial_value>
TBase SequenceNumber<TBase, max_value, min_value, initial_value>::MinValue()
{
  return min_value;
}

#endif
/////////////////////////////////////////////////

}
