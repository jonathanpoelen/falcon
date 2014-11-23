#ifndef FALCON_FN_MAKE_GLOBAL_FUNCTION_OBJECT_HPP
#define FALCON_FN_MAKE_GLOBAL_FUNCTION_OBJECT_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/preprocessor/concat.hpp>
#include <falcon/preprocessor/pack.hpp>
#include <falcon/c++1x/syntax.hpp>
#include <utility>

#define FALCON_MAKE_STATIC_GLOBAL_FUNCTION_OBJECT(namespace_adl, name)\
  FALCON_GLOBAL_OBJECT(name, namespace_adl::FALCON_CONCAT(name,_fn))

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_TYPE_IMPL( \
  namespace_adl, name, template_params, type_params, impl) \
  namespace namespace_adl { \
    struct FALCON_CONCAT(name,_fn) \
    { \
      constexpr FALCON_CONCAT(name,_fn)() noexcept {} \
\
      template<FALCON_PP_PACK template_params> \
      constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
        operator()(FALCON_PP_PACK type_params) const \
      , impl) \
    }; \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_NON_MEMBER_FUNCTION_IMPL( \
  namespace_adl, name, template_params, type_params, impl) \
  namespace namespace_adl { \
    template<FALCON_PP_PACK template_params> \
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      name(FALCON_PP_PACK type_params) \
    , impl) \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_IMPL( \
  namespace_adl, name, template_params, type_params, obj_impl, func_impl) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_NON_MEMBER_FUNCTION_IMPL( \
    namespace_adl, name, template_params, type_params, func_impl) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_TYPE_IMPL( \
    namespace_adl, name, template_params, type_params, obj_impl) \
  FALCON_MAKE_STATIC_GLOBAL_FUNCTION_OBJECT(namespace_adl, name)


#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(namespace_adl, name) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_IMPL(namespace_adl, name, \
    (class T), (T && x), name(std::forward<T>(x)), std::forward<T>(x).name())

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(namespace_adl, name) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_IMPL(namespace_adl, name, \
    (class T, class... Args), \
    (T && x, Args&&... args), \
    name(std::forward<T>(x), std::forward<Args>(args)...), \
    std::forward<T>(x).name(std::forward<Args>(args)...))

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_ARGS( \
  namespace_adl, name, template_params, type_params, params) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_IMPL(namespace_adl, name, \
    (class T, FALCON_PP_PACK template_params), \
    (T && x, FALCON_PP_PACK type_params), \
    name(std::forward<T>(x), FALCON_PP_PACK params), \
    std::forward<T>(x).name(FALCON_PP_PACK params))


#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_TYPE_WITH_RESULT_IMPL( \
  result, namespace_adl, name, template_params, type_params, impl) \
  namespace namespace_adl { \
    struct FALCON_CONCAT(name,_fn) \
    { \
      using result_type = result;\
      constexpr FALCON_CONCAT(name,_fn)() noexcept {} \
\
      template<FALCON_PP_PACK template_params> \
      constexpr result operator()(FALCON_PP_PACK type_params) const \
      noexcept(noexcept(impl)) \
      { return impl; } \
    }; \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_NON_MEMBER_FUNCTION_WITH_RESULT_IMPL( \
  result, namespace_adl, name, template_params, type_params, impl) \
  namespace namespace_adl { \
    template<FALCON_PP_PACK template_params> \
    constexpr result name(FALCON_PP_PACK type_params) \
    noexcept(noexcept(impl)) \
    { return impl; } \
  }

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WITH_RESULT_IMPL( \
  result, namespace_adl, name, \
  template_params, type_params, obj_impl, func_impl) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_NON_MEMBER_FUNCTION_WITH_RESULT_IMPL( \
    result, namespace_adl, name, template_params, type_params, func_impl) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_TYPE_WITH_RESULT_IMPL( \
    result, namespace_adl, name, template_params, type_params, obj_impl) \
  FALCON_MAKE_STATIC_GLOBAL_FUNCTION_OBJECT(namespace_adl, name)


#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT( \
  result, namespace_adl, name) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WITH_RESULT_IMPL( \
    result, namespace_adl, name, \
    (class T), (T && x), name(std::forward<T>(x)), std::forward<T>(x).name())

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT_WRAPPER( \
  result, namespace_adl, name) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WITH_RESULT_IMPL( \
    result, namespace_adl, name, \
    (class T, class... Args), (T && x, Args && ... ), \
    name(std::forward<T>(x), std::forward<Args>(args)...), \
    std::forward<T>(x).name(std::forward<Args>(args)...))

#define FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT_ARGS( \
  result, namespace_adl, name, template_params, type_params, params) \
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WITH_RESULT_IMPL( \
    result, namespace_adl, name, \
    (class T, , FALCON_PP_PACK template_params), \
    (T && x, FALCON_PP_PACK type_params), \
    name(std::forward<T>(x), FALCON_PP_PACK params), \
    std::forward<T>(x).name(FALCON_PP_PACK params))

#endif
