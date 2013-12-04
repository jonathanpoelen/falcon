#ifndef FALCON_MPL_AUX__FIND_IMPL_HPP
#define FALCON_MPL_AUX__FIND_IMPL_HPP

#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/next.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {
namespace aux {

template<typename First, typename Last, typename T, bool = std::is_same<deref_t<First>, T>::value>
struct find_impl
: find_impl<next_t<First>, Last, T>
{};

template<typename First, typename Last, typename T>
struct find_impl<First, Last, T, true>
{ using type = First; };

template<typename Last, typename T>
struct find_impl<Last, Last, T, true>
{ using type = Last; };

template<typename Last, typename T>
struct find_impl<Last, Last, T, false>
{ using type = Last; };

}
}
}

#endif
