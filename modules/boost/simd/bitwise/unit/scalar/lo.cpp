//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - lo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/lo.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


NT2_TEST_CASE_TPL ( lo_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(lo(boost::simd::Nan<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(lo(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(lo(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( lo_int64__1_0,  (boost::simd::int64_t)(boost::simd::uint64_t))
{
  
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(lo(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(lo(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for int64_

NT2_TEST_CASE_TPL ( lo_int32__1_0,  (boost::simd::int32_t)(boost::simd::uint32_t))
{
  
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(lo(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(lo(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for int32_

NT2_TEST_CASE_TPL ( lo_int16__1_0,  (boost::simd::int16_t)(boost::simd::uint16_t))
{
  
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(lo(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(lo(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for int16_
