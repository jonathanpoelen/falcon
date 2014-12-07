#ifndef FALCON_CONTAINER_CONTAINER_VIEW
#define FALCON_CONTAINER_CONTAINER_VIEW

#include <falcon/type_traits/enable_if_not_integral.hpp>
#include <falcon/container/range_access_traits.hpp>
#include <falcon/type_traits/rebind.hpp>
#include <falcon/utility/move.hpp>

#include <iterator>
#include <tuple>


namespace falcon {

/**
 * @ingroup sequences
 */
template<class Container, class RangeAccess = range_access_traits >
class container_view
{
public:
  typedef Container container_type;
  typedef RangeAccess access_type;
  using iterator = range_access_to_iterator<RangeAccess, Container>;

private:
  typedef std::iterator_traits<iterator> iterator_traits;

public:
  typedef typename iterator_traits::value_type value_type;
  typedef typename iterator_traits::pointer pointer;
  typedef typename iterator_traits::reference reference;
  typedef typename iterator_traits::difference_type difference_type;


public:
  container_view() = default;
  container_view(const container_view& other) = default;
  container_view(container_view&& other) = default;

  explicit container_view(access_type traits)
  : t(nullptr, std::move(traits))
  {}

  explicit container_view(container_type& container)
  {
    std::get<0>(t) = &container;
  }

  container_view(container_type& container, access_type traits)
  : t(&container, std::move(traits))
  {}

  template<typename... Args>
  explicit container_view(container_type& container, Args&&... access_args)
  : t(&container, access_type(std::forward<Args>(access_args)...))
  {}

  container_view& operator=(const container_view& other) = default;
  container_view& operator=(container_view&& other) = default;

  container_view& operator=(container_type& other)
  {
    std::get<0>(t) = &other;
    return *this;
  }

  explicit operator bool () const noexcept
  { return std::get<0>(t); }

  iterator begin() const
  { return std::get<1>(t).begin(base()); }

  iterator end() const
  { return std::get<1>(t).end(base()); }

  value_type& operator[](difference_type n) const
  { return std::get<0>(t)[n]; }

  void swap(container_view& other)
  {
    using std::swap;
    swap(t, other.t);
  }

  container_type& base() const
  { return *std::get<0>(t); }

  container_type& get_access()
  { return std::get<1>(t); }

  const container_type& get_access() const
  { return std::get<1>(t); }

private:
  std::tuple<container_type*, access_type> t;
};


template<class Container>
using const_container_view
= container_view<const Container, range_access_traits>;

template<class Container>
using reverse_container_view
= container_view<Container, reverse_range_access_traits>;

template<class Container>
using const_reverse_container_view = reverse_container_view<const Container>;


template<class Container, typename Iterator>
using iterator_container_view = container_view<
  Container
, iterator_range_access_traits<Iterator, range_access_traits>
>;

template<class Container, typename Iterator>
using reverse_iterator_container_view = container_view<
  Container
, iterator_range_access_traits<Iterator, reverse_range_access_traits>
>;

template<class Container, typename Iterator>
using iterator_const_container_view
  = iterator_container_view<const Container, Iterator>;

template<class Container, typename Iterator>
using reverse_iterator_const_container_view
  = reverse_iterator_container_view<const Container, Iterator>;


template<class Container>
container_view<Container>
seq(Container& cont)
{ return container_view<Container>(cont); }

template<class Container, class RangeAccess>
typename enable_if_not_integral<
  RangeAccess, container_view<Container, RangeAccess> >::type
seq(Container& cont, RangeAccess access)
{ return container_view<Container, RangeAccess>(cont, access); }


template<class Container>
reverse_container_view<Container>
rseq(Container& cont)
{ return reverse_container_view<Container>(cont); }


template<class Container>
container_view<const Container>
cseq(const Container& cont)
{ return container_view<const Container>(cont); }

template<class Container, class RangeAccess>
container_view<const Container, RangeAccess>
cseq(const Container& cont, RangeAccess access)
{ return container_view<const Container, RangeAccess>(cont, access); }


template<class Container>
reverse_container_view<const Container>
crseq(const Container& cont)
{ return reverse_container_view<const Container>(cont); }


template<class Container, class RangeAccess>
void swap(
  container_view<Container, RangeAccess>& a
, container_view<Container, RangeAccess>& b)
{ a.swap(b); }

}

#endif
