#ifndef FALCON_MPL_AUX__FIND_IF_IMPL_HPP
#define FALCON_MPL_AUX__FIND_IF_IMPL_HPP

#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/next.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<typename First, typename Last, template <typename> class Pred
, bool = Pred<deref_t<First>>::value>
struct find_if_impl
: find_if_impl<next_t<First>, Last, Pred>
{};

template<typename First, typename Last, template <typename> class Pred>
struct find_if_impl<First, Last, Pred, true>
{ using type = First; };

template<typename Last, template <typename> class Pred>
struct find_if_impl<Last, Last, Pred, true>
{ using type = Last; };

template<typename Last, template <typename> class Pred>
struct find_if_impl<Last, Last, Pred, false>
{ using type = Last; };

}
}
}

#endif
