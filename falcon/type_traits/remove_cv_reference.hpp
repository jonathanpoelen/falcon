#ifndef FALCON_TYPE_TRAITS_REMOVE_CV_REFERENCE_HPP
#define FALCON_TYPE_TRAITS_REMOVE_CV_REFERENCE_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)
#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)

namespace falcon {

template<typename T>
struct remove_cv_reference
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<
    typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type
  >::type type;
};

}

#endif
