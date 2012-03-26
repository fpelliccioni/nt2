/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container runner"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template <class T>
struct extent_
{
  typedef typename T::extent_type type;
};

NT2_TEST_CASE( value_at )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0(of_size(4, 3));
  table<T> a1(of_size(4, 3));

  for(std::size_t j=1; j!=3+1; ++j)
    for(std::size_t i=1; i!=4+1; ++i)
      a0(i, j) = T(i+j);

  a1 = a0 + T(1);

  for(std::size_t j=1; j!=3+1; ++j)
    for(std::size_t i=1; i!=4+1; ++i)
      NT2_TEST_EQUAL( T(a1(i, j)), T(i+j+1) );

  table<T, nt2::_1D> a2(of_size(13));
  table<T, nt2::_1D> a3(of_size(13));
  for(std::size_t i=1; i!=13+1; ++i)
    a2(i) = T(i);

  a3 = a2 + T(1);

  for(std::size_t i=1; i!=13+1; ++i)
    NT2_TEST_EQUAL( T(a3(i)), T(i+1) );

/*
  table<T, nt2::_1D> xd = nt2::_(T(0),T(2),T(9));
  table<T, nt2::_1D> a2_(of_size(5));
  a2_ = a2(xd);
*/
}

NT2_TEST_CASE( scalar_size )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0 = T(42);
  NT2_TEST( a0.extent() == of_size(1) );
  NT2_TEST_EQUAL( T(a0(1)), T(42) );

  table<T> a1;
  NT2_TEST( a1.extent() == of_size(0) );

  a1 = T(42);
  NT2_TEST( a1.extent() == of_size(1) );
  NT2_TEST_EQUAL( T(a0(1)), T(42) );
}

NT2_TEST_CASE( element_wise )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0;
  table<boost::dispatch::meta::as_integer<T>::type> a1;
  a1 = nt2::toint(a0);
}


NT2_TEST_CASE( reduction_size )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;

  std::size_t N = 2;
  std::size_t M = 3;
  std::size_t O = 4;
  std::size_t P = 5;

  table<T,nt2::_1D> a00(of_size(N));
  table<T> a01(of_size(N));

  table<T> a1(of_size(1,M));
  table<T> a2_4(of_size(N,M,O,P));
  table<T, nt2::_3D> a2_3(of_size(N,M,O));
  table<T, nt2::_2D> a2_2(of_size(N,M));

  table<T> a3(of_size(N,M,O,1));

  a1 = sum(a2_4,4);
  NT2_TEST( (a1.extent() == of_size(N,M,O)) );
  NT2_TEST( (a2_4.extent() == of_size(N,M,O,P)) );

  a1 = sum(a2_4,3);
  NT2_TEST( (a1.extent() == of_size(N,M,1,P)) );

  a1 = sum(a2_4,2);
  NT2_TEST( (a1.extent() == of_size(N,1,O,P)) );

  a1 = sum(a2_4,1);
  NT2_TEST( (a1.extent() == of_size(1,M,O,P)) );
  a1 = sum(a2_3,1);
  NT2_TEST( (a1.extent() == of_size(1,M,O)) );
  a1 = sum(a2_2,1);
  NT2_TEST( (a1.extent() == of_size(1,M)) );


  a1 = sum(a00);
  NT2_TEST( (a1.extent() == of_size(1)) );
  a1 = sum(a01);
  NT2_TEST( (a1.extent() == of_size(1)) );

}


NT2_TEST_CASE( reduction_value )
{

  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;


  std::size_t N = 2;
  std::size_t M = 3;
  std::size_t O = 4;
  std::size_t P = 5;

  table<T> a1(of_size(1,M));
  table<T> a2_4(of_size(N,M,O,P));
  table<T, nt2::_3D> a2_3(of_size(N,M,O));
  table<T, nt2::_2D> a2_2(of_size(N,M));

  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= M; ++j){
        for(std::size_t i = 1; i <= N; ++i){
          a2_4(i,j,k,l) = T(1);
          a2_3(i,j,k) = T(1);
          a2_2(i,j) = T(1);
        }
      }
    }
  }
  

  a1 = sum(a2_4,1);
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= M; ++j){
        NT2_TEST_EQUAL(T(a1(1,j,k,l)),T(N)) ;
      }
    }
  }

  a1 = sum(a2_3,1);
  for(std::size_t k = 1; k <= O; ++k){
    for(std::size_t j = 1; j <= M; ++j){
      NT2_TEST_EQUAL(T(a1(1,j,k)),T(N)) ;
    }
  }

  a1 = sum(a2_2,1);
  for(std::size_t j = 1; j <= M; ++j){
    NT2_TEST_EQUAL(T(a1(1,j)),T(N)) ;
  }
  


}
