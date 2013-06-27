#ifndef _FALCON_PREPROCESSOR_VARIADIC_HAS_PARENTHESIS_HPP
#define _FALCON_PREPROCESSOR_VARIADIC_HAS_PARENTHESIS_HPP

#include <boost/preprocessor/dec.hpp>
#include <falcon/preprocessor/variadic/size.hpp>
#include <falcon/preprocessor/variadic/punctuation.hpp>

#define FALCON_PP_VARIADIC_HAS_PARENTHESIS(a)\
	BOOST_PP_DEC(FALCON_PP_VARIADIC_SIZE(FALCON_PP_VARIADIC_COMMA a))

#endif