#ifndef _FALCON_CPP_NOEXCEPT_HPP
#define _FALCON_CPP_NOEXCEPT_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_NOEXCEPT noexcept
# if defined(IN_IDE_PARSER)
#  define CPP_NOEXCEPT_OPERATOR(exp) noexcept(exp)
# else
#  define CPP_NOEXCEPT_OPERATOR(...) noexcept(__VA_ARGS__)
# endif
#else
# define CPP_NOEXCEPT throw()
# define CPP_NOEXCEPT_OPERATOR(...)
#endif

#define CPP_NOEXCEPT_OPERATOR2(...) CPP_NOEXCEPT_OPERATOR(CPP_NOEXCEPT_OPERATOR(__VA_ARGS__))

#endif
