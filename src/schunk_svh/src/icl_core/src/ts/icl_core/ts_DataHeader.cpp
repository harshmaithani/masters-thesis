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
 * \author  Florian Kuhnt <kuhnt@fzi.de>
 * \date    2014-04-11
 *
 */
//----------------------------------------------------------------------
#include <icl_core/DataHeader.h>

#include <icl_core/BaseTypes.h>

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>


using icl_core::DataHeader;
using icl_core::Stamped;
using icl_core::StampedBase;

BOOST_AUTO_TEST_SUITE(ts_DataHeader)

typedef boost::mpl::list<char, short, uint32_t, int, long, float, double> TestTypes;

BOOST_AUTO_TEST_CASE_TEMPLATE(DataHeaderCapacity, T, TestTypes)
{

  {
    boost::shared_ptr< Stamped<uint32_t> > test_data(new Stamped<uint32_t>);
    boost::shared_ptr<StampedBase> test2 = test_data;
    boost::dynamic_pointer_cast< Stamped<uint32_t> >(test2);
    Stamped<uint32_t>::Ptr test3 = boost::dynamic_pointer_cast<Stamped<uint32_t> >(test2);
  }

  {
    typename Stamped<T>::Ptr test_data(new Stamped<T>);
    StampedBase::Ptr test2 = test_data;
    typename Stamped<T>::Ptr test3 = boost::dynamic_pointer_cast<Stamped<T> >(test2);
  }

}

BOOST_AUTO_TEST_SUITE_END()
