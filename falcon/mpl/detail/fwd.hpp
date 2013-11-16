#ifndef FALCON_MPL_DETAIL_FWD_HPP
#define FALCON_MPL_DETAIL_FWD_HPP

#include <falcon/config.hpp>

#include <type_traits>

namespace falcon {
namespace mpl {

struct mpl_apply_def
{ using mpl_type = std::true_type; };

namespace detail {
  template<typename T, T x>
  struct integral
  { static const T value = x; };

  template<typename T, typename Integral = typename T::mpl_type>
  constexpr bool has_mpl_type_impl(int, const Integral& = Integral())
  { return Integral::value; }

  template<typename T>
  constexpr bool has_mpl_type_impl(unsigned)
  { return 0; }

  template<typename...>
  struct seq;
}

class na;

#ifdef IN_IDE_PARSER
# define FALCON_MPL_DEF_TYPE(name) struct name { using type = na; }
# define FALCON_MPL_DEF_TYPE_AND_VALUE(name) struct name { using type = na; \
  static const int value = 0; }
#else
# define FALCON_MPL_DEF_TYPE(name) class name
# define FALCON_MPL_DEF_TYPE_AND_VALUE(name) class name
#endif

template<typename Seq>
FALCON_MPL_DEF_TYPE_AND_VALUE(size);

template<typename Seq>
FALCON_MPL_DEF_TYPE_AND_VALUE(empty);

template <typename Seq>
FALCON_MPL_DEF_TYPE(begin);

template <typename Seq>
FALCON_MPL_DEF_TYPE(end);

template<typename Seq>
FALCON_MPL_DEF_TYPE(front);

template<typename Seq>
FALCON_MPL_DEF_TYPE(back);

template<typename Seq, typename Pos>
FALCON_MPL_DEF_TYPE(at);

template<typename Seq, typename Pos, typename T>
FALCON_MPL_DEF_TYPE(insert);

template<typename Seq, typename Pos, typename Range>
FALCON_MPL_DEF_TYPE(insert_range);

template<typename Seq, typename Pos, typename Last = na>
FALCON_MPL_DEF_TYPE(erase);

template<typename Seq>
FALCON_MPL_DEF_TYPE(clear);

template<typename Seq, typename T>
FALCON_MPL_DEF_TYPE(push_back);

template<typename Seq, typename T>
FALCON_MPL_DEF_TYPE(push_front);

template<typename Seq>
FALCON_MPL_DEF_TYPE(pop_back);

template<typename Seq>
FALCON_MPL_DEF_TYPE(pop_front);

#undef FALCON_MPL_DEF_TYPE
#undef FALCON_MPL_DEF_TYPE_AND_VALUE

}
}

#endif
