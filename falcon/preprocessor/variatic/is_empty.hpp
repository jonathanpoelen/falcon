#ifndef _FALCON_PREPROCESSOR_VARIATIC_IS_EMPTY_HPP
#define _FALCON_PREPROCESSOR_VARIATIC_IS_EMPTY_HPP

#include <boost/preprocessor/if.hpp>
#include <falcon/preprocessor/variatic/size.hpp>

#define FALCON_PP_VARIADIC_IS_EMPTY(elem...)\
	BOOST_PP_IF(FALCON_PP_VARIADIC_SIZE(elem), 0,1)

#endif