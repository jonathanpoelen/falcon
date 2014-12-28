#ifndef FALCON_TYPE_TRAITS_MAKE_TYPE_ALIAS_HPP
#define FALCON_TYPE_TRAITS_MAKE_TYPE_ALIAS_HPP

#include <falcon/preprocessor/concat.hpp>
#include <falcon/preprocessor/pack.hpp>

#define FALCON_MAKE_GENERIC_TYPE_ALIAS(name, templates_params, name_params) \
  template<FALCON_PP_PACK templates_params>                                 \
  using FALCON_CONCAT(name, _t)                                             \
    = typename name<FALCON_PP_PACK name_params>::type


#define FALCON_MAKE_TYPE_ALIAS(name) \
  template<class T> using FALCON_CONCAT(name, _t) = typename name<T>::type

#define FALCON_MAKE_XTYPE_ALIAS(name, tt) \
  template<tt X, class T> \
  using FALCON_CONCAT(name, _t) = typename name<X, T>::type


#define FALCON_MAKE_USING_TYPE_ALIAS1(name, p1) \
  using FALCON_CONCAT(name, _t) = typename name<p1>::type

#define FALCON_MAKE_USING_TYPE_ALIAS2(name, p1, p2) \
  using FALCON_CONCAT(name, _t) = typename name<p1, p2>::type

#define FALCON_MAKE_USING_TYPE_ALIAS3(name, p1, p2, p3) \
  using FALCON_CONCAT(name, _t) = typename name<p1, p2, p3>::type


#define FALCON_MAKE_TYPE_ALIAS1(name, p1) \
  template<class p1>                      \
  using FALCON_CONCAT(name, _t) = typename name<p1>::type

#define FALCON_MAKE_TYPE_ALIAS2(name, p1, p2) \
  template<class p1, class p2>                \
  using FALCON_CONCAT(name, _t) = typename name<p1, p2>::type

#define FALCON_MAKE_TYPE_ALIAS3(name, p1, p2, p3) \
  template<class p1, class p2, class p3>          \
  using FALCON_CONCAT(name, _t) = typename name<p1, p2, p3>::type


#define FALCON_MAKE_XTYPE_ALIAS1(name, T, p1, p2) \
  template<T p1, class p2>                        \
  using FALCON_CONCAT(name, _t) = typename name<p1, p2>::type

#define FALCON_MAKE_XTYPE_ALIAS2(name, T, p1, p2, p3) \
  template<T p1, class p2, class p3>                  \
  using FALCON_CONCAT(name, _t) = typename name<p1, p2, p3>::type

#endif
