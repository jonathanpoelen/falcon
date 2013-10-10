#ifndef FALCON_CPP_BOOST_OR_STD_HPP
#define FALCON_CPP_BOOST_OR_STD_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define FALCON_BOOST_OR_STD_NAMESPACE ::std
# define FALCON_BOOST_OR_STD_TRAITS(name_traits) <type_traits>
#else
# define FALCON_BOOST_OR_STD_NAMESPACE ::boost
# define FALCON_BOOST_OR_STD_TRAITS(name_traits) <boost/type_traits/name_traits.hpp>
#endif

#endif
