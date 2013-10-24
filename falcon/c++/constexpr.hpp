#ifndef _FALCON_CPP_CONSTEXPR_HPP
#define _FALCON_CPP_CONSTEXPR_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_CONSTEXPR constexpr
# define CPP_CONSTEXPR_OR_CONST constexpr
# if __cplusplus < 201403L
#  define CPP_CONSTEXPR_NOT_CONST
# else
#  define CPP_CONSTEXPR_NOT_CONST constexpr
# endif
#else
# define CPP_CONSTEXPR
# define CPP_CONSTEXPR_OR_CONST const
# define CPP_CONSTEXPR_NOT_CONST
#endif

#endif
