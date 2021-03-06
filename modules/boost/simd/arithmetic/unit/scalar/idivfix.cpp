//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - idivfix/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <boost/simd/toolbox/arithmetic/include/functions/idivfix.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/trunc.hpp>
#include <boost/simd/include/functions/toint.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( idivfix_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::idivfix;
  using boost::simd::tag::idivfix_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<idivfix_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_integer<typename boost::common_type<T,T>::type>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivfix(T(-4),T(0)), boost::simd::Valmin<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(T(4),T(0)), boost::simd::Valmax<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(T(4),T(3)), T(1), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Nan<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( idivfix_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::idivfix;
  using boost::simd::tag::idivfix_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<idivfix_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_integer<typename boost::common_type<T,T>::type>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivfix(T(4),T(3)), T(1), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Nan<T>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( idivfix_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::idivfix;
  using boost::simd::tag::idivfix_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<idivfix_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_integer<typename boost::common_type<T,T>::type>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivfix(T(4),T(3)), T(1), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(idivfix(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Nan<T>(), 0);
} // end of test for signed_int_
