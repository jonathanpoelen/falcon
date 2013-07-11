#ifndef _FALCON_CONTAINER_CONTAINER_WRAPPER
#define _FALCON_CONTAINER_CONTAINER_WRAPPER

#include <falcon/container/range_access_traits.hpp>
#include <iterator>


namespace falcon{

/**
 * @ingroup sequences
 */
template<typename Container, typename Access = range_access_traits<Container> >
class container_wrapper
{
public:
  typedef Container container_type;
  typedef Access access_type;
  typedef typename Access::iterator iterator;

private:
  typedef std::iterator_traits<iterator> __type_traits;

public:
  typedef typename __type_traits::value_type value_type;
  typedef typename __type_traits::pointer pointer;
  typedef typename __type_traits::reference reference;
  typedef typename __type_traits::difference_type difference_type;


public:
#if __cplusplus >= 201103L
  explicit container_wrapper(std::nullptr_t)
  : _container(0)
  , _access()
  {}

  bool valid()
  { return _container != nullptr; }
#endif

  explicit container_wrapper(const access_type& traits)
  : _container(0)
  , _access(traits)
  {}

  explicit container_wrapper(container_type& container)
  : _container(&container)
  , _access()
  {}

  container_wrapper(container_type& container, const access_type& traits)
  : _container(&container)
  , _access(traits)
  {}

#if __cplusplus >= 201103L
  template<typename... Args>
  container_wrapper(container_type& container, Args&&... argtraits)
  : _container(&container)
  , _access(std::forward<Args>(argtraits)...)
  {}
#endif

  container_wrapper(const container_wrapper& other)
  : _container(other._container)
  , _access(other._access)
  {}

  container_wrapper& operator=(container_wrapper& other)
  {
    _container = other._container;
    _access = other._access;
    return *this;
  }

  container_wrapper& operator=(container_type& other)
  {
    _container = &other;
    return *this;
  }

  iterator begin() const
  { return _access.begin(base()); }

  iterator end() const
  { return _access.end(base()); }

  value_type& operator[](difference_type n)
  { return *(begin() + n); }

  void swap(container_wrapper& other)
  {
    using std::swap;
    swap(_access, other._access);
    swap(_container, other._container);
  }

  template<typename Access2>
  void swap_container(container_wrapper<Container, Access2>& other)
  {
    using std::swap;
    swap(_access, other._access);
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
  Access _access;
};


template<typename Container, typename _Iterator>
struct build_container_wrapper
{
  typedef container_wrapper<
    Container,
    range_access_traits<Container, _Iterator>
  > type;
};

template<typename Container, typename _Iterator>
struct build_reverse_container_wrapper
{
  typedef container_wrapper<
    Container,
    reverse_range_access_traits<Container, _Iterator>
  > type;
};

#if __cplusplus >= 201103L
template<typename Container,
  typename Access = reverse_range_access_traits<Container> >
using reverse_container_wrapper = container_wrapper<Container, Access>;
#endif


template<typename Container>
container_wrapper<Container>
seq(Container& cont)
{ return container_wrapper<Container>(cont); }

template<typename Container, typename Access>
container_wrapper<Container, Access>
seq(Container& cont, const Access& access)
{ return container_wrapper<Container, Access>(cont, access); }

template<typename Container>
container_wrapper<Container, reverse_range_access_traits<Container> >
rseq(Container& cont)
{ return container_wrapper<Container, reverse_range_access_traits<Container> >(cont); }

template<typename Container>
container_wrapper<const Container>
cseq(const Container& cont)
{ return container_wrapper<const Container>(cont); }

template<typename Container>
container_wrapper<const Container, reverse_range_access_traits<const Container> >
crseq(const Container& cont)
{ return container_wrapper<const Container, reverse_range_access_traits<const Container> >(cont); }

template<typename Container, typename Access>
void swap(container_wrapper<Container, Access>& a,
          container_wrapper<Container, Access>& b)
{ a.swap(b); }

}

#endif
