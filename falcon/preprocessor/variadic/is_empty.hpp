#ifndef _FALCON_PREPROCESSOR_VARIADIC_IS_EMPTY_HPP
#define _FALCON_PREPROCESSOR_VARIADIC_IS_EMPTY_HPP

#include <boost/preprocessor/control/if.hpp>
#include <falcon/preprocessor/variadic/size.hpp>

#define FALCON_PP_VARIADIC_IS_EMPTY(elem...)\
	BOOST_PP_IF(FALCON_PP_VARIADIC_SIZE(elem), 0,1)

#endif
