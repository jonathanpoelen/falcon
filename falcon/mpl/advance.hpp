#ifndef FALCON_MPL_ADVANCE_HPP
#define FALCON_MPL_ADVANCE_HPP

#include <falcon/mpl/iterator_category.hpp>
#include <falcon/mpl/integral_c.hpp>
#include <falcon/mpl/prior.hpp>
#include <falcon/mpl/next.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/if.hpp>
#include <falcon/mpl/aux_/fold_impl.hpp>

namespace falcon {
namespace mpl {

template<typename Tag>
struct advance_impl
{
  template<typename Iterator, typename N>
  struct apply
  {
  private:
    template<typename> struct noop {};

  public:
    using type = typename aux::fold_impl<
      noop
    , long_<0>
    , long_<(N::value < 0 ? -N::value : N::value)>
    , Iterator
    , if_c_t<(N::value < 0), next<arg<1>>, prior<arg<1>>>
    >::type;
  };
};


template<typename Iterator, typename N>
struct advance
{
  using type = typename advance_impl<iterator_category_t<Iterator>>
  ::template apply<Iterator, N>::type;
};

template<typename Iterator, long N>
using advance_c = advance<Iterator, long_<N>>;

template<typename Iterator, typename N>
using advance_t = typename advance<Iterator, N>::type;

template<typename Iterator, long N>
using advance_c_t = typename advance<Iterator, long_<N>>::type;

}}

#endif
