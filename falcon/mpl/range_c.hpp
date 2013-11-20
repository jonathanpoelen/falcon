#ifndef FALCON_MPL_RANGE_C_HPP
#define FALCON_MPL_RANGE_C_HPP

#include <falcon/mpl/protect.hpp>
#include <falcon/mpl/integral.hpp>
#include <falcon/mpl/detail/iterator.hpp>
#include <falcon/type_traits/eval_if.hpp>

namespace falcon {
namespace mpl {

template<typename T, T Start, T Finish>
struct range_c
{
  using start = integral_c<T,Start>;
  using finish = integral_c<T,Finish>;
};

namespace detail {

template<typename Range, typename Pos>
struct range_iterator_impl
: mpl_iterator_def
{
  static const unsigned pos = unsigned(Pos::value);
  using type = typename ::falcon::eval_if<
    (pos >= Range::finish - Range::start),
    void_,
    integral_c<typename Pos::type, Range::start + pos>
  >::type;
  using next = range_iterator_impl<Range, uint_<pos+1> >;
  using prior = range_iterator_impl<Range, uint_<pos-1> >;

  template<typename T>
  struct advance
  { using type = range_iterator_impl<Range, uint_<pos+T::value> >; };

  template<typename T>
  struct recoil
  { using type = range_iterator_impl<Range, uint_<pos-T::value> >; };
};

}

namespace aux {

template<typename T, T Start, T Finish>
struct size<range_c<T, Start, Finish>>
{ static const std::size_t value = Finish - Start; };

template<typename T, T Start, T Finish>
struct empty<range_c<T, Start, Finish>>
{ static const bool value = Start == Finish; };

template<typename T, T Start, T Finish>
struct begin<range_c<T, Start, Finish>>
{ using type = detail::range_iterator_impl<range_c<T, Start, Finish>, uint_<0>>; };

template<typename T, T Start, T Finish>
struct end<range_c<T, Start, Finish>>
{ using type = detail::range_iterator_impl<range_c<T, Start, Finish>, uint_<Finish-Start> >; };

template<typename T, T Start, T Finish>
struct front<range_c<T, Start, Finish>>
{ using type = integral_c<T, Start>; };

template<typename T, T Start, T Finish>
struct back<range_c<T, Start, Finish>>
{ using type = integral_c<T, Finish>; };

template<typename T, T Start, T Finish, typename Pos>
struct at<range_c<T, Start, Finish>, Pos, detail::na>
{ using type = typename ::falcon::eval_if<
    (Pos::value >= Finish - Start),
    void_,
    integral_c<T, Start + Pos::value>
  >::type;
};

}

}
}

#endif
