#ifndef _FALCON_PREPROCESSOR_VARIATIC_HAS_PARENTHESIS_HPP
#define _FALCON_PREPROCESSOR_VARIATIC_HAS_PARENTHESIS_HPP

#include <boost/preprocessor/dec.hpp>
#include <falcon/preprocessor/variatic/size.hpp>
#include <falcon/preprocessor/variatic/punctuation.hpp>

#define FALCON_PP_VARIADIC_HAS_PARENTHESIS(a)\
	BOOST_PP_DEC(FALCON_PP_VARIADIC_SIZE(FALCON_PP_VARIADIC_COMMA a))

#endif