#ifndef _FALCON_CPP_REFERENCE_HPP
#define _FALCON_CPP_REFERENCE_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_RVALUE_OR_CONST_REFERENCE &&
#else
# define CPP_RVALUE_OR_CONST_REFERENCE const &
#endif

#endif