//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - oneminus/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/oneminus.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


NT2_TEST_CASE_TPL ( oneminus_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::oneminus;
  using boost::simd::tag::oneminus_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<oneminus_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_signed<typename boost::result_of<boost::dispatch::meta::arithmetic(T)>::type>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Inf<T>()), -boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Minf<T>()), -boost::simd::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Mone<T>()), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Nan<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::One<T>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Zero<T>()), boost::simd::One<r_t>(), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( oneminus_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::oneminus;
  using boost::simd::tag::oneminus_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<oneminus_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_signed<typename boost::result_of<boost::dispatch::meta::arithmetic(T)>::type>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::One<T>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Zero<T>()), boost::simd::One<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( oneminus_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::oneminus;
  using boost::simd::tag::oneminus_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<oneminus_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_signed<typename boost::result_of<boost::dispatch::meta::arithmetic(T)>::type>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Mone<T>()), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::One<T>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(oneminus(boost::simd::Zero<T>()), boost::simd::One<T>(), 0);
} // end of test for signed_int_
