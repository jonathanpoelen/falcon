#ifndef FALCON_MEMORY_TEMPORARY_RAW_STORAGE_HPP
#define FALCON_MEMORY_TEMPORARY_RAW_STORAGE_HPP

#include <falcon/type_traits/is_nothrow_swap.hpp>
#include <falcon/parameter/optimal_index_pack.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/parameter/index_element.hpp>
#include <falcon/tuple/optimal_tuple.hpp>
#include <falcon/memory/allocate.hpp>
#include <falcon/utility/unpack.hpp>
#include <falcon/functional/arg.hpp>

#include <type_traits>
#include <memory>
#include <array>
#include <tuple>

namespace falcon {

namespace _aux {
  template<class>
  using usingsize__t = std::size_t;
}

/**
 * Allocates storage containing \a Elements types
 */
template<class Allocator, class... Elements>
class temporary_raw_storage_with_allocator
{
  typedef typename std::allocator_traits<Allocator>
    ::template rebind_alloc<char> internal_allocator;

  typedef std::allocator_traits<internal_allocator> allocator_traits;
  typedef typename allocator_traits::size_type size_type;
  typedef typename allocator_traits::pointer pointer;

  static constexpr bool is_noexcept()
  { return noexcept(allocator_traits::allocate(std::declval<internal_allocator&>(), size_type(0))); }

public:
  typedef Allocator allocator_type;
  typedef std::tuple<Elements*...> tuple_type;
  typedef tuple_type type;

  temporary_raw_storage_with_allocator()
  noexcept(noexcept(internal_allocator()))
  : t(0, tuple_type(), internal_allocator())
  {}

  explicit
  temporary_raw_storage_with_allocator(_aux::usingsize__t<Elements>... sizes)
  noexcept(temporary_raw_storage_with_allocator::is_noexcept())
  : t(0, tuple_type(), internal_allocator())
  { init_(indexes(), optimal_indexes(), sizes...); }

  explicit
  temporary_raw_storage_with_allocator(
    const allocator_type & alloc, _aux::usingsize__t<Elements>... sizes)
  noexcept(temporary_raw_storage_with_allocator::is_noexcept())
  : t(0, tuple_type(), internal_allocator(alloc))
  { init_(indexes(), optimal_indexes(), sizes...); }

  temporary_raw_storage_with_allocator(
    temporary_raw_storage_with_allocator && other) noexcept
  : t(std::move(other.t))
  {
    get<0>(other.t) = 0;
    get<1>(other.t) = tuple_type();
  }

  temporary_raw_storage_with_allocator &
  operator=(temporary_raw_storage_with_allocator && other) noexcept
  {
    using std::swap;
    temporary_raw_storage_with_allocator tmp(std::move(other));
    swap(tmp, *this);
    return *this;
  }

  temporary_raw_storage_with_allocator(temporary_raw_storage_with_allocator const &) = delete;

  temporary_raw_storage_with_allocator&
  operator=(temporary_raw_storage_with_allocator const &) = delete;

  ~temporary_raw_storage_with_allocator()
  { allocator_traits::deallocate(allocator_(), pointer_(), size_()); }

  /**
   * \return tuple on uninitialized pointers
   */
  const tuple_type &
  get_tuple() const noexcept
  { return get<1>(t); }

  allocator_type
  get_allocator() const
  { return allocator_type(allocator_()); }

  explicit operator bool () const noexcept
  { return pointer_(); }

  void swap(temporary_raw_storage_with_allocator & other)
  noexcept(_aux::is_nothrow_swap<internal_allocator>())
  {
    using std::swap;
    swap(get<1>(t), get<1>(other.t));
    swap(get<0>(t), get<0>(other.t));
    swap(get<2>(t), get<2>(other.t));
  }

private:
  typedef parameter_pack<Elements...> elements;
  typedef build_parameter_index_t<sizeof...(Elements)> indexes;
  typedef typename optimal_index_pack<elements>::type optimal_indexes;
  typedef std::is_same<indexes, optimal_indexes> same;

  optimal_tuple<
      size_type,
      tuple_type,
      internal_allocator
  > t;

  size_type size_() const noexcept
	{ return get<0>(t); }

  char * pointer_() const noexcept
  { return reinterpret_cast<char*>(std::get<index_element<0, optimal_indexes>::value>(get<1>(t))); }

  internal_allocator & allocator_() noexcept
  { return get<2>(t); }

  template <std::size_t... Indexes, std::size_t... OptiIndexes>
  void init_(
    parameter_index<Indexes...>, parameter_index<OptiIndexes...>,
    _aux::usingsize__t<Elements>... sizes)
  noexcept(temporary_raw_storage_with_allocator::is_noexcept())
  {
    const char * p1 = 0;
    const char * p2 = 0;
    std::array<std::size_t, sizeof...(Indexes)> szs;

    FALCON_UNPACK((
      p2 = reinterpret_cast<char*>(reinterpret_cast<size_t>(p1 + (
        std::alignment_of<typename parameter_element<OptiIndexes, elements>::type>::value - 1)
      ) & -std::alignment_of<typename parameter_element<OptiIndexes, elements>::type>::value),
      szs[OptiIndexes] = std::size_t(p1 - static_cast<char*>(0)),
      p1 = p2,
      p1 += sizeof(typename parameter_element<OptiIndexes, elements>::type)
      * ::falcon::arg<OptiIndexes>(size_t(sizes)...)
    ));

    get<0>(t) = size_type(p1 - static_cast<char*>(0));
    void * const p = allocator_traits::allocate(allocator_(), get<0>(t));
    if (!is_noexcept() && !p) {
      get<0>(t) = 0;
      get<1>(t) = std::tuple<Elements*...>{static_cast<Elements*>(nullptr)...};
      return ;
    }
    get<1>(t) = std::tuple<Elements*...>{
      reinterpret_cast<Elements*>(static_cast<char*>(p) + szs[Indexes])...
    };
  }
};


/**
 * Allocates storage containing \a Elements types
 */
template<class... Elements>
using temporary_raw_storage = temporary_raw_storage_with_allocator<std::allocator<char>, Elements...>;


template<typename... Elements, typename Allocator>
temporary_raw_storage_with_allocator<Allocator, Elements...>
make_temporary_raw_storage(const Allocator & alloc, _aux::usingsize__t<Elements>... sizes)
{ return temporary_raw_storage_with_allocator<Allocator, Elements...>(alloc, sizes...); }

template<typename... Elements>
temporary_raw_storage<Elements...>
make_temporary_raw_storage(_aux::usingsize__t<Elements>... sizes)
{ return temporary_raw_storage<Elements...>(sizes...); }


template<class T>
struct raw_element
{ size_t n; };

namespace _aux {
  template<class T>
  struct is_raw_element
  : std::false_type
  {};

  template<class T>
  struct is_raw_element<raw_element<T>>
  : std::true_type
  {};
}

template<typename... Elements, typename Allocator>
typename std::enable_if<
  !_aux::is_raw_element<Allocator>::value,
  temporary_raw_storage_with_allocator<Allocator, Elements...>>::type
make_temporary_raw_storage(const Allocator & alloc, raw_element<Elements>... e)
{ return temporary_raw_storage_with_allocator<Allocator, Elements...>(alloc, e.n...); }

template <typename... Elements>
temporary_raw_storage<Elements...>
make_temporary_raw_storage(raw_element<Elements>... e)
{ return temporary_raw_storage<Elements...>(e.n...); }


template<typename... Elements, typename Allocator>
void swap(
  temporary_raw_storage_with_allocator<Allocator, Elements...> & a,
  temporary_raw_storage_with_allocator<Allocator, Elements...> & b
) noexcept(noexcept(a.swap(b)))
{ a.swap(b); }

}

#endif
