//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.reduction toolbox - is_included_c/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/reduction/include/functions/is_included_c.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/complement.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( is_included_c_integer__2_0,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::is_included_c;
  using boost::simd::tag::is_included_c_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_included_c_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(is_included_c(boost::simd::Mone<vT>(),boost::simd::Zero<vT>()), boost::simd::True<sr_t>());
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<vT>(),boost::simd::Mone<vT>()), boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<vT>(),boost::simd::Three<vT>()), boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<vT>(),boost::simd::Two<vT>()), boost::simd::True<sr_t>());
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::True<sr_t>());
  NT2_TEST_EQUAL(is_included_c(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::True<sr_t>());
} // end of test for integer_
