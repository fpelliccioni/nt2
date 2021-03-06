//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_CNP_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_CNP_HPP_INCLUDED

#include <nt2/toolbox/combinatorial/functions/cnp.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/split.hpp>
#include <nt2/include/functions/simd/group.hpp>
#include <nt2/sdk/meta/upgrade.hpp>

namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::cnp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<arithmetic_<A0>,X>))
//                       ((simd_<arithmetic_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return boost::simd::bitwise_cast<A0>(toint(cnp(tofloat(a0),tofloat(a1))));
//     }
//   };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::cnp_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type16_<A0>,X>))
                      ((simd_<type16_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::upgrade<A0> ::type utype;
      utype a00, a01, a10, a11;
      nt2::split(a0, a00, a01);
      nt2::split(a1, a10, a11);
      return nt2::group(cnp(a00,a10),cnp(a01,a11));
    }
  };

//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::cnp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<type8_<A0>,X>))
//                       ((simd_<type8_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       typedef typename meta::upgrade<A0> ::type utype;
//       utype a00, a01, a10, a11;
//       nt2::split(a0, a00, a01);
//       nt2::split(a1, a10, a11);
//       return nt2::group(cnp(a00,a10),cnp(a01,a11));
//     }
//   };

//   /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is floating_
// /////////////////////////////////////////////////////////////////////////////


//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::cnp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<floating_<A0>,X>))
//                       ((simd_<floating_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return map(functor<tag::cnp_>(), a0, a1);
//     }
//   };
} }
#endif
