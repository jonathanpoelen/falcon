#ifndef FALCON_TUPLE_OPTIMAL_TUPLE_HPP
#define FALCON_TUPLE_OPTIMAL_TUPLE_HPP

#include <falcon/parameter/optimal_index_pack.hpp>
#include <falcon/parameter/index_element.hpp>
#include <falcon/parameter/pack_element.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/tuple/is_tuple_like.hpp>
#include <falcon/utility/unpack.hpp>
#include <falcon/arg/arg.hpp>

#include <utility>
#include <tuple>

namespace falcon {

template<typename... Elements>
struct optimal_tuple_traits
{
  typedef std::tuple<Elements...> tuple_base;

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
  { static const std::size_t value = sizeof...(Elements); };

  constexpr static std::size_t size()
  { return tuple_size::value; }

  template<std::size_t I>
  constexpr static typename tuple_element<I>::type&
  get(tuple_base& t)
  {
    using std::get;
    return get<idx<I>::value>(t);
  }

  template<std::size_t I>
  constexpr static const typename tuple_element<I>::type&
  get(const tuple_base& t)
  {
    using std::get;
    return get<idx<I>::value>(t);
  }

  template<std::size_t I>
  constexpr static typename tuple_element<I>::type&&
  get(tuple_base&& t)
  {
    using std::get;
    return get<idx<I>::value>(std::forward<tuple_base>(t));
  }
};


template<class... Elements>
class optimal_tuple
{
  using indexes = build_parameter_index_t<sizeof...(Elements)>;
public:
  using traits_type = optimal_tuple_traits<Elements...>;

private:
  struct spa{};
  struct spt{};
  struct opti_impl
  {
    opti_impl() = default;

    template<std::size_t... Indexes, typename... Args>
    constexpr opti_impl(spa, parameter_index<Indexes...>, Args&&... args)
    : tuple(arg<traits_type::template idx<Indexes>::value>(
      std::forward<Args>(args)...)...
    )
    {}

    template<std::size_t... Indexes, typename Tuple2>
    constexpr opti_impl(spt, parameter_index<Indexes...>, Tuple2&& t)
    : tuple(traits_type::template get<Indexes>(std::forward<Tuple2>(t))...)
    {}

    template<typename Tuple2>
    constexpr opti_impl(Tuple2&& t)
    : tuple(std::forward<Tuple2>(t))
    {}

    template<typename Tuple2, std::size_t... Indexes>
    void assign(parameter_index<Indexes...>, Tuple2&& t)
    {
      using std::get;
      FALCON_UNPACK(traits_type::get<Indexes>(tuple)
        = get<Indexes>(std::forward<Tuple2>(t)));
    }

    typename traits_type::tuple tuple;
  };

public:
  optimal_tuple() = default;

  template<typename Tuple2>
  constexpr optimal_tuple(Tuple2&& t)
  : impl_(typename std::conditional<traits_type::size() != 1, spt, spa>::type(),
            indexes(), std::forward<Tuple2>(t))
  {}

  template<typename... Args>
  constexpr optimal_tuple(Args&&... args)
  : impl_(spa(), indexes(), std::forward<Args>(args)...)
  {}

  template<typename... Elements2>
  constexpr optimal_tuple(optimal_tuple<Elements2...>&& other)
  : impl_(std::forward<Elements2...>(other.impl.tuple))
  {}

  template<typename Tuple2>
  optimal_tuple& operator=(Tuple2&& t)
  {
    impl_.assign(indexes(), std::forward<Tuple2>(t));
    return *this;
  }

  template<typename... Elements2>
  optimal_tuple& operator=(optimal_tuple<Elements2...>&& other)
  {
    impl_.tuple = std::forward<Elements2...>(other.impl.tuple);
    return *this;
  }

public:
  opti_impl impl_;
};


template<class... Elements>
struct is_tuple_like<optimal_tuple<Elements...>>
: std::true_type
{};

template<std::size_t I, class... Elements>
constexpr auto get(optimal_tuple<Elements...>&& t)
-> decltype(optimal_tuple_traits<Elements...>::
  template get<I>(std::forward<Elements...>(t.impl_.tuple)))
{
  return optimal_tuple_traits<Elements...>::
  template get<I>(std::forward<Elements...>(t.impl_.tuple));
}

template<std::size_t I, class... Elements>
constexpr auto get(const optimal_tuple<Elements...>& t)
-> decltype(optimal_tuple_traits<Elements...>::template get<I>(t.impl_.tuple))
{ return optimal_tuple_traits<Elements...>::template get<I>(t.impl_.tuple); }

template<std::size_t I, class... Elements>
constexpr auto get(optimal_tuple<Elements...>& t)
-> decltype(optimal_tuple_traits<Elements...>::template get<I>(t.impl_.tuple))
{ return optimal_tuple_traits<Elements...>::template get<I>(t.impl_.tuple); }

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
