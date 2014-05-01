#ifndef FALCON_TUPLE_OPTIMAL_TUPLE_HPP
#define FALCON_TUPLE_OPTIMAL_TUPLE_HPP

#include <falcon/parameter/optimal_index_pack.hpp>
#include <falcon/parameter/index_element.hpp>
#include <falcon/parameter/pack_element.hpp>
#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/utility/unpack.hpp>
#include <falcon/arg/arg.hpp>

#include <utility>
#include <tuple>

namespace falcon {

template<typename Tuple>
struct optimal_tuple_traits;

template<typename... Params>
struct optimal_tuple_traits<std::tuple<Params...>>
{
  typedef std::tuple<Params...> tuple_base;

private:
  typedef typename tuple_to_parameter_pack<tuple_base>::type parameter_pack;

  typedef typename optimal_index_pack<parameter_pack>::type indexes;

public:
  typedef typename parameter_pack_to_tuple<
    typename pack_element<parameter_pack, indexes>::type
  >::type tuple;
  typedef tuple type;

  template<std::size_t I>
  struct idx
  { static const std::size_t value = index_element<I, indexes>::value; };

  template<std::size_t I>
  struct tuple_element
  { typedef typename std::tuple_element<idx<I>::value, tuple_base>::type type; };

  struct tuple_size
  { static const std::size_t value = std::tuple_size<tuple_base>::value; };

  constexpr static std::size_t size()
  { return tuple_size::value; }

  template<std::size_t I>
  static typename tuple_element<I>::type& get(tuple_base& t)
  { return std::get<idx<I>::value>(t); }

  template<std::size_t I>
  static const typename tuple_element<I>::type& get(const tuple_base& t)
  { return std::get<idx<I>::value>(t); }

  template<std::size_t I>
  static typename tuple_element<I>::type&& get(tuple_base&& t)
  { return std::get<idx<I>::value>(std::forward<tuple_base>(t)); }
};


template<typename Tuple>
class optimal_tuple
{
  using indexes = build_parameter_index_t<std::tuple_size<Tuple>::value>;
public:
  using traits_type = optimal_tuple_traits<Tuple>;

private:
  struct spa{};
  struct spt{};
  struct opti_impl
  {
    opti_impl() = default;

    template<std::size_t... Indexes, typename... Args>
    opti_impl(spa, parameter_index<Indexes...>, Args&&... args)
    : tuple(arg<traits_type::template idx<Indexes>::value>(
      std::forward<Args>(args)...)...
    )
    {}

    template<std::size_t... Indexes, typename Tuple2>
    opti_impl(spt, parameter_index<Indexes...>, Tuple2&& t)
    : tuple(traits_type::template get<Indexes>(std::forward<Tuple2>(t))...)
    {}

    template<typename Tuple2>
    opti_impl(Tuple2&& t)
    : tuple(std::forward<Tuple2>(t))
    {}

    template<typename Tuple2, std::size_t... Indexes>
    void assign(parameter_index<Indexes...>, Tuple2&& t)
    {
      FALCON_UNPACK(traits_type::get<Indexes>(tuple)
      = get<Indexes>(std::forward<Tuple2>(t)));
    }

    typename traits_type::tuple tuple;
  };

public:
  optimal_tuple() = default;

  template<typename Tuple2>
  optimal_tuple(Tuple2&& t)
  : _M_impl(typename std::conditional<traits_type::size() != 1, spt, spa>::type(),
            indexes(), std::forward<Tuple2>(t))
  {}

  template<typename... Args>
  optimal_tuple(Args&&... args)
  : _M_impl(spa(), indexes(), std::forward<Args>(args)...)
  {}

  template<typename Tuple2>
  optimal_tuple(optimal_tuple<Tuple2>&& other)
  : _M_impl(std::forward<Tuple2>(other.impl.tuple))
  {}

  template<typename Tuple2>
  optimal_tuple& operator=(Tuple2&& t)
  {
    _M_impl.assign(indexes(), std::forward<Tuple2>(t));
    return *this;
  }

  template<typename Tuple2>
  optimal_tuple& operator=(optimal_tuple<Tuple2>&& other)
  {
    _M_impl.tuple = std::forward<Tuple2>(other.impl.tuple);
    return *this;
  }

public:
  opti_impl _M_impl;
};


template<typename Tuple>
struct is_tuple_impl<optimal_tuple<Tuple>>
: std::true_type
{};

template<std::size_t I, typename Tuple>
auto get(optimal_tuple<Tuple>&& t)
-> decltype(optimal_tuple_traits<Tuple>::
  template get<I>(std::forward<Tuple>(t._M_impl.tuple)))
{
  return optimal_tuple_traits<Tuple>::
  template get<I>(std::forward<Tuple>(t._M_impl.tuple));
}

template<std::size_t I, typename Tuple>
auto get(const optimal_tuple<Tuple>& t)
-> decltype(optimal_tuple_traits<Tuple>::template get<I>(t._M_impl.tuple))
{ return optimal_tuple_traits<Tuple>::template get<I>(t._M_impl.tuple); }

template<std::size_t I, typename Tuple>
auto get(optimal_tuple<Tuple>& t)
-> decltype(optimal_tuple_traits<Tuple>::template get<I>(t._M_impl.tuple))
{ return optimal_tuple_traits<Tuple>::template get<I>(t._M_impl.tuple); }

}

namespace std {

template<typename Tuple>
struct tuple_size<::falcon::optimal_tuple<Tuple>>
: public integral_constant<std::size_t, ::falcon::optimal_tuple_traits<Tuple>::size()>
{};

template<std::size_t I, typename Tuple>
struct tuple_element<I, ::falcon::optimal_tuple<Tuple>>
{
  typedef typename ::falcon::optimal_tuple_traits<Tuple>::
  template tuple_element<I>::type type;
};

}

#endif
