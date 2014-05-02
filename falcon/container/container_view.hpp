#ifndef FALCON_CONTAINER_CONTAINER_VIEW
#define FALCON_CONTAINER_CONTAINER_VIEW

#include <falcon/type_traits/enable_if_not_integral.hpp>
#include <falcon/container/range_access_traits.hpp>
#include <falcon/type_traits/rebind.hpp>
#include <falcon/utility/move.hpp>
#include <iterator>


namespace falcon{

/**
 * @ingroup sequences
 */
template<class Container, class Access = range_access_traits<Container> >
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
  : container_()
  , access_()
  {}

#if __cplusplus >= 201103L
  explicit container_view(std::nullptr_t)
  : container_(0)
  , access_()
  {}
#endif

  explicit container_view(access_type traits)
  : container_(0)
  , access_(FALCON_MOVE(traits))
  {}

  explicit container_view(container_type& container)
  : container_(&container)
  , access_()
  {}

  container_view(container_type& container, access_type traits)
  : container_(&container)
  , access_(FALCON_MOVE(traits))
  {}

#if __cplusplus >= 201103L
  template<typename... Args>
  container_view(container_type& container, Args&&... argtraits)
  : container_(&container)
  , access_(std::forward<Args>(argtraits)...)
  {}
#endif

  container_view(const container_view& other)
  : container_(other.container_)
  , access_(other.access_)
  {}

  bool valid()
  { return container_ != nullptr; }

  container_view& operator=(container_view& other)
  {
        container_ = other.container_;
        access_ = other.access_;
    return *this;
  }

  container_view& operator=(container_type& other)
  {
        container_ = &other;
    return *this;
  }

  iterator begin() const
  { return access_.begin(base()); }

  iterator end() const
  { return access_.end(base()); }

  value_type& operator[](difference_type n) const
  { return *(begin() + n); }

  void swap(container_view& other)
  {
    using std::swap;
    swap(access_, other.access_);
    swap(container_, other.container_);
  }

  template<class Access2>
  void swap_container(container_view<Container, Access2>& other)
  {
    using std::swap;
    swap(container_, other._container);
  }

  operator container_type&() const
  { return base(); }

  container_type& base() const
  { return *container_; }

  container_type& access()
  { return access_; }

  const container_type& access() const
  { return access_; }


private:
  container_type* container_;
  access_type access_;
};


template<class Container, typename Iterator>
struct build_container_view
{
  typedef container_view<
    Container
  , range_access_to_iterator_traits<
      Container
    , range_access_traits<Container>, Iterator>
  > type;
};

template<class Container, typename Iterator>
struct build_reverse_container_view
{
  typedef container_view<
    Container
  , range_access_to_iterator_traits<
      Container
    , reverse_range_access_traits<Container>, Iterator>
  > type;
};

#if __cplusplus >= 201103L
template<class Container,
  class Access = reverse_range_access_traits<const Container> >
using const_container_view = container_view<const Container, Access>;

template<class Container,
  class Access = reverse_range_access_traits<Container> >
using reverse_container_view = container_view<Container, Access>;

template<class Container,
  class Access = reverse_range_access_traits<const Container> >
using const_reverse_container_view = container_view<const Container, Access>;
#endif


template<class Container>
container_view<Container>
seq(Container& cont)
{ return container_view<Container>(cont); }

template<class Container, class Access>
typename enable_if_not_integral<Access, container_view<Container, Access> >::type
seq(Container& cont, Access access)
{ return container_view<Container, Access>(cont, access); }

template<class Container>
container_view<Container, reverse_range_access_traits<Container> >
rseq(Container& cont)
{ return container_view<Container, reverse_range_access_traits<Container> >(cont); }

template<class Container>
container_view<const Container>
cseq(const Container& cont)
{ return container_view<const Container>(cont); }

template<class Container, class Access>
container_view<const Container, Access>
cseq(const Container& cont, Access access)
{ return container_view<const Container, Access>(cont, access); }

template<class Container>
container_view<const Container, reverse_range_access_traits<const Container> >
crseq(const Container& cont)
{ return container_view<const Container, reverse_range_access_traits<const Container> >(cont); }

template<class Container, class Access>
void swap(container_view<Container, Access>& a,
          container_view<Container, Access>& b)
{ a.swap(b); }

}

#endif
