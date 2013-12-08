#ifndef FALCON_MPL_EQUAL_HPP
#define FALCON_MPL_EQUAL_HPP

#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/size.hpp>
#include <falcon/mpl/is_same.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/integral_c.hpp>
#include <falcon/mpl/aux_/equal_impl.hpp>
#include <falcon/type_traits/if.hpp>

namespace falcon {
namespace mpl {

template<typename Seq1, typename Seq2, typename Pred = is_same<arg<1>,arg<2>>>
struct equal
{
private:
  struct impl
  : aux::equal_impl<
    begin_t<Seq1>
  , end_t<Seq1>
  , begin_t<Seq2>
  , end_t<Seq2>
  , Pred
  >{};

public:
  using type = ::falcon::if_t<(size<Seq1>::value == size<Seq2>::value), impl, false_>;
  static const bool value = type::value;
};

template<typename Seq1, typename Seq2, typename Pred = is_same<arg<1>,arg<2>>>
using equal_t = typename equal<Seq1, Seq2, Pred>::type;

}
}

#endif
