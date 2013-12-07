#ifndef FALCON_MPL_COUNT_HPP
#define FALCON_MPL_COUNT_HPP

#include <falcon/mpl/aux_/count_if_impl.hpp>
#include <falcon/mpl/sequence_tag.hpp>
#include <falcon/mpl/count_fwd.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {

template<typename Tag>
struct count_impl
{
  template<typename Sequence, typename T>
  struct apply
  {
  private:
    template<typename U>
    using predicate = std::is_same<T, U>;

  public:
    using type = typename aux::count_if_impl<
      begin_t<Sequence>
    , end_t<Sequence>
    , predicate
    >::type;
  };
};

template<typename Sequence, typename T>
struct count
{
  using type = typename count_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence, T>::type;
  const static decltype(type::value) value = type::value;
};

template<typename Sequence, typename T>
using count_t = typename count<Sequence, T>::type;

}
}

#endif
