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
#ifndef ICL_CORE_MAP_H_INCLUDED
#define ICL_CORE_MAP_H_INCLUDED

#include <map>

namespace icl_core
{

// \todo Create a wrapper class (and/or additional RT-safe implementations).
template <typename TKey, typename TValue>
class Map : public std::map<TKey, TValue>
{
public:
  Map() : std::map<TKey, TValue>() { }
  Map(const Map& c) : std::map<TKey, TValue>(c) { }
  Map(const std::map<TKey, TValue>& c) : std::map<TKey, TValue>(c) { }
  template <typename TInputIterator>
  Map(TInputIterator start, TInputIterator end) : std::map<TKey, TValue>(start, end) { }
};

}

#endif
