#ifndef FALCON_MPL_AUX__EQUAL_IMPL_HPP
#define FALCON_MPL_AUX__EQUAL_IMPL_HPP

#include <falcon/mpl/next.hpp>
#include <falcon/mpl/apply.hpp>
#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/integral_c.hpp>
#include <falcon/type_traits/if.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<typename First1, typename Last1, typename First2, typename Last2, typename Pred>
struct equal_impl
: ::falcon::if_c_t<apply_t<Pred, deref_t<First1>, deref_t<First2>>
, equal_impl<next_t<First1>, Last1, next_t<First2>, Last1, Pred>
, false_
>
{};

template<typename Last1, typename Last2, typename Pred>
struct equal_impl<Last1, Last1, Last2, Last2, Pred>
: true_
{};

}
}
}

#endif
