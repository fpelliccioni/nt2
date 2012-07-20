//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BSXFUN_HPP_INCLUDED

#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/sdk/meta/as_index.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::bsxfun_, N>))
                              (generic_< integer_<State> >)
                              (target_<unspecified_<Data> >)
                            )
  {
    typedef typename boost::proto::result_of::
                     child_c<A0&,0>::value_type                        child0_t;
    typedef typename boost::simd::ext::adapt_data<child0_t,Data>::type    ad0_t;

    typedef typename boost::proto::result_of::
                     child_c<A0&,1>::value_type                        child1_t;
    typedef typename boost::simd::ext::adapt_data<child1_t,Data>::type    ad1_t;

    typedef typename A0::extent_type                                      ext_t;
    typedef typename Data::type                                     result_type;

    typedef typename meta::as_index<result_type>::type                      i_t;
    typedef typename meta::call < nt2::tag
                                  ::enumerate_(State,meta::as_<i_t>)
                                >::type                                     p_t;
    typedef typename meta::call<nt2::tag::ind2sub_(ext_t,p_t)>::type        s_t;
    typedef typename s_t::value_type                                        w_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Grab position and size for each children
      s_t pos0  = ind2sub(a0.extent(),enumerate<i_t>(p));
      ext_t sz0 = boost::proto::child_c<0>(a0).extent();
      ext_t sz1 = boost::proto::child_c<1>(a0).extent();
      s_t pos1  = pos0;

      // If you're a singleton, you're always the smallest
      for(std::size_t i = 0; i != ext_t::size(); ++i)
      {
        pos0[i] = nt2::min(splat<w_t>(sz0[i]),pos0[i]);
        pos1[i] = nt2::min(splat<w_t>(sz1[i]),pos1[i]);
      }

      // Call f on each value potential repeated
      return  boost::proto::value(boost::proto::child_c<2>(a0))
              ( run(boost::proto::child_c<0>(a0), sub2ind(sz0, pos0), ad0_t())
              , run(boost::proto::child_c<1>(a0), sub2ind(sz1, pos1), ad1_t())
              );
    }
  };
} }

#endif
