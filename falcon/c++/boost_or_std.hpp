#ifndef FALCON_CPP_BOOST_OR_STD_HPP
#define FALCON_CPP_BOOST_OR_STD_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#define FALCON_BOOST_OR_STD_TRAITS(name_traits) <type_traits>
#else
#define FALCON_BOOST_OR_STD_TRAITS(name_traits) <boost/type_traits/name_traits.hpp>
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#define FALCON_BOOST_OR_STD_NAMESPACE std
#else
#define FALCON_BOOST_OR_STD_NAMESPACE boost
#endif

#endif