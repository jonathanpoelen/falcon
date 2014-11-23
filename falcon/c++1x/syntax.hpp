#ifndef FALCON_CPP1X_SYNTAX_HPP
#define FALCON_CPP1X_SYNTAX_HPP

#include <falcon/config.hpp>
#include <falcon/c++/initialize.hpp>
#include <falcon/c++1x/assignable.hpp>

# define CPP1X CPP_INITIALIZE

#if defined(IN_IDE_PARSER)
# define CPP1X_DELEGATE_FUNCTION(Func, impl)\
  auto Func -> decltype(impl) { return impl; }
# define CPP1X_DELEGATE_FUNCTION_NOEXCEPT(Func, impl)\
  auto Func noexcept(noexcept(impl)) -> decltype(impl) { return impl; }
# define CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(Func, impl)\
  auto Func noexcept -> decltype(impl) { return impl; }
#else
# if __cplusplus > 201103L
# define CPP1X_DELEGATE_FUNCTION(Func, ...)\
  decltype(auto) Func { return __VA_ARGS__; }
# define CPP1X_DELEGATE_FUNCTION_NOEXCEPT(Func, ...)\
  decltype(auto) Func noexcept(noexcept(__VA_ARGS__)) { return __VA_ARGS__; }
# define CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(Func, ...)\
  decltype(auto) Func noexcept { return __VA_ARGS__; }
# else
# define CPP1X_DELEGATE_FUNCTION(Func, ...)\
  auto Func -> decltype(__VA_ARGS__) { return __VA_ARGS__; }
# define CPP1X_DELEGATE_FUNCTION_NOEXCEPT(Func, ...)\
  auto Func noexcept(noexcept(__VA_ARGS__))\
    -> decltype(__VA_ARGS__) { return __VA_ARGS__; }
# define CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(Func, ...)\
  auto Func noexcept -> decltype(__VA_ARGS__) { return __VA_ARGS__; }
# endif
#endif

#endif
