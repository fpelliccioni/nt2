//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SCALAR_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SCALAR_UNALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/toolbox/memory/functions/unaligned_load.hpp>
#include <boost/simd/toolbox/memory/functions/scalar/load.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_REGISTER_DISPATCH_TO ( boost::simd::tag::unaligned_load_
                                  , tag::cpu_
                                  , (A0)(A1)(A2)
                                  , (iterator_< unspecified_<A0> >)
                                    (scalar_< fundamental_<A1> >)
                                    (target_< unspecified_<A2> >)
                                  , functor<boost::simd::tag::load_>
                                  );

  BOOST_SIMD_REGISTER_DISPATCH_TO ( boost::simd::tag::unaligned_load_
                                  , tag::cpu_
                                  , (A0)(A1)(A2)
                                  , (fusion_sequence_<A0>)
                                    (generic_< integer_<A1> >)
                                    ((target_< fusion_sequence_<A2> >))
                                  , functor<boost::simd::tag::load_>
                                  );
} } }

#endif
