#ifndef FALCON_MPL_IS_PLACEHOLDER_HPP
#define FALCON_MPL_IS_PLACEHOLDER_HPP

#include <falcon/mpl/arg.hpp>

#include <type_traits>

namespace falcon {
namespace mpl {

template< typename T >
struct is_placeholder
: std::false_type
{};

template<std::size_t N>
struct is_placeholder<arg<N>>
: std::true_type
{};


}
}

#endif
