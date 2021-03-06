//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/toolbox/ieee/include/functions/frexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( frexp, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::frexp;
  using boost::simd::tag::frexp_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  typedef typename boost::dispatch::meta::as_integer<vT,signed>::type viT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<frexp_(vT)>::type)
                  , (std::pair<vT,viT>)
                  );

  {
    viT e;
    vT  m;

    frexp(boost::simd::One<vT>(), m, e);
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<viT>());
  }

  {
    viT e;
    vT  m;

    m = frexp(boost::simd::One<vT>(), e);
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<viT>());
  }

  {
    viT e;
    vT  m;

    boost::fusion::vector_tie(m,e) = frexp(boost::simd::One<vT>());
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<viT>());
  }

  {
    std::pair<vT,viT> p;

    p = frexp(boost::simd::One<vT>());
    NT2_TEST_EQUAL(p.first  , boost::simd::Half<vT>());
    NT2_TEST_EQUAL(p.second , boost::simd::One<viT>());
  }
}
