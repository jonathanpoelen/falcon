#ifndef _FALCON_CPP_REFERENCE_HPP
#define _FALCON_CPP_REFERENCE_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define CPP_RVALUE_OR_CONST_REFERENCE(...) __VA_ARGS__&&
#else
# define CPP_RVALUE_OR_CONST_REFERENCE(...) const __VA_ARGS__&
#endif

#endif