#ifndef FALCON_CPP0X_SYNTAX_HPP
#define FALCON_CPP0X_SYNTAX_HPP

#include <falcon/c++0x/keywords.hpp>
#include <falcon/c++0x/assignable.hpp>
#include <falcon/c++0x/extend_pack.hpp>

#if __cplusplus <= 201100L
# define CPP0X_PROTO(_Func, ...) undetermined_type _Func

# define CPP0X(...) (__VA_ARGS__)
# define CPP0X_INITIALIZER(...) __VA_ARGS__
# define CPP0X_RVALUE_REF &

#else

# define CPP0X_PROTO(_Func, ...) auto _Func -> __VA_ARGS__

# define CPP0X(...) {__VA_ARGS__}
# define CPP0X_INITIALIZER(...) {__VA_ARGS__}
# define CPP0X_RVALUE_REF &&

#endif

#define CPP0X_DELEGATE_FUNCTION(_Func, ...)\
	CPP0X_PROTO(_Func, decltype(__VA_ARGS__)) { return __VA_ARGS__; }

#endif