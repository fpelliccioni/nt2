//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::cons function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>






NT2_TEST_CASE_TPL( assign, BOOST_SIMD_TYPES )
{
  nt2::table<T> a = nt2::_(T(1), T(6));
  nt2::table<T> b = nt2::cons(T(1), T(2), T(3), T(4), T(5), T(6));
  nt2::table<T> c = nt2::cons(nt2::of_size(6, 1), T(1), T(2), T(3), T(4), T(5), T(6));
  nt2::table<T> d = nt2::cons(nt2::of_size(2, 3), T(1), T(2), T(3), T(4), T(5), T(6));
//  nt2::table<T> e = nt2::cons_row(nt2::of_size(2, 3), T(1), T(2), T(3), T(4), T(5), T(6));
  NT2_TEST_EQUAL(a, b);
  NT2_TEST_EQUAL(nt2::colvect(a), c);
  NT2_TEST_EQUAL(nt2::reshape(a, 3, 2), c);
  NT2_TEST_EQUAL(nt2::trans(nt2::reshape(a, 3, 2)), c);

}
