#ifndef FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP
#define FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/preprocessor/concat.hpp>
#include <falcon/preprocessor/nil.hpp>
#include <falcon/fn/range.hpp>
#include <falcon/arg/arg.hpp>

#include <iterator>
#include <tuple>

namespace falcon {

#define MAKE_RANGE_ACCESS_TRAITS(prefix_name, prefix_func) \
struct FALCON_CONCAT(prefix_name, range_access_traits)     \
{                                                          \
  template<class Cont>                                     \
  static auto begin(Cont & cont)                           \
  -> decltype(fn::FALCON_CONCAT(prefix_func, begin)(cont)) \
  { return fn::FALCON_CONCAT(prefix_func, begin)(cont); }  \
                                                           \
  template<class Cont>                                     \
  static auto end(Cont & cont)                             \
  -> decltype(fn::FALCON_CONCAT(prefix_func, end)(cont))   \
  { return fn::FALCON_CONCAT(prefix_func, end)(cont); }    \
}

/// begin()/end() traits
MAKE_RANGE_ACCESS_TRAITS(FALCON_PP_NIL(), FALCON_PP_NIL());
/// rbegin()/rend() traits
MAKE_RANGE_ACCESS_TRAITS(reverse_, r);
/// cbegin()/cend() traits
MAKE_RANGE_ACCESS_TRAITS(const_, c);
/// crbegin()/crend() traits
MAKE_RANGE_ACCESS_TRAITS(const_reverse_, cr);

#undef MAKE_RANGE_ACCESS_TRAITS

/// transforms the iterator returned by RangeAccessTraits
template<
  class ToIterator
, class RangeAccessTraits = range_access_traits
, class... Elements>
struct iterator_range_access_traits
: private std::tuple<Elements...>
{
private:
  using tuple_type_ = std::tuple<Elements...>;
  using indexes = build_parameter_index_t<sizeof...(Elements)>;

public:
  iterator_range_access_traits() = default;

  iterator_range_access_traits(iterator_range_access_traits const &) = default;
  iterator_range_access_traits(iterator_range_access_traits &&) = default;

  template<class... TElements>
  iterator_range_access_traits(TElements && ... args)
  : tuple_type_(std::forward<TElements>(args)...)
  {}

  template<class Cont>
  ToIterator begin(Cont & cont) const
  { return dispatch_(RangeAccessTraits::begin(cont), indexes()); }

  template<class Cont>
  ToIterator end(Cont & cont) const
  { return dispatch_(RangeAccessTraits::end(cont), indexes()); }

private:
  template<class It, std::size_t... Ints>
  ToIterator dispatch_(It && it, parameter_index<Ints...>) const
  { return ToIterator(
    std::move(it)
  , std::get<Ints>(static_cast<tuple_type_ const&>(*this))...
  ); }
};

template<class ToIterator, class RangeAccessTraits>
struct iterator_range_access_traits<ToIterator, RangeAccessTraits>
{
  template<class Cont>
  static ToIterator begin(Cont & cont)
  { return ToIterator(RangeAccessTraits::begin(cont)); }

  template<class Cont>
  static ToIterator end(Cont & cont)
  { return ToIterator(RangeAccessTraits::end(cont)); }
};

template<class Access, class Cont>
using range_access_to_iterator
  = decltype(static_cast<Access*>(0)->begin(*static_cast<Cont*>(0)));

}

#endif
