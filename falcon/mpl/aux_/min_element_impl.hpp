#ifndef FALCON_MPL_AUX__MIN_ELEMENT_IMPL_HPP
#define FALCON_MPL_AUX__MIN_ELEMENT_IMPL_HPP

#include <falcon/mpl/next.hpp>
#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/aux_/fold_impl.hpp>
#include <falcon/type_traits/wrap.hpp>
#include <falcon/type_traits/if.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template <typename First, typename Last, typename Pred>
struct min_element_impl
: fold_impl<deref_t, next_t<First>, Last, deref_t<First>, Pred>
{
private:
  struct predicate
  {
    template<typename Iter, typename Iter2>
    using apply = ::falcon::if_c<apply_t<Pred, deref_t<Iter>, deref_t<Iter2>>, Iter, Iter2>;
  };

public:
  using type = typename aux::fold_impl<wrap_t, next_t<First>, Last, First, predicate>::type;
};

template <typename Last, typename Pred>
struct min_element_impl<Last, Last, Pred>
{ using type = Last; };

}
}
}

#endif
