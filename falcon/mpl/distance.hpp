#ifndef FALCON_MPL_DISTANCE_HPP
#define FALCON_MPL_DISTANCE_HPP

#include <falcon/mpl/iterator_category.hpp>
#include <falcon/mpl/integral_c.hpp>
#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/next.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/aux_/fold_impl.hpp>

namespace falcon {
namespace mpl {

template<typename Tag>
struct distance_impl
{
  template<typename First, typename Last>
  struct apply
  {
    typedef typename aux::fold_impl<
      deref_t
    , First
    , Last
    , mpl::long_<0>
    , next<arg<1>>
    >::type type;
  };
};

template<typename First, typename Last>
struct distance
{
  using type = typename distance_impl<iterator_category_t<First>>
  ::template apply<First, Last>::type;
  static const typename type::value_type value = type::value;
};

template<typename First, typename Last>
using distance_t = distance<First, Last>;


}
}

#endif
