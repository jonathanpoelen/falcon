#ifndef FALCON_ITERATOR_INTEGRAL_ITERATOR_HPP
#define FALCON_ITERATOR_INTEGRAL_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {

template <class T>
class integral_iterator;

namespace detail
{
  template <class T>
  struct integral_iterator_base
  {
    typedef typename iterator_handler_types<
      integral_iterator<T>
    , T
    , std::random_access_iterator_tag
    , T
    , typename difference<T>::type
    , T*
    , T&
    >::type type;
  };
}

template<class T>
class integral_iterator
: public detail::integral_iterator_base<T>::type
{
  typedef typename integral_iterator::handler_type inherit_type;

  friend class iterator_core_access;

public:
  typedef typename inherit_type::reference reference;

public:
  integral_iterator()
  {}

  integral_iterator(const T& value)
  : inherit_type(value, 1)
  {}

#if __cplusplus >= 201103L
  integral_iterator(T&& value)
  : inherit_type(std::forward<T>(value), 1)
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  integral_iterator(U&& value)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  {}
#endif

  using inherit_type::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }
};


template <class T>
integral_iterator<T>
make_integral_iterator(const T& value)
{ return integral_iterator<T>(value); }

template <class T>
integral_iterator<const T>
make_cintegral_iterator(const T& value)
{ return integral_iterator<const T>(value); }


typedef integral_iterator<int>           int_iterator;
typedef integral_iterator<unsigned int>  uint_iterator;
typedef integral_iterator<long>          long_iterator;
typedef integral_iterator<unsigned long> ulong_iterator;
#if __cplusplus >= 201103L
typedef integral_iterator<long long>          long_long_iterator;
typedef integral_iterator<unsigned long long> ulong_long_iterator;
#endif

} }

#endif
