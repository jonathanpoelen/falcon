#ifndef FALCON_CPP_REFERENCE_HPP
#define FALCON_CPP_REFERENCE_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_RVALUE_OR_CONST_REFERENCE &&
# define CPP_RVALUE_OR_REFERENCE &&
# define CPP_RVALUE &&
#else
# define CPP_RVALUE_OR_CONST_REFERENCE const &
# define CPP_RVALUE_OR_REFERENCE &
# define CPP_RVALUE
#endif

#endif
