#ifndef _FALCON_CPP_NOEXCEPT_HPP
#define _FALCON_CPP_NOEXCEPT_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_NOEXCEPT noexcept
# if defined(IN_IDE_PARSER)
#  define CPP_NOEXCEPT_OPERATOR(expr...) noexcept(expr)
# else
#  define CPP_NOEXCEPT_OPERATOR(...) noexcept(__VA_ARGS__)
# endif
#else
# define CPP_NOEXCEPT
# define CPP_NOEXCEPT_OPERATOR(...)
#endif

#endif