//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::wmean function"

#include <nt2/table.hpp>
#include <nt2/include/functions/wmean.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/repnum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( wmean_scalar, (float)(double))//NT2_TYPES )
{
  typedef std::complex<T>  cT;
  cT x = nt2::wmean(cT(42), T(1));
  NT2_TEST_EQUAL( x, cT(42));

  x = nt2::wmean(cT(42),T(1), 1);
  NT2_TEST_EQUAL( x, cT(42) );

  x = nt2::wmean(cT(42),T(1), 2);
  NT2_TEST_EQUAL( x, cT(42) );

}

NT2_TEST_CASE_TPL( wmean, (float)(double))//NT2_TYPES )
{
  typedef std::complex<T>  cT;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<cT> sy;
  nt2::table<cT> sy2;
  nt2::table<T> w = nt2::repnum(nt2::rec(T(3)),5, 1);

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = cT(i + 10*j, i + 10*j);
  display("y", y);

  std::cout << "firstnonsingleton" << std::endl;
  sy = nt2::sum(y)/T(nt2::size(y, nt2::firstnonsingleton(y)));
  sy2 = nt2::wmean(y, w);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_ULP_EQUAL(sy(i,j), sy2(i, j), 0.5);

  std::cout << "dim1" << std::endl;
  sy = nt2::sum(y)/T(nt2::size(y, 1));
  sy2 = nt2::wmean(y, w, 1);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_ULP_EQUAL(sy(i,j), sy2(i, j), 0.5);

  std::cout << "dim2" << std::endl;
  w = nt2::repnum(nt2::rec(T(1)),1, 3);
  sy = nt2::sum(y, 2)/T(nt2::size(y, 2));
  sy2 = nt2::wmean(y, w, 2);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_ULP_EQUAL(sy(i,j), sy2(i, j), 0.5);

//   std::cout << "dim3" << std::endl;
//   w = nt2::repnum(nt2::rec(T(12)),1, 1);
//   sy = nt2::sum(y, 3)/T(nt2::size(y, 3));
//   sy2 = nt2::wmean(y, w, 3);
//   display("sy", sy);
//   display("sy2", sy2);
//   for(int j=1;j<=size(sy, 2);j++)
//     for(int i=1;i<=size(sy, 1);i++)
//       NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

//   w = nt2::repnum(nt2::rec(T(12)),numel(y), 1);

//   std::cout <<  nt2::wmean(y(nt2::_), w);
}

