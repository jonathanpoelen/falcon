#ifndef FALCON_FN_MAKE_GLOBAL_FUNCTION_OBJECT_HPP
#define FALCON_FN_MAKE_GLOBAL_FUNCTION_OBJECT_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/preprocessor/concat.hpp>
#include <falcon/preprocessor/pack.hpp>
#include <falcon/c++1x/syntax.hpp>
#include <utility>

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(namespace_adl, name) \
  namespace namespace_adl { \
    template<class T> \
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      name(T && x) \
    , std::forward<T>(x).name()) \
\
    struct FALCON_CONCAT(name,_fn) \
    { \
      constexpr FALCON_CONCAT(name,_fn)() noexcept {} \
\
      template<class T> \
      constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
        operator()(T && x) const \
      , name(std::forward<T>(x)) \
      ) \
    }; \
  } \
\
  namespace { \
    constexpr auto const & name \
      = ::falcon::static_const<namespace_adl::FALCON_CONCAT(name,_fn)>::value; \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT2( \
  namespace_adl, name, template_params, type_params, params) \
  namespace namespace_adl { \
    template<class T, FALCON_PP_PACK template_params> \
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      name(T && x, FALCON_PP_PACK type_params)\
    , std::forward<T>(x).name params) \
\
    struct FALCON_CONCAT(name,_fn) \
    { \
      constexpr FALCON_CONCAT(name,_fn)() noexcept {} \
\
      template<class T, FALCON_PP_PACK template_params> \
      constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
        operator()(T && x, FALCON_PP_PACK type_params) const \
      , name(std::forward<T>(x), FALCON_PP_PACK params)) \
    }; \
  } \
\
  namespace { \
    constexpr auto const & name \
      = ::falcon::static_const<namespace_adl::FALCON_CONCAT(name,_fn)>::value; \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(namespace_adl, name) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT2( \
    namespace_adl, name \
  , (class... Ts), (Ts&&...args), (std::forward<Ts>(args)...))


#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT(result, namespace_adl, name) \
  namespace namespace_adl { \
    template<class T> \
    constexpr result name(T && x) \
    noexcept(noexcept(std::forward<T>(x).name())) \
    { return std::forward<T>(x).name(); } \
\
    struct FALCON_CONCAT(name,_fn) \
    { \
      constexpr FALCON_CONCAT(name,_fn)() noexcept {} \
\
      template<class T> \
      constexpr result operator()(T && x) const \
      noexcept(name(std::forward<T>(x))) \
      { return name(std::forward<T>(x)); } \
    }; \
  } \
\
  namespace { \
    constexpr auto const & name \
      = ::falcon::static_const<namespace_adl::FALCON_CONCAT(name,_fn)>::value; \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT2_RESULT( \
  result, namespace_adl, name, template_params, type_params, params) \
  namespace namespace_adl { \
    template<class T, FALCON_PP_PACK template_params> \
    constexpr result name(T && x, FALCON_PP_PACK type_params) \
    noexcept(noexcept(std::forward<T>(x).name params)) \
    { return std::forward<T>(x).name params; } \
\
    struct FALCON_CONCAT(name,_fn) \
    { \
      constexpr FALCON_CONCAT(name,_fn)() noexcept {} \
\
      template<class T, FALCON_PP_PACK template_params> \
      constexpr result operator()(T && x, FALCON_PP_PACK type_params) const \
      noexcept(noexcept(name(std::forward<T>(x), FALCON_PP_PACK params))) \
      { return name(std::forward<T>(x), FALCON_PP_PACK params); } \
    }; \
  } \
\
  namespace { \
    constexpr auto const & name \
      = ::falcon::static_const<namespace_adl::FALCON_CONCAT(name,_fn)>::value; \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT_WRAPPER( \
  result, namespace_adl, name) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT2_RESULT( \
    result, namespace_adl, name \
  , (class... Ts), (Ts&&args...), (std::forward<Ts>(args)...))

#endif
