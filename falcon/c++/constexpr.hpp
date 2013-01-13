#ifndef _FALCON_CPP_CONSTEXPR_HPP
#define _FALCON_CPP_CONSTEXPR_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define CPP_CONSTEXPR constexpr
# define CPP_USE_CONSTEXPR constexpr
#else
# define CPP_CONSTEXPR
# define CPP_USE_CONSTEXPR const
#endif

#endif