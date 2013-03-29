//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - load/simd Mode"

#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/memory/stack_buffer.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

NT2_TEST_CASE_TPL( load,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  typedef typename  boost::dispatch::meta
                  ::call<load_( T*
                              , int
                              , boost::dispatch::meta::as_<vT>
                              )
                        >::type                     rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , rT, 3 );

  for(std::size_t i=0;i<cardinal_of<vT>::value*3;++i)
  {
    data[i] = T(1+i);
    ref[i/cardinal_of<vT>::value][i%cardinal_of<vT>::value] = T(1+i);
  }

  for(std::size_t i=0;i<3;++i)
  {
    rT v = boost::simd::load<vT>(&data[i*cardinal_of<vT>::value]);
    NT2_TEST_EQUAL(v , ref[i]);
  }
}

NT2_TEST_CASE_TPL( load_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  typedef typename  boost::dispatch::meta
                  ::call<load_( T*
                              , int
                              , boost::dispatch::meta::as_<vT>
                              )
                        >::type                     rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , rT, 3 );

  for(std::size_t i=0;i<cardinal_of<vT>::value*3;++i)
  {
    data[i] = T(1+i);
    ref[i/cardinal_of<vT>::value][i%cardinal_of<vT>::value] = T(1+i);
  }

  std::ptrdiff_t off = cardinal_of<vT>::value;

  rT v;

  v = boost::simd::load<vT>(&data[cardinal_of<vT>::value],-off);
  NT2_TEST_EQUAL(v , ref[0]);

  v = boost::simd::load<vT>(&data[cardinal_of<vT>::value], 0);
  NT2_TEST_EQUAL(v , ref[1]);

  v = boost::simd::load<vT>(&data[cardinal_of<vT>::value],+off);
  NT2_TEST_EQUAL(v , ref[2]);
}

NT2_TEST_CASE_TPL( load_suboffset_periodic,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  typedef typename  boost::dispatch::meta
                  ::call<load_( T*
                              , int
                              , boost::dispatch::meta::as_<vT>
                              )
                        >::type                     rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , rT, 3 );

  for(std::size_t i=0;i<cardinal_of<vT>::value*3;++i)
  {
    data[i] = T(1+i);
    ref[i/cardinal_of<vT>::value][i%cardinal_of<vT>::value] = T(1+i);
  }

  for(std::size_t i=0;i<2;++i)
  {
    rT v = boost::simd::load<vT,cardinal_of<vT>::value>(&data[(1+i)*cardinal_of<vT>::value]);
    NT2_TEST_EQUAL(v , ref[i+1]);
  }
}

NT2_TEST_CASE_TPL( load_suboffset_forward,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  typedef typename  boost::dispatch::meta
                  ::call<load_( T*
                              , int
                              , boost::dispatch::meta::as_<vT>
                              )
                        >::type                     rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , rT, 3 );

  for(std::size_t i=0;i<cardinal_of<vT>::value*3;++i)
  {
    data[i] = T(1+i);
    ref[i/cardinal_of<vT>::value][i%cardinal_of<vT>::value] = T(2+i);
  }

  for(std::size_t i=0;i<2;++i)
  {
    rT v = boost::simd::load<vT,1>(&data[1+i*cardinal_of<vT>::value]);
    NT2_TEST_EQUAL(v , ref[i]);
  }
}

NT2_TEST_CASE_TPL( load_suboffset_backward,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  typedef typename  boost::dispatch::meta
                  ::call<load_( T*
                              , int
                              , boost::dispatch::meta::as_<vT>
                              )
                        >::type                     rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , rT, 3 );

  for(std::size_t i=0;i<cardinal_of<vT>::value*3;++i)
  {
    data[i] = T(1+i);
    ref[i/cardinal_of<vT>::value][i%cardinal_of<vT>::value] = T(i);
  }

  for(std::size_t i=1;i<3;++i)
  {
    rT v = boost::simd::load<vT,-1>(&data[i*cardinal_of<vT>::value-1]);
    NT2_TEST_EQUAL(v , ref[i]);
  }
}

NT2_TEST_CASE_TPL( load_gather, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type viT;

  typedef typename
          boost::dispatch::
          meta::call<load_(T*,viT,boost::dispatch::meta::as_<vT>)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );

  for(size_t i=0;i<cardinal_of<vT>::value*3;++i) data[i] = T(1+i);

  viT index;
  rT ref;

  // Spread out the gather values
  index[0] = cardinal_of<vT>::value*3 -1;
  index[cardinal_of<viT>::value-1] = 0;

  for(size_t i=1;i<cardinal_of<viT>::value-1;++i)
  {
    index[i] = i*(cardinal_of<vT>::value*3)/(cardinal_of<vT>::value-1);
  }

  for(size_t i=0;i<cardinal_of<vT>::value;++i) ref[i] = data[index[i]];

  rT v = boost::simd::load<vT>(&data[0], index);

  NT2_TEST_EQUAL(v , ref);
}

struct foo { short d; float f; char c; };

BOOST_FUSION_ADAPT_STRUCT(foo,(short,d)(float,f)(char,c))

NT2_TEST_CASE( load_sequence )
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::fusion::make_vector;
  using boost::fusion::result_of::value_at;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo,ext_t>                        vT;

  static const size_t sz = cardinal_of< vT >::value;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( cdata,  char , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( fdata,  float, sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( sdata,  short, sz );

  for(std::size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    sdata[i] = short(1+i);
  }

  vT v = load<vT>(make_vector(&sdata[0], &fdata[0], &cdata[0]), 0);

  typedef typename value_at<vT,boost::mpl::int_<0> >::type foo0_t;
  typedef typename value_at<vT,boost::mpl::int_<1> >::type foo1_t;
  typedef typename value_at<vT,boost::mpl::int_<2> >::type foo2_t;

  foo0_t sref = load<foo0_t>(&sdata[0]);
  foo1_t fref = load<foo1_t>(&fdata[0]);
  foo2_t cref = load<foo2_t>(&cdata[0]);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
}

NT2_TEST_CASE( load_pointer_of_sequence )
{

  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::fusion::make_vector;
  using boost::fusion::result_of::value_at;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo,ext_t>                        vT;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, foo, (native<foo,ext_t>::static_size) );

  for(size_t i=0;i<native<foo,ext_t>::static_size;++i)
  {
    data[i].d = int16_t(1+i);
    data[i].f = float(2+i);
    data[i].c = char(3+i);
  }

  typename value_at<vT,boost::mpl::int_<0> >::type sref;
  typename value_at<vT,boost::mpl::int_<1> >::type fref;
  typename value_at<vT,boost::mpl::int_<2> >::type cref;

  for(size_t i=0;i<native<foo,ext_t>::static_size;++i)
  {
    sref[i] = data[i].d;
    fref[i] = data[i].f;
    cref[i] = data[i].c;
  }

  vT v = load<vT>(&data[0], 0);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
}
