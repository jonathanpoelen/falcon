#ifndef FALCON_ITERATOR_NORMAL_ITERATOR_HPP
#define FALCON_ITERATOR_NORMAL_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename Iterator,
    typename Tp = use_default, typename Category = use_default,
    typename Reference = use_default, typename Distance = use_default,
    typename Pointer = use_default
>
class normal_iterator;

namespace detail {

    template <typename Iterator, typename Tp, typename Category,
      typename Reference, typename Distance, typename Pointer>
    struct normal_base
    {
        typedef typename iterator_handler_types<
            normal_iterator<Iterator, Tp, Category, Reference, Distance, Pointer>,
            Iterator,
            Category,
            Tp,
            Distance,
            Pointer,
            Reference
        >::base base;
    };

}

template <typename Iterator,
    typename Tp,
    typename Category,
    typename Reference,
    typename Distance,
    typename Pointer
>
class normal_iterator
: public detail::normal_base<Iterator, Tp, Category, Reference, Distance, Pointer>::base
{
  friend class iterator_core_access;

  typedef detail::normal_base<Iterator, Tp, Category, Reference, Distance, Pointer> __detail;
  typedef typename __detail::base __base;

public:
  typedef typename __base::iterator_type iterator_type;
  typedef typename __base::difference_type difference_type;
  typedef typename __base::reference reference;

public:
  normal_iterator()
  : __base()
  {}

  explicit normal_iterator(iterator_type __x)
  : __base(__x)
  {}

  normal_iterator(const normal_iterator& __x)
  : __base(__x)
  {}

  using __base::operator=;
#if __cplusplus >= 201103L
  normal_iterator& operator=(const normal_iterator&) = default;
#else
  normal_iterator& operator=(const normal_iterator& other)
  {
    __base::operator=(other);
    return *this;
  }
#endif
};

template <typename Iterator>
normal_iterator<Iterator>
make_normal_iterator(Iterator x)
{ return normal_iterator<Iterator>(x); }

}}

#endif
