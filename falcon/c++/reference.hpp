#ifndef _FALCON_CPP_REFERENCE_HPP
#define _FALCON_CPP_REFERENCE_HPP

#if __cplusplus > 201100L
# define CPP_RVALUE_OR_CONST_REFERENCE(...) __VA_ARGS__&&
#else
# define CPP_RVALUE_OR_CONST_REFERENCE(...) const __VA_ARGS__&
#endif

#endif