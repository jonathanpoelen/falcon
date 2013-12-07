#ifndef FALCON_MPL_AUX__COUNT_IF_IMPL_HPP
#define FALCON_MPL_AUX__COUNT_IF_IMPL_HPP

#include <falcon/mpl/integral_c.hpp>
#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/next.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<typename First, typename Last, template <typename> class Pred
, std::size_t N = 0, bool X = Pred<deref_t<First>>::value>
struct count_if_impl
: count_if_impl<next_t<First>, Last, Pred, N + (X?1:0)>
{};

template<typename Last, template <typename> class Pred, std::size_t N, bool Contains>
struct count_if_impl<Last, Last, Pred, N, Contains>
{ using type = integral_c<std::size_t, N>; };

}
}
}

#endif
