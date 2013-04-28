#ifndef FALCON_CPP_CAST_HPP
#define FALCON_CPP_CAST_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_EXPLICIT_CAST explicit
#else
# define CPP_EXPLICIT_CAST
#endif

#define CPP_EXPLICIT_BOOL_CAST(_Cast)\
	CPP_EXPLICIT_CAST operator bool() const\
	{ return _Cast; }

#endif