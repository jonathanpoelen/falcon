#ifndef _FALCON_CPP_NOEXCEPT_HPP
#define _FALCON_CPP_NOEXCEPT_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define CPP_NOEXCEPT noexcept
#else
# define CPP_NOEXCEPT
#endif

#endif