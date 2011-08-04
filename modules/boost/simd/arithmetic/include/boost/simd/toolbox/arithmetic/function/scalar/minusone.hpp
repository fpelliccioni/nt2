//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MINUSONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MINUSONE_HPP_INCLUDED
#include <boost/dispatch/meta/as_signed.hpp>
#include <boost/simd/include/constants/digits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::minusone_, tag::cpu_,
			     (A0),
			     (scalar_ < arithmetic_<A0> > )
			     )
  {
    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0)>::type tmp;
    typedef typename dispatch::meta::as_signed<tmp>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return result_type(a0)-One<result_type>();
    }

  };
} } }

#endif
