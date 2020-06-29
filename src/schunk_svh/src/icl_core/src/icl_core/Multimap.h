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
 * \author  Jan Oberländer <oberlaen@fzi.de>
 * \date    2012-01-24
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_MULTIMAP_H_INCLUDED
#define ICL_CORE_MULTIMAP_H_INCLUDED

#include <map>

namespace icl_core
{

// \todo Create a wrapper class (and/or additional RT-safe implementations).
template <typename TKey, typename TValue>
class Multimap : public std::multimap<TKey, TValue>
{
public:
  Multimap() : std::multimap<TKey, TValue>() { }
  Multimap(const Multimap& c) : std::multimap<TKey, TValue>(c) { }
  Multimap(const std::multimap<TKey, TValue>& c) : std::multimap<TKey, TValue>(c) { }
  template <typename TInputIterator>
  Multimap(TInputIterator start, TInputIterator end) : std::multimap<TKey, TValue>(start, end) { }
};

}

#endif
