#ifndef FALCON_MPL_AUX__CONTAINS_IMPL_HPP
#define FALCON_MPL_AUX__CONTAINS_IMPL_HPP

#include <falcon/mpl/integral_c.hpp>
#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/next.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {
namespace aux {

template<typename First, typename Last, typename T
, bool = std::is_same<deref_t<First>, T>::value>
struct contains_impl
: contains_impl<next_t<First>, Last, T>
{};

template<typename First, typename Last, typename T>
struct contains_impl<First, Last, T, true>
{ using type = true_; };

template<typename Last, typename T>
struct contains_impl<Last, Last, T, true>
{ using type = true_; };

template<typename Last, typename T>
struct contains_impl<Last, Last, T, false>
{ using type = false_; };

}
}
}

#endif
