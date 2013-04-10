#ifndef FALCON_CPP_BOOST_OR_STD_HPP
#define FALCON_CPP_BOOST_OR_STD_HPP

#if __cplusplus > 201100L
#define FALCON_BOOST_OR_STD_TRAITS(name_traits) <type_traits>
#else
#define FALCON_BOOST_OR_STD_TRAITS(name_traits) <boost/type_traits/name_traits.hpp>
#endif

#if __cplusplus > 201100L
#define FALCON_BOOST_OR_STD_NAMESPACE std
#else
#define FALCON_BOOST_OR_STD_NAMESPACE boost
#endif

#endif