//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_AS_UNSIGNED_HPP_INCLUDED
#define NT2_SDK_META_AS_UNSIGNED_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements \ref nt2::meta::as_unsigned
 */

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<class T, class Enable = void>
  struct  as_unsigned;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   *
   * Returns the input type rebound the unsigned equivalent type to its primitive
   * type.
   *
   * \tparam T Type to modify
   *
   * \par Models:
   *
   * \metafunction
   *
   * \par Semantic:
   *
   * For any type \c T,
   *
   * \code
   * typedef as_unsigned<T>::type type;
   * \endcode
   *
   * is equivalent to
   *
   * \code
   * typedef T  type;
   * \endcode
   *
   * if \c primitive<T>::type is \c unsigned and to
   *
   * \code
   *  typedef apply< meta::factory_of<T>::type
   *               , boost::make_unsigned< meta::primitive_of<T>::type >::type
   *               >::type                                                type;
   * \endcode
   *
   * if \c primitive<T>::type is signed.
   *
   * \par Example usage:
   *
   * \include as_unsigned.cpp
   */
  //============================================================================
  template<class T>
  struct  as_unsigned
        : details::as_unsigned < typename meta::strip<T>::type >
  {
    NT2_STATIC_ASSERT
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , NT2_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_UNSIGNED
    , "A type with a non-fundamental primitive is used in nt2::meta::as_unsigned."
    );
  };
} }

namespace nt2 { namespace details
{
  template<class T, class Enable>
  struct  as_unsigned
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_unsigned < typename meta::primitive_of<T>::type
                                          >::type
                            >
  {};

  template<class T>
  struct  as_unsigned < T
                      , typename boost::enable_if < typename meta::
                                                    is_fundamental<T>::type
                                                  >::type
                      >
       : boost::mpl::eval_if< boost::mpl::
                              bool_ <   boost::is_integral<T>::value
                                    &&  !boost::is_same<bool,T>::value
                                    >
                            , boost::make_unsigned<T>
                            , boost::mpl::identity<T>
                            > {};
} }
#endif
