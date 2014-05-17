#ifndef FALCON_ITERATOR_PROXY_ITERATOR_HPP
#define FALCON_ITERATOR_PROXY_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/utility/move.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <boost/type_traits/remove_pointer.hpp>
#endif

namespace falcon {
namespace iterator {

template <
  class Iterator
, class Proxy = use_default
, class T = use_default
, class Reference = use_default
>
class indirect_iterator;

namespace detail {
  template <class Iterator>
  struct proxy_indirect_iterator
  {
    typedef typename std::iterator_traits<Iterator>::value_type argument_type;
#if __cplusplus >= 201103L
    typedef decltype(**std::declval<Iterator&>()) result_type;
#else
    typedef typename boost::remove_pointer<argument_type>::type& result_type;
#endif

    result_type operator()(argument_type& x) const
    { return *x; }
  };

  template <class Iterator, class Proxy, class T, class Reference>
  struct indirect_iterator_base
  {
    typedef typename default_or_type<
      use<proxy_indirect_iterator<Iterator> >,
      Proxy
    >::type proxy;

#if __cplusplus >= 201103L
    struct result_type_t {
      typedef typename std::result_of<
        proxy(decltype(*std::declval<Iterator&>()))
      >::type type;
    };
    typedef typename default_or_type<result_type_t, Reference>::type reference;
    typedef typename default_or_type<std::remove_reference<reference>, T>::type value_type;
#else
    typedef typename default_or_type<use_result_type<proxy>, T>::type value_type;
    typedef typename default_or_type<use<value_type&>, Reference>::type reference;
#endif

    typedef typename iterator_handler_types<
      indirect_iterator<Iterator, Proxy, T, Reference>
    , Iterator
    , use_default
    , value_type
    , use_default
    , use_default
    , reference
    >::type type;
  };

}

template <class Iterator, class Proxy, class T, class Reference>
class indirect_iterator
: public detail::indirect_iterator_base<Iterator, Proxy, T, Reference>::type
{
  friend class iterator_core_access;

  typedef detail::indirect_iterator_base<Iterator, Proxy, T, Reference> detail_type;
  typedef typename detail_type::type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;
  typedef typename inherit_type::reference reference;

  typedef typename detail_type::proxy  proxy_type;

private:
  proxy_type proxy_;

public:
  indirect_iterator()
  {}

  indirect_iterator(iterator_type x)
  : inherit_type(x)
  {}

  indirect_iterator(iterator_type x, proxy_type proxy__)
  : inherit_type(x)
  , proxy_(proxy__)
  {}

  using inherit_type::operator=;

  Proxy proxy() const
  { return proxy_; }

private:
  reference dereference() const
  { return proxy_(*(this->base_reference())); }

  reference dereference()
  { return proxy_(*(this->base_reference())); }
};

template <class Iterator, class Proxy>
indirect_iterator<Iterator, Proxy>
make_indirect_iterator(Iterator x, Proxy proxy)
{ return indirect_iterator<Iterator, Proxy>(x, proxy); }

template <class Iterator>
indirect_iterator<Iterator>
make_indirect_iterator(Iterator x)
{ return indirect_iterator<Iterator>(x); }

template <class Proxy, class Iterator>
indirect_iterator<Iterator>
make_indirect_iterator(Iterator x)
{ return indirect_iterator<Iterator, Proxy>(x); }

}}

#endif
