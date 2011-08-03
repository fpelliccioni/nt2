//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 bitwise toolbox - lo/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/bitwise/include/lo.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>
typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<lo_> from bitwise
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::lo_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n3 {
  typedef boost::simd::uint64_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n4 {
  typedef boost::simd::int64_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n5 {
  typedef boost::simd::uint32_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n6 {
  typedef boost::simd::int32_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n7 {
  typedef boost::simd::uint16_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}
namespace n8 {
  typedef boost::simd::int16_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(lo_,(RS(vT,T(0),T(10))))
}

#undef RS
