//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TBB_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TBB_INNER_FOLD_HPP_INCLUDED
#if defined(NT2_USE_TBB)

#include <nt2/core/functions/inner_fold.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/tbb/tbb.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif


#ifndef BOOST_SIMD_NO_SIMD
//==============================================================================
// tbb + SIMD
//==============================================================================
namespace nt2 {

  namespace details
  {
    // Create the correct functor for tbb::parallel reduce according to the
    // requested Site.
    template<class A1, class A2, class A3, class Target>
    struct bop_reduce_simd
    {
      typedef Target target_type;

      bop_reduce_simd(target_type const& vec, A1& in, A3 const& bop, std::size_t const& k)
      : vec_out_(vec), in_(in), bop_(bop), k_(k)
      {}

      bop_reduce_simd(bop_reduce_simd& src, tbb::split)
      : in_(src.in_), bop_(src.bop_), k_(src.k_)
      { vec_out_ = neutral_(nt2::meta::as_<target_type>()); }

      void operator()(tbb::blocked_range<std::size_t> const& r)
      {
        static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
        for(std::size_t i = r.begin(); i < r.end(); i+=N)
        {
          vec_out_ = bop_( vec_out_
                         , nt2::run( in_
                                   , i+k_, meta::as_<target_type>()));
        }
      }

      void join( bop_reduce_simd& rhs ) { vec_out_ = bop_(vec_out_,rhs.vec_out_); }

      target_type         vec_out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      std::size_t               k_;
    };



    template<class A0, class A1, class A2, class A3, class A4, class Target, class Value>
    struct inner_reduce_simd
    {
      typedef Target target_type;
      typedef Value   value_type;

      inner_reduce_simd( A0& out, A1& in, A2 const& n, A3 const& bop, A4 const& uop
                       , std::size_t const& bound, std::size_t const& ibound)
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      , bound_(bound), ibound_(ibound)
      {}

      void operator()(tbb::blocked_range<std::ptrdiff_t> const& r) const
      {
        static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

        for(std::ptrdiff_t j = r.begin(); j < r.end(); ++j)
        {
          std::size_t k = j*bound_;
          nt2::run(out_, j, neutral_(meta::as_<value_type>()));

          bop_reduce_simd<A1,A2,A3,target_type> boppy( neutral_(nt2::meta::as_<target_type>())
                                                     , in_
                                                     , bop_
                                                     , k
                                                     );

          std::size_t chunk = ibound_/tbb::task_scheduler_init::default_num_threads();
          std::size_t grain = r.grainsize()==0
                            ? (chunk<N)
                              ? ibound_
                              : chunk
                            : ibound_;

          tbb::parallel_reduce( tbb::blocked_range<std::size_t>(0,ibound_,grain)
                              , boppy
                              );

          nt2::run(out_, j, uop_(boppy.vec_out_));

          for(std::size_t i = ibound_; i < bound_; ++i)
            nt2::run(out_, j
                     , bop_( nt2::run(out_, j, meta::as_<value_type>())
                                   , nt2::run(in_, i+k, meta::as_<value_type>())));
        }
      }

      A0&                     out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      A4                      uop_;
      std::size_t           bound_;
      std::size_t          ibound_;
    };


  }

  namespace ext
  {
    //============================================================================
    // Generates inner_fold
    //============================================================================
    NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::inner_fold_, nt2::tag::tbb_<Site>
                                 , (A0)(S0)(A1)(A2)(A3)(A4)(Site)
                                 , (boost::simd::meta::is_vectorizable<typename A0::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                                 , ((expr_< table_< unspecified_<A0>, S0 >
                                          , nt2::tag::terminal_
                                          , boost::mpl::long_<0>
                                          >
                                   ))
                                   ((ast_< A1, nt2::container::domain>))
                                   (unspecified_<A2>)
                                   (unspecified_<A3>)
                                   (unspecified_<A4>)
                                 )
    {
      typedef void                                                              result_type;
      typedef typename A0::value_type                                           value_type;
      typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;
      typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

      BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop ) const
      {
        extent_type ext = in.extent();
        static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
        std::size_t bound  = boost::fusion::at_c<0>(ext);
        std::size_t ibound = (boost::fusion::at_c<0>(ext)/N) * N;
        std::ptrdiff_t obound = nt2::numel(boost::fusion::pop_front(ext));
        std::size_t     grain = obound/tbb::task_scheduler_init::default_num_threads();
        details::inner_reduce_simd< A0,A1,A2,A3,A4
                                  , target_type
                                  , value_type> ared( out, in, neutral, bop
                                                     , uop, bound, ibound);

#ifndef BOOST_NO_EXCEPTIONS
        boost::exception_ptr exception;
        try
        {
#endif
          tbb::parallel_for( tbb::blocked_range<std::ptrdiff_t>(0,obound,grain)
                           , ared
                           );

#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
          // Store exception for late rethrow
          exception = boost::current_exception();
        }

        if(exception)
          boost::rethrow_exception(exception);
#endif
      }

    };
  }
}
#else
//==============================================================================
// tbb + noSIMD
//==============================================================================
namespace nt2
{
  namespace details
  {
    template <class X, class N, class B, class U>
    BOOST_FORCEINLINE typename X::value_type
    inner_fold_step(X const& in, const std::size_t& p, N const& neutral, B const& bop, U const& uop);

    template<class A0, class A1, class A2, class A3, class A4>
    struct inner_reduce_scal
    {
      inner_reduce_scal( A0& out, A1& in, A2 const& n, A3 const& bop, A4 const& uop
                       , std::size_t const& ibound)
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      , ibound_(ibound)
      {}

      void operator()(tbb::blocked_range<std::ptrdiff_t> const& r) const
      {
        for(std::ptrdiff_t j = r.begin(); j < r.end(); ++j)
        {
          std::size_t k = j*ibound_;
          nt2::run(out_, j
                  , details::inner_fold_step( in_
                                            , k
                                            , neutral_
                                            , bop_
                                            , uop_
                                            )
                  );
        }
      }

      A0&                     out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      A4                      uop_;
      std::size_t          ibound_;
    };
  }

  namespace ext
  {
  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_fold_, nt2::tag::tbb_<Site>
                              , (A0)(A1)(A2)(A3)(A4)(Site)
                            , ((ast_< A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename A0::value_type                                            value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::ptrdiff_t obound = nt2::numel(boost::fusion::pop_front(ext));
      const std::size_t grain = obound/tbb::task_scheduler_init::default_num_threads();
      details::inner_reduce_scal<A0,A1,A2,A3,A4> ared( out, in, neutral, bop
                                                      , uop, ibound);
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
      try
      {
#endif
        tbb::parallel_for( tbb::blocked_range<std::ptrdiff_t>(0,obound,grain)
                         , ared
                         );
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        exception = boost::current_exception();
      }
      if(exception)
        boost::rethrow_exception(exception);
#endif

    }
  };

} }

#endif
#endif
#endif
