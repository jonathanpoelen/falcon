#ifndef FALCON_MPL_AUX__IS_ARG_HPP
#define FALCON_MPL_AUX__IS_ARG_HPP

#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/integral_c.hpp>

namespace falcon {
namespace mpl {

template<typename>
struct is_arg
: false_
{};

template<std::size_t N>
struct is_arg<arg<N>>
: true_
{};

}
}

#endif
