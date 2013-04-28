#ifndef _FALCON_CPP_STATIC_CONST_HPP
#define _FALCON_CPP_STATIC_CONST_HPP

#include <falcon/c++/constexpr.hpp>

#define CPP_STATIC_CONST(var, init) static CPP_CONSTEXPR_OR_CONST var = init

#endif