//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - dist/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/arithmetic/include/functions/dist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( dist_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::dist;
  using nt2::tag::dist_;
  typedef std::complex<T> cT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<dist_(cT, cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef nt2::imaginary<T> ciT;
  typedef nt2::dry<T> dT;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );

  // specific values tests
  NT2_TEST_EQUAL(dist(cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), nt2::Nan<T>());
  NT2_TEST_EQUAL(dist(cT(nt2::One<T>()), cT(nt2::Zero<T>())), nt2::One<T>());
  NT2_TEST_EQUAL(dist(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())),nt2::Zero<T>());
  NT2_TEST_ULP_EQUAL(dist(cT(0, 1), cT(1, 0)), nt2::Sqrt_2<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(dist(cT(0, nt2::Inf<T>()), cT(nt2::Inf<T>(), 0)), nt2::Inf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(dist(nt2::Inf<dT>(),nt2::Inf<dT>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_EQUAL(dist(cT(1, 0), cT(1, 0)), nt2::Zero<T>());
  NT2_TEST_EQUAL(dist(cT(2, 1), ciT(1)), nt2::Two<T>());
  NT2_TEST_EQUAL(dist(ciT(1), ciT(0)), nt2::One<T>());
  NT2_TEST_EQUAL(dist(ciT(1), T(0)), nt2::One<T>());
} // end of test for floating_
