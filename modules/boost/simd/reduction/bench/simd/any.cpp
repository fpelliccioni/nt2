//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 reduction toolbox - any/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/reduction/include/any.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>
typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<any_> from reduction
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::any_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(any_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(any_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}

#undef RS
