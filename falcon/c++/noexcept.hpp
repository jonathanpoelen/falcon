#ifndef FALCON_CPP_NOEXCEPT_HPP
#define FALCON_CPP_NOEXCEPT_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_NOEXCEPT noexcept
# if defined(IN_IDE_PARSER)
#  define CPP_NOEXCEPT_OPERATOR(exp) noexcept(exp)
#  define CPP_NOEXCEPT_OPERATOR2(exp) noexcept(noexcept(exp))
# else
#  define CPP_NOEXCEPT_OPERATOR(...) noexcept(__VA_ARGS__)
#  define CPP_NOEXCEPT_OPERATOR2(...) noexcept(noexcept(__VA_ARGS__))
# endif
#else
# define CPP_NOEXCEPT throw()
# define CPP_NOEXCEPT_OPERATOR(exp)
# define CPP_NOEXCEPT_OPERATOR2(exp)
#endif

#endif
