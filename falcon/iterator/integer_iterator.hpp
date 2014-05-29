#ifndef FALCON_ITERATOR_INTEGER_ITERATOR_HPP
#define FALCON_ITERATOR_INTEGER_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {

struct integer_iterator_full_comparison_tag {};
struct integer_iterator_less_comparison_tag {};
struct integer_iterator_equal_to_comparison_tag {};

template <
  class T
, class ComparisonTag = use_default
, class Category = use_default
>
class integer_iterator;

template <
  class T
, class ComparisonTag = use_default
, class Category = use_default
>
class reverse_integer_iterator;


namespace detail {

  template <
    template<class,class,class> class IntegerIterator
  , class T
  , class ComparisonTag
  , class Category
  >
  struct integer_iterator_base_impl
  {
    typedef typename iterator_handler_types<
      IntegerIterator<T, ComparisonTag, Category>
    , T
    , class default_or_type<
        use<std::random_access_iterator_tag /*TODO not always*/>
      , Category
      >::type
    , T
    , typename difference<T>::type
    , T*
    , T&
    >::type type;
  };

  template <class T, class ComparisonTag, class Category>
  struct integer_iterator_base
  {
    typedef typename integer_iterator_base_impl<
      integer_iterator, T, ComparisonTag, Category>::type type;
  };

  template <class T, class ComparisonTag, class Category>
  struct reverse_integer_iterator_base
  {
    typedef typename integer_iterator_base_impl<
      reverse_integer_iterator, T, ComparisonTag, Category>::type type;
  };

}


template<class T, class ComparisonTag, class Category>
class integer_iterator
: public detail::integer_iterator_base<T, ComparisonTag, Category>::type
{
  typedef typename integer_iterator::handler_type inherit_type;

  friend class iterator_core_access;

public:
  typedef typename inherit_type::reference reference;

public:
  integer_iterator()
  {}

  integer_iterator(const T& value)
  : inherit_type(value, 1)
  {}

#if __cplusplus >= 201103L
  integer_iterator(T&& value)
  : inherit_type(std::forward<T>(value), 1)
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  integer_iterator(U&& value)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  {}
#endif

  using inherit_type::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }

  typedef typename default_or_type<
    use<integer_iterator_full_comparison_tag>
  , ComparisonTag
  >::type comparison_tag;

  bool equal(const integer_iterator& other,
             integer_iterator_less_comparison_tag) const
  { return other.base_reference() < this->base_reference(); }

  template<class Tag>
  bool equal(const integer_iterator& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const integer_iterator& other) const
  { return equal(other, comparison_tag()); }

  bool less(const integer_iterator& other,
            integer_iterator_equal_to_comparison_tag) const;

  template<class Tag>
  bool less(const integer_iterator& other, Tag) const
  { return this->base_reference() < other.base_reference(); }

  bool less(const integer_iterator& other) const
  { return less(other, comparison_tag()); }
};


template <class T>
integer_iterator<T>
make_integer_iterator(const T& value)
{ return integer_iterator<T>(value); }

template <class T, class ComparisonTag>
integer_iterator<T, ComparisonTag>
make_integer_iterator(const T& value, ComparisonTag)
{ return integer_iterator<T, ComparisonTag>(value); }

template <class T>
integer_iterator<const T>
make_cinteger_iterator(const T& value)
{ return integer_iterator<const T>(value); }

template <class T, class ComparisonTag>
integer_iterator<const T, ComparisonTag>
make_cinteger_iterator(const T& value, ComparisonTag)
{ return integer_iterator<const T, ComparisonTag>(value); }


template<class T, class ComparisonTag, class Category>
class reverse_integer_iterator
: public detail::reverse_integer_iterator_base<T, ComparisonTag, Category>::type
{
  typedef typename reverse_integer_iterator::handler_type inherit_type;

  friend class iterator_core_access;

public:
  typedef typename inherit_type::reference reference;
  typedef typename inherit_type::difference_type difference_type;

public:
  reverse_integer_iterator()
  {}

  reverse_integer_iterator(const T& value)
  : inherit_type(value, 1)
  {}

#if __cplusplus >= 201103L
  reverse_integer_iterator(T&& value)
  : inherit_type(std::forward<T>(value))
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  reverse_integer_iterator(U&& value)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  {}
#endif

  using inherit_type::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }

  void increment()
  { --this->base_reference(); }

  void decrement()
  { ++this->base_reference(); }

  void advance(difference_type n)
  { this->base_reference() -= n; }

  difference_type difference(const reverse_integer_iterator& other) const
  { return other.base_reference() - this->base_reference(); }

  typedef typename default_or_type<
    use<integer_iterator_full_comparison_tag>,
    ComparisonTag
  >::type comparison_tag;

  bool equal(const reverse_integer_iterator& other,
             integer_iterator_less_comparison_tag) const
  { return this->base_reference() < other.base_reference(); }

  template<class Tag>
  bool equal(const reverse_integer_iterator& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const reverse_integer_iterator& other) const
  { return equal(other, comparison_tag()); }

  bool less(const reverse_integer_iterator& other,
            integer_iterator_equal_to_comparison_tag) const;

  template<class Tag>
  bool less(const reverse_integer_iterator& other, Tag) const
  { return other.base_reference() < this->base_reference(); }

  bool less(const reverse_integer_iterator& other) const
  { return less(other, comparison_tag()); }
};


template <class T>
reverse_integer_iterator<T>
make_reverse_integer_iterator(const T& value)
{ return reverse_integer_iterator<T>(value); }

template <class T, class ComparisonTag>
reverse_integer_iterator<T, ComparisonTag>
make_reverse_integer_iterator(const T& value, ComparisonTag)
{ return reverse_integer_iterator<T, ComparisonTag>(value); }

template <class T>
reverse_integer_iterator<const T>
make_creverse_integer_iterator(const T& value)
{ return reverse_integer_iterator<const T>(value); }

template <class T, class ComparisonTag>
reverse_integer_iterator<const T, ComparisonTag>
make_creverse_integer_iterator(const T& value, ComparisonTag)
{ return reverse_integer_iterator<const T, ComparisonTag>(value); }


template <class T, class ComparisonTag = use_default, class Category = use_default>
class integer_iterator_with_step
: public detail::integer_iterator_base_impl<
  integer_iterator_with_step
, T, ComparisonTag, Category>::type
{
  typedef typename integer_iterator_with_step::handler_type inherit_type;

  friend class iterator_core_access;

public:
  typedef typename inherit_type::reference reference;
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;

public:
  integer_iterator_with_step()
  : step_(1)
  {}

  integer_iterator_with_step(const iterator_type& other)
  : inherit_type(other)
  , step_(1)
  {}

  integer_iterator_with_step(const iterator_type& other, difference_type step)
  : inherit_type(other)
  , step_(other.step_)
  {}

  integer_iterator_with_step(const integer_iterator_with_step& other,
                             difference_type step)
  : inherit_type(other)
  , step_(other.step_)
  {}

#if __cplusplus >= 201103L
  integer_iterator_with_step(T&& value)
  : inherit_type(std::piecewise_construct, std::forward<T>(value))
  , step_(1)
  {}

  integer_iterator_with_step(T&& value, difference_type step)
  : inherit_type(std::piecewise_construct, std::forward<T>(value))
  , step_(step)
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  integer_iterator_with_step(U&& value)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  , step_(1)
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  integer_iterator_with_step(U&& value, difference_type step)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  , step_(step)
  {}
#endif

  using inherit_type::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }

  typedef typename default_or_type<
    use<integer_iterator_full_comparison_tag>,
    ComparisonTag
  >::type comparison_tag;

  bool equal(const integer_iterator_with_step& other,
             integer_iterator_less_comparison_tag) const
  { return other.base_reference() < this->base_reference(); }

  template<class Tag>
  bool equal(const integer_iterator_with_step& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const integer_iterator_with_step& other) const
  { return equal(other, comparison_tag()); }

  bool less(const integer_iterator_with_step& other,
            integer_iterator_equal_to_comparison_tag) const;

  template<class Tag>
  bool less(const integer_iterator_with_step& other, Tag) const
  { return this->base_reference() < other.base_reference(); }

  bool less(const integer_iterator_with_step& other) const
  { return less(other, comparison_tag()); }

  void increment()
  { this->base_reference() += step_; }

  void decrement()
  { this->base_reference() -= step_; }

  void advance(difference_type n)
  { this->base_reference() += n * step_; }

  difference_type step_;
};

template <class T, class ComparisonTag = use_default, class Category = use_default>
class reverse_integer_iterator_with_step
: public detail::integer_iterator_base_impl<
  reverse_integer_iterator_with_step
, integer_iterator<T, ComparisonTag, Category>
, ComparisonTag, Category>::type
{
  typedef typename reverse_integer_iterator_with_step::handler_type inherit_type;

  friend class iterator_core_access;

public:
  typedef typename inherit_type::reference reference;
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;

public:
  reverse_integer_iterator_with_step()
  : step_(1)
  {}

  reverse_integer_iterator_with_step(const iterator_type& other)
  : inherit_type(other)
  , step_(1)
  {}

  reverse_integer_iterator_with_step(const iterator_type& other, difference_type step)
  : inherit_type(other)
  , step_(step)
  {}

  reverse_integer_iterator_with_step(const reverse_integer_iterator_with_step& other,
                                     difference_type step)
  : inherit_type(other)
  , step_(step)
  {}

  reverse_integer_iterator_with_step(const T& value)
  : inherit_type(iterator_type(value), 1)
  , step_(1)
  {}

  reverse_integer_iterator_with_step(const T& value, difference_type step)
  : inherit_type(iterator_type(value), 1)
  , step_(step)
  {}

#if __cplusplus >= 201103L
  reverse_integer_iterator_with_step(T&& value)
  : inherit_type(std::piecewise_construct, std::forward<T>(value))
  , step_(1)
  {}

  reverse_integer_iterator_with_step(T&& value, difference_type step)
  : inherit_type(std::piecewise_construct, std::forward<T>(value))
  , step_(step)
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  reverse_integer_iterator_with_step(U&& value)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  , step_(1)
  {}

  template<class U, class Enable = typename std::enable_if<
    !std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  reverse_integer_iterator_with_step(U&& value, difference_type step)
  : inherit_type(std::piecewise_construct, std::forward<U>(value))
  , step_(step)
  {}
#endif

  using inherit_type::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }

  void increment()
  { this->base_reference() -= step_; }

  void decrement()
  { this->base_reference() += step_; }

  void advance(difference_type n)
  { this->base_reference() -= n * step_; }

  difference_type difference(const reverse_integer_iterator_with_step& other) const
  { return other.base_reference() - this->base_reference(); }

  typedef typename default_or_type<
    use<integer_iterator_full_comparison_tag>,
    ComparisonTag
  >::type comparison_tag;

  bool equal(const reverse_integer_iterator_with_step& other,
             integer_iterator_less_comparison_tag) const
  { return this->base_reference() < other.base_reference(); }

  template<class Tag>
  bool equal(const reverse_integer_iterator_with_step& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const reverse_integer_iterator_with_step& other) const
  { return equal(other, comparison_tag()); }

  bool less(const reverse_integer_iterator_with_step& other,
            integer_iterator_equal_to_comparison_tag) const;

  template<class Tag>
  bool less(const reverse_integer_iterator_with_step& other, Tag) const
  { return other.base_reference() < this->base_reference(); }

  bool less(const reverse_integer_iterator_with_step& other) const
  { return less(other, comparison_tag()); }

  difference_type step_;
};

template <class T>
reverse_integer_iterator_with_step<T>
make_reverse_integer_iterator_with_step(
  const T& value
, typename reverse_integer_iterator_with_step<T>::difference_type step)
{ return reverse_integer_iterator_with_step<T>(value, step); }

template <class T, class ComparisonTag>
reverse_integer_iterator_with_step<T, ComparisonTag>
make_reverse_integer_iterator_with_step(
  const T& value
, typename reverse_integer_iterator_with_step<T>::difference_type step
, ComparisonTag)
{ return reverse_integer_iterator_with_step<T, ComparisonTag>(value, step); }

template <class T>
reverse_integer_iterator_with_step<const T>
make_creverse_integer_iterator_with_step(
  const T& value
, typename reverse_integer_iterator_with_step<T>::difference_type step)
{ return reverse_integer_iterator_with_step<const T>(value, step); }

template <class T, class ComparisonTag>
reverse_integer_iterator_with_step<const T, ComparisonTag>
make_creverse_integer_iterator_with_step(
  const T& value
, typename reverse_integer_iterator_with_step<T>::difference_type step
, ComparisonTag)
{ return reverse_integer_iterator_with_step<const T, ComparisonTag>(value, step); }

}}

#endif
