#ifndef FALCON_MPL_VECTOR_HPP
#define FALCON_MPL_VECTOR_HPP

#include <falcon/mpl/at_fwd.hpp>
#include <falcon/mpl/size_fwd.hpp>
#include <falcon/mpl/clear_fwd.hpp>
#include <falcon/mpl/empty_fwd.hpp>
#include <falcon/mpl/begin_end_fwd.hpp>
#include <falcon/mpl/front_fwd.hpp>
#include <falcon/mpl/back_fwd.hpp>
#include <falcon/mpl/insert_fwd.hpp>
#include <falcon/mpl/insert_range_fwd.hpp>
#include <falcon/mpl/erase_fwd.hpp>
#include <falcon/mpl/push_front_fwd.hpp>
#include <falcon/mpl/push_back_fwd.hpp>
#include <falcon/mpl/pop_back_fwd.hpp>
#include <falcon/mpl/pop_front_fwd.hpp>
#include <falcon/mpl/detail/s_at.hpp>
#include <falcon/mpl/detail/s_size.hpp>
#include <falcon/mpl/detail/s_empty.hpp>
#include <falcon/mpl/detail/s_begin.hpp>
#include <falcon/mpl/detail/s_end.hpp>
#include <falcon/mpl/detail/s_front.hpp>
#include <falcon/mpl/detail/s_back.hpp>
#include <falcon/mpl/detail/s_insert.hpp>
#include <falcon/mpl/detail/s_insert_range.hpp>
#include <falcon/mpl/detail/s_erase.hpp>
#include <falcon/mpl/detail/s_push_front.hpp>
#include <falcon/mpl/detail/s_push_back.hpp>
#include <falcon/mpl/detail/s_pop_back.hpp>
#include <falcon/mpl/detail/s_pop_front.hpp>
#include <falcon/mpl/detail/seq.hpp>
#include <falcon/mpl/aux_/iter.hpp>
#include <falcon/mpl/integral_c.hpp>

namespace falcon {
namespace mpl {

namespace aux {
  struct vector_tag {};
}

template<typename... Args>
using vector = detail::seq<aux::vector_tag, Args...>;

template<>
struct size_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  : detail::s_size<typename Vector::type>
  {};
};

template<>
struct empty_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  : detail::s_empty<typename Vector::type>
  {};
};

template<>
struct begin_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  { using type = aux::random_access_iterator_impl<Vector, uint_<0>>; };
};

template<>
struct end_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  {
    using type = aux::random_access_iterator_impl<
      Vector
    , uint_<detail::s_size<Vector>::value>
    >;
  };
};

template<>
struct front_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  : detail::s_front<typename Vector::type>
  {};
};

template<>
struct back_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  : detail::s_back<typename Vector::type>
  {};
};

template<>
struct at_impl<aux::vector_tag>
{
  template<typename Vector, typename N>
  struct apply
  : detail::s_at<typename Vector::type, N::value>
  {};
};

template<>
struct insert_impl<aux::vector_tag>
{
  template<typename Vector, typename Pos, typename T>
  struct apply
  : detail::s_insert<typename Vector::type, Pos::value, T>
  {};
};

template<>
struct insert_range_impl<aux::vector_tag>
{
  template<typename Vector, typename Pos, typename Range>
  struct apply
  : detail::s_insert_range<typename Vector::type, Pos::value, Range>
  {};
};

template<>
struct erase_impl<aux::vector_tag>
{
  template<typename Vector, typename Pos, typename Last>
  struct apply
  : detail::s_erase<typename Vector::type, Pos::value, Last>
  {};
};

template<>
struct clear_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  { using type = vector<>; };
};

template<>
struct push_back_impl<aux::vector_tag>
{
  template<typename Vector, typename T>
  struct apply
  : detail::s_push_back<typename Vector::type, T>
  {};
};

template<>
struct push_front_impl<aux::vector_tag>
{
  template<typename Vector, typename T>
  struct apply
  : detail::s_push_front<typename Vector::type, T>
  {};
};

template<>
struct pop_front_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  : detail::s_pop_front<typename Vector::type>
  {};
};

template<>
struct pop_back_impl<aux::vector_tag>
{
  template<typename Vector>
  struct apply
  : detail::s_pop_back<typename Vector::type>
  {};
};

}
}

#endif
