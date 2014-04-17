#ifndef FALCON_CONTAINER_CONTAINER_VIEW
#define FALCON_CONTAINER_CONTAINER_VIEW

#include <falcon/container/range_access_traits.hpp>
#include <falcon/type_traits/rebind.hpp>
#include <falcon/utility/move.hpp>
#include <iterator>


namespace falcon{

/**
 * @ingroup sequences
 */
template<typename Container, typename Access = range_access_traits<Container> >
class container_view
{
public:
  typedef Container container_type;
  typedef typename rebind<Access, Container>::type access_type;
  typedef typename Access::iterator iterator;

private:
  typedef std::iterator_traits<iterator> iterator_traits;

public:
  typedef typename iterator_traits::value_type value_type;
  typedef typename iterator_traits::pointer pointer;
  typedef typename iterator_traits::reference reference;
  typedef typename iterator_traits::difference_type difference_type;


public:
  explicit container_view()
  : _container()
  , _access()
  {}

#if __cplusplus >= 201103L
  explicit container_view(std::nullptr_t)
  : _container(0)
  , _access()
  {}
#endif

  explicit container_view(access_type traits)
  : _container(0)
  , _access(FALCON_MOVE(traits))
  {}

  explicit container_view(container_type& container)
  : _container(&container)
  , _access()
  {}

  container_view(container_type& container, access_type traits)
  : _container(&container)
  , _access(FALCON_MOVE(traits))
  {}

#if __cplusplus >= 201103L
  template<typename... Args>
  container_view(container_type& container, Args&&... argtraits)
  : _container(&container)
  , _access(std::forward<Args>(argtraits)...)
  {}
#endif

  container_view(const container_view& other)
  : _container(other._container)
  , _access(other._access)
  {}

  bool valid()
  { return _container != nullptr; }

  container_view& operator=(container_view& other)
  {
    _container = other._container;
    _access = other._access;
    return *this;
  }

  container_view& operator=(container_type& other)
  {
    _container = &other;
    return *this;
  }

  iterator begin() const
  { return _access.begin(base()); }

  iterator end() const
  { return _access.end(base()); }

  value_type& operator[](difference_type n) const
  { return *(begin() + n); }

  void swap(container_view& other)
  {
    using std::swap;
    swap(_access, other._access);
    swap(_container, other._container);
  }

  template<typename Access2>
  void swap_container(container_view<Container, Access2>& other)
  {
    using std::swap;
    swap(_container, other._container);
  }

  operator container_type&() const
  { return base(); }

  container_type& base() const
  { return *_container; }

  container_type& access()
  { return _access; }

  const container_type& access() const
  { return _access; }


private:
  container_type* _container;
  access_type _access;
};


template<typename Container, typename Iterator>
struct build_container_view
{
  typedef container_view<
    Container
  , range_access_to_iterator_traits<range_access_traits<Container>, Iterator>
  > type;
};

template<typename Container, typename Iterator>
struct build_reverse_container_view
{
  typedef container_view<
    Container
  , range_access_to_iterator_traits<reverse_range_access_traits<Container>, Iterator>
  > type;
};

#if __cplusplus >= 201103L
template<typename Container,
  typename Access = reverse_range_access_traits<Container> >
using reverse_container_view = container_view<Container, Access>;
#endif


template<typename Container>
container_view<Container>
seq(Container& cont)
{ return container_view<Container>(cont); }

template<typename Container, typename Access>
container_view<Container, Access>
seq(Container& cont, Access access)
{ return container_view<Container, Access>(cont, access); }

template<typename Container>
container_view<Container, reverse_range_access_traits<Container> >
rseq(Container& cont)
{ return container_view<Container, reverse_range_access_traits<Container> >(cont); }

template<typename Container>
container_view<const Container>
cseq(const Container& cont)
{ return container_view<const Container>(cont); }

template<typename Container, typename Access>
container_view<const Container, Access>
cseq(const Container& cont, Access access)
{ return container_view<const Container, Access>(cont, access); }

template<typename Container>
container_view<const Container, reverse_range_access_traits<const Container> >
crseq(const Container& cont)
{ return container_view<const Container, reverse_range_access_traits<const Container> >(cont); }

template<typename Container, typename Access>
void swap(container_view<Container, Access>& a,
          container_view<Container, Access>& b)
{ a.swap(b); }

}

#endif
