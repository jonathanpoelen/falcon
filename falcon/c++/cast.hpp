#ifndef FALCON_CPP_CAST_HPP
#define FALCON_CPP_CAST_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define CPP_EXPLICIT_CAST explicit
#else
# define CPP_EXPLICIT_CAST
#endif

#define CPP_EXPLICIT_BOOL_CAST(_Cast)\
	CPP_EXPLICIT_CAST operator bool() const\
	{ return _Cast; }

#endif