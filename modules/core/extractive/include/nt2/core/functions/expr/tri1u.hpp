//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_TRI1U_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_TRI1U_HPP_INCLUDED

#include <nt2/core/functions/tri1u.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/tri1u.hpp>
#include <nt2/include/functions/ismatrix.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tri1u_, tag::cpu_, (A0), ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::tri1u_
                                          , container::domain
                                          , A0 const&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using tri1u: First input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::tri1u_
                                    , container::domain
                                    > ( boost::cref(a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::offset_tri1u_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::offset_tri1u_
                                          , container::domain
                                          , A0 const&
                                          , A1
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using tri1u: First input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::offset_tri1u_
                                    , container::domain
                                    > ( boost::cref(a0), a1 );
    }
  };
} }

#endif
