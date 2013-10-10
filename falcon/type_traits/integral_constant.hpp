#ifndef FALCON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define FALCON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(integral_constant)

namespace falcon {
  using FALCON_BOOST_OR_STD_NAMESPACE::integral_constant;
  using FALCON_BOOST_OR_STD_NAMESPACE::true_type;
  using FALCON_BOOST_OR_STD_NAMESPACE::false_type;
}

#endif
