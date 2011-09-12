//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_IS_COMPOSITE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_IS_COMPOSITE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

////////////////////////////////////////////////////////////////////////////////
// For a given type, return a reference or const reference type that can be
// returned after Level dereferencing
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<typename Buffer, std::size_t Level = 1UL> 
  struct reference_;

  template<typename Buffer, std::size_t Level = 1UL> 
  struct const_reference_;
} }

#endif
