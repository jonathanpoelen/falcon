#ifndef _FALCON_CPP_NOEXCEPT_HPP
#define _FALCON_CPP_NOEXCEPT_HPP

#if __cplusplus > 201100L
# define CPP_NOEXCEPT noexcept
#else
# define CPP_NOEXCEPT
#endif

#endif