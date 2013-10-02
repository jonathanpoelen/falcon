#ifndef FALCON_MEMORY_GROUPING_NEW_HPP
#define FALCON_MEMORY_GROUPING_NEW_HPP

#include <falcon/parameter/optimal_index_pack.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/memory/construct.hpp>
#include <falcon/utility/maker.hpp>
#include <falcon/arg/arg.hpp>

#include <array>
#include <tuple>

namespace falcon {

///TODO memory/align.hpp
#if defined(__GNUC__)
inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space)
{
  void* r = nullptr;
  if (size <= space)
  {
    char* p1 = static_cast<char*>(ptr);
    char* p2 = reinterpret_cast<char*>(reinterpret_cast<std::size_t>(p1 + (alignment - 1)) & -alignment);
    size_t d = static_cast<size_t>(p2 - p1);
    if (d <= space - size)
    {
      r = p2;
      ptr = r;
      space -= d;
    }
  }
  return r;
}
#else
using std::align;
#endif


template<std::size_t I, std::size_t N, std::size_t Idx, std::size_t... Indexes>
struct __initialize_optimal_grouping_allocae_tuple
{
  template<typename Tuple, typename Sizes>
  static void init(Tuple& t, const Sizes& szs)
  {
    get<I+1>(t) = reinterpret_cast<
      typename std::tuple_element<I+1, Tuple>::type
    >(static_cast<char*>(get<0>(t)) + szs[Idx]);
    __initialize_optimal_grouping_allocae_tuple<I+1,N,Indexes...>::init(t, szs);
  }
};

template<std::size_t N>
struct __initialize_optimal_grouping_allocae_tuple<N,N,0>
{
  template<typename Tuple, typename Sizes>
  static void init(Tuple&, const Sizes&)
  {}
};

template <typename Allocate, typename... Elements, std::size_t... Indexes, typename... S>
std::tuple<void*, Elements*...>
__optimal_grouping_allocate(parameter_index<Indexes...>, parameter_pack<Elements...>,
                            Allocate& allocate, S... sizes)
{
  typedef parameter_pack<Elements...> pack_t;
  typedef std::array<std::size_t, sizeof...(Indexes)> array_t;
  constexpr array_t a{{alignof(typename parameter_element<Indexes, pack_t>::type)...}};
  constexpr array_t szt{{sizeof(typename parameter_element<Indexes, pack_t>::type)...}};

  std::tuple<void*, Elements*...> ret(nullptr, maker<Elements*>()(nullptr)...);
  array_t szs{{arg<Indexes>(sizes...)...}};
  char * p = 0;
  size_t sz = -1u;

  for (std::size_t i = 0; i < sizeof...(Elements); ++i) {
    std::size_t size = szt[i] * szs[i];
    if (align(a[i], size, reinterpret_cast<void*&>(p), sz)) {
      szs[i] = p-static_cast<char*>(0);
      p += size;
      sz -= size;
    }
    else {
      return ret;
    }
  }

  get<0>(ret) = allocate(-1u - sz);
  __initialize_optimal_grouping_allocae_tuple<0, sizeof...(Elements), Indexes..., 0>
  ::init(ret, szs);

  return ret;
}

template <typename... Elements>
struct __grouping_allocate_result
{
  typedef parameter_pack<Elements*...> pack;
  typedef typename optimal_index_pack<pack>::type indexes;
  typedef typename parameter::pack_element<pack, indexes>::type optimal_parameter_pack;
  typedef typename parameter_pack_to_tuple<
    typename parameter::pack_add_left<optimal_parameter_pack, void*>::type
  >::type tuple;
};


template <typename... Elements, typename Allocate, typename... S>
typename __grouping_allocate_result<Elements...>::tuple
optimal_grouping_allocate(Allocate allocate, S... sizes)
{
  typedef __grouping_allocate_result<Elements...> __result_handler;
  typedef parameter_pack<Elements...> elements;
  typedef typename __result_handler::indexes indexes;
  return __optimal_grouping_allocate<>(indexes(), elements(), allocate, sizes...);
}

//TODO
// template <typename... Elements, typename... S>
// CPP1X_DELEGATE_FUNCTION(optimal_grouping_allocate(S... sizes),
//                         optimal_grouping_allocate(allocate_wrapper<char>(), sizes...))



template<std::size_t I, std::size_t N>
struct __initialize_grouping_allocae_tuple
{
  template<typename Tuple, typename Sizes>
  static void init(Tuple& t, const Sizes& szs)
  {
    get<I>(t) = reinterpret_cast<
      typename std::tuple_element<I, Tuple>::type
    >(static_cast<char*>(get<0>(t)) + szs[I]);
    __initialize_grouping_allocae_tuple<I+1,N>::init(t, szs);
  }
};

template<std::size_t N>
struct __initialize_grouping_allocae_tuple<N,N>
{
  template<typename Tuple, typename Sizes>
  static void init(Tuple&, const Sizes&)
  {}
};

template <typename... Elements, typename Allocate, typename... S>
std::tuple<Elements*...>
grouping_allocate(Allocate allocate, S... sizes)
{
  typedef std::array<std::size_t, sizeof...(Elements)> array_t;
  constexpr array_t a{{alignof(Elements)...}};
  constexpr array_t szt{{sizeof(Elements)...}};

  std::tuple<Elements*...> ret;
  array_t szs{{sizes...}};
  char * p = 0;
  size_t sz = -1u;

  for (std::size_t i = 0; i < sizeof...(Elements); ++i) {
    std::size_t size = szt[i] * szs[i];
    if (align(a[i], size, reinterpret_cast<void*&>(p), sz)) {
      szs[i] = p-static_cast<char*>(0);
      p += size;
      sz -= size;
    }
    else {
      return ret;
    }
  }

  get<0>(ret) = allocate(-1u - sz);
  __initialize_grouping_allocae_tuple<1, sizeof...(Elements)>::init(ret, szs);

  return ret;
}

template <typename... Elements, typename... S>
std::tuple<Elements*...> grouping_allocate(S... sizes)
{ return grouping_allocate(allocate_wrapper<char>(), sizes...); }

//TODO
// template <typename... Elements, typename... S>
// CPP1X_DELEGATE_FUNCTION(grouping_allocate(S... sizes),
//                         grouping_allocate(allocate_wrapper<char>(), sizes...))



template <typename T>
struct new_element
{
  typedef T type;
  std::size_t size;
  operator std::size_t () const
  { return size; }
};


template <typename T, typename... Elements>
CPP1X_DELEGATE_FUNCTION(optimal_grouping_allocate(new_element<T> e, Elements... elems),
                        optimal_grouping_allocate<typename T::type, typename Elements::type...>(e.size, static_cast<std::size_t>(elems)...))

template <typename Allocate, typename T, typename... Elements>
CPP1X_DELEGATE_FUNCTION(optimal_grouping_allocate(Allocate allocate,
                                                  new_element<T> e, Elements... elems),
                        optimal_grouping_allocate<typename T::type, typename Elements::type...>
                        (e.size, static_cast<std::size_t>(elems)...))

template <typename T, typename... Elements>
CPP1X_DELEGATE_FUNCTION(grouping_allocate(new_element<T> e, Elements... elems),
                        grouping_allocate<typename T::type, typename Elements::type...>(e.size, static_cast<std::size_t>(elems)...))

template <typename Allocate, typename T, typename... Elements>
CPP1X_DELEGATE_FUNCTION(grouping_allocate(Allocate allocate,
                                          new_element<T> e, Elements... elems),
                        grouping_allocate<typename T::type, typename Elements::type...>
                        (e.size, static_cast<std::size_t>(elems)...))

}

#endif
