//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - load/scalar Mode"

#include <boost/simd/include/functions/load.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(load, BOOST_SIMD_TYPES)
{
  using boost::simd::load;

  T data[5] = {0,1,2,3,4};

  NT2_TEST_EQUAL( (load<T,-4>(&data[0]-4,4)), T(0) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0]-4,5)), T(1) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0]-4,6)), T(2) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0]-4,7)), T(3) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0]-4,8)), T(4) );

  NT2_TEST_EQUAL( (load<T,-3>(&data[0]-3,3)), T(0) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0]-3,4)), T(1) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0]-3,5)), T(2) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0]-3,6)), T(3) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0]-3,7)), T(4) );

  NT2_TEST_EQUAL( (load<T,-2>(&data[0]-2,2)), T(0) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0]-2,3)), T(1) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0]-2,4)), T(2) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0]-2,5)), T(3) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0]-2,6)), T(4) );

  NT2_TEST_EQUAL( (load<T,-1>(&data[0]-1,1)), T(0) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0]-1,2)), T(1) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0]-1,3)), T(2) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0]-1,4)), T(3) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0]-1,5)), T(4) );

  NT2_TEST_EQUAL( load<T>(&data[0],0), T(0) );
  NT2_TEST_EQUAL( load<T>(&data[0],1), T(1) );
  NT2_TEST_EQUAL( load<T>(&data[0],2), T(2) );
  NT2_TEST_EQUAL( load<T>(&data[0],3), T(3) );
  NT2_TEST_EQUAL( load<T>(&data[0],4), T(4) );

  NT2_TEST_EQUAL( (load<T,0>(&data[0],0)), T(0) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],1)), T(1) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],2)), T(2) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],3)), T(3) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],4)), T(4) );

  NT2_TEST_EQUAL( (load<T,1>(&data[0]+1,-1)), T(0) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0]+1, 0)), T(1) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0]+1, 1)), T(2) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0]+1, 2)), T(3) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0]+1, 3)), T(4) );

  NT2_TEST_EQUAL( (load<T,2>(&data[0]+2,-2)), T(0) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0]+2,-1)), T(1) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0]+2, 0)), T(2) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0]+2, 1)), T(3) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0]+2, 2)), T(4) );

  NT2_TEST_EQUAL( (load<T,3>(&data[0]+3,-3)), T(0) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0]+3,-2)), T(1) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0]+3,-1)), T(2) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0]+3, 0)), T(3) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0]+3, 1)), T(4) );

  NT2_TEST_EQUAL( (load<T,4>(&data[0]+4,-4)), T(0) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0]+4,-3)), T(1) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0]+4,-2)), T(2) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0]+4,-1)), T(3) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0]+4, 0)), T(4) );
}

NT2_TEST_CASE( load_sequence )
{
  using boost::simd::load;
  using boost::simd::tag::load_;

  double d = 3.4;
  float  f = 1.8f;
  char   c = 'a';

  typedef boost::fusion::vector<double,float,char> type;
  type v;

  v = load< type >(boost::fusion::make_vector(&d, &f, &c), 0);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , d);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , f);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , c);
}

NT2_TEST_CASE( load_pointer_of_sequence )
{
  using boost::simd::load;
  using boost::simd::tag::load_;

  double d = 3.4;
  float  f = 1.8f;
  char   c = 'a';

  typedef boost::fusion::vector<double,float,char> type;
  type s(d,f,c);
  type v;

  v = load< type >(&s, 0);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , d);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , f);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , c);
}
