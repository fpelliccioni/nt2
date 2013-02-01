/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container sum"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

template<class T> struct outer_4D_test
{
  outer_4D_test(std::size_t m, std::size_t n, std::size_t o,std::size_t p,T const& min, T const& max )
    : a0(nt2::of_size(m,n,o,p)), a1(nt2::of_size(m,n,o,p))
      ,M(m),N(n),O(o),P(p)
  {
    for(std::size_t l=1;l<=P; ++l)
      for(std::size_t k=1; k<=O; ++k)
        for(std::size_t j=1; j<=N; ++j)
          for(std::size_t i=1; i<=M; ++i)
            a1(i,j,k,l)  = a0(i,j,k,l) = roll<T>(min,max);
  }

  void operator()()
  {
    a1 = nt2::sum(a0,4);
  }

  void reset() {}

  nt2::container::table<T, nt2::settings(nt2::_4D)> a0,a1;
  std::size_t M,N,O,P;
};

template<class T> struct inner_4D_test
{
  inner_4D_test(std::size_t m, std::size_t n, std::size_t o,std::size_t p,T const& min, T const& max )
    : a0(nt2::of_size(m,n,o,p)), a1(nt2::of_size(m,n,o,p))
      ,M(m),N(n),O(o),P(p)
  {
    for(std::size_t l=1;l<=P; ++l)
      for(std::size_t k=1; k<=O; ++k)
        for(std::size_t j=1; j<=N; ++j)
          for(std::size_t i=1; i<=M; ++i)
            a1(i,j,k,l)  = a0(i,j,k,l) = roll<T>(min,max);
  }

  void operator()()
  {
    a1 = nt2::sum(a0,1);
  }

  void reset() {}

  nt2::container::table<T, nt2::settings(nt2::_4D)> a0,a1;
  std::size_t M,N,O,P;
};

template<class T> struct partial_4D_test
{
  partial_4D_test(std::size_t m, std::size_t n, std::size_t o,std::size_t p,T const& min, T const& max )
    : a0(nt2::of_size(m,n,o,p)), a1(nt2::of_size(m,n,o,p))
      ,M(m),N(n),O(o),P(p)
  {
    for(std::size_t l=1;l<=P; ++l)
      for(std::size_t k=1; k<=O; ++k)
        for(std::size_t j=1; j<=N; ++j)
          for(std::size_t i=1; i<=M; ++i)
            a1(i,j,k,l)  = a0(i,j,k,l) = roll<T>(min,max);
  }

  void operator()()
  {
    a1 = nt2::sum(a0,3);
  }

  void reset() {}

  nt2::container::table<T, nt2::settings(nt2::_4D)> a0,a1;
  std::size_t M,N,O,P;
};

template<class T> struct total_4D_test
{
  total_4D_test(std::size_t m, std::size_t n, std::size_t o,std::size_t p,T const& min, T const& max )
    : a0(nt2::of_size(m,n,o,p)), a1(nt2::of_size(m,n,o,p))
      ,M(m),N(n),O(o),P(p)
  {
    for(std::size_t l=1;l<=P; ++l)
      for(std::size_t k=1; k<=O; ++k)
        for(std::size_t j=1; j<=N; ++j)
          for(std::size_t i=1; i<=M; ++i)
            a1(i,j,k,l)  = a0(i,j,k,l) = roll<T>(min,max);
  }

  void operator()()
  {
    a1 = nt2::sum(a0(nt2::_));
  }

  void reset() {}

  nt2::container::table<T, nt2::settings(nt2::_4D)> a0,a1;
  std::size_t M,N,O,P;
};


template<class T> void do_test_()
{
  std::cout << "\tOuter_fold\n";
  std::cout << "Size\ttable (c/e)\ttable (s)\n";

  for(int N=4;N<=64;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "^4\t";
    outer_4D_test<T> tt(N,N,N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N*N) << "\t";
    std::cout << std::scientific << tv.median << "\n";

  }

  std::cout << "\tPartial_fold\n";
  std::cout << "Size\ttable (c/e)\ttable (s)\n";

  for(int N=4;N<=64;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "^4\t";
    partial_4D_test<T> tt(N,N,N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N*N) << "\t";
    std::cout << std::scientific << tv.median << "\n";

  }

  std::cout << "\tInner_fold\n";
  std::cout << "Size\ttable (c/e)\ttable (s)\n";

  for(int N=4;N<=64;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "^4\t";
    inner_4D_test<T> tt(N,N,N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N*N) << "\t";
    std::cout << std::scientific << tv.median << "\n";

  }

  std::cout << "\tTotal_fold\n";
  std::cout << "Size\ttable (c/e)\ttable (s)\n";

  for(int N=4;N<=64;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "^4\t";
    total_4D_test<T> tt(N,N,N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N*N) << "\t";
    std::cout << std::scientific << tv.median << "\n";

  }

}

NT2_TEST_CASE_TPL( sum, (double)(float) )
{
  do_test_<T>();
}
