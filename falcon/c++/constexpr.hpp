#ifndef _FALCON_CPP_CONSTEXPR_HPP
#define _FALCON_CPP_CONSTEXPR_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_CONSTEXPR constexpr
# define CPP_CONSTEXPR_OR_CONST constexpr
# if __cplusplus > 201103L
#   define CPP_CONSTEXPR_NOT_CONST constexpr
# else
#   define CPP_CONSTEXPR_NOT_CONST
# endif
# define CPP_GLOBAL_CONSTEXPR constexpr
#else
# define CPP_CONSTEXPR
# define CPP_CONSTEXPR_OR_CONST const
# define CPP_CONSTEXPR_NOT_CONST
# define CPP_GLOBAL_CONSTEXPR static const
#endif

#endif
