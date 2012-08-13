#ifndef _FALCON_LITERAL_DETAIL_LITERAL_SUPPORT_HPP
#define _FALCON_LITERAL_DETAIL_LITERAL_SUPPORT_HPP

//TODO #include <boost/select_compiler_config.hpp>

#if defined __GNUC__
# ifndef __GXX_EXPERIMENTAL_CXX0X__
#  include <falcon/c++0x/warning.hpp>
# elif __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)
#  error Your compiler not supported literal definition.
# endif
#endif

#endif