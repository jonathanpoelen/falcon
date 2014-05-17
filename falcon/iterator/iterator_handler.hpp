#ifndef ITERATOR_ITERATOR_HANDLER_HPP
#define ITERATOR_ITERATOR_HANDLER_HPP

#include <falcon/c++/boost_or_std.hpp>

#include <falcon/preprocessor/nil.hpp>
#include <falcon/preprocessor/qualifier.hpp>

#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>
#include <falcon/type_traits/is_same.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#include <falcon/helper/restrict_pointer.hpp>
#include <falcon/helper/restrict_reference.hpp>
#include <falcon/helper/restrict_value_type.hpp>
#include <falcon/helper/restrict_difference_type.hpp>
#include <falcon/helper/restrict_iterator_category.hpp>

#include <iterator>
#if __cplusplus >= 201103L
# include <utility>
#else
# include <boost/type_traits/add_pointer.hpp>
#endif

namespace falcon {
namespace iterator {

template<
  typename Iterator
, typename IteratorBase
, typename Category
, typename T
, typename Distance
, typename Pointer
, typename Reference
>
class iterator_handler;

struct iterator_core_access
{
#define FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
  template<class I, class IBase, class C, class V, class D, class P, class R>

#define FALCON_ITERATOR_HANDLER_TYPE()\
  iterator_handler<I, IBase, C, V, D, P, R>

#define FALCON_ITERATOR_CORE_ACCESS_HEAD(prefix, result_type, name, qualifier)\
  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
  prefix result_type name(qualifier() FALCON_ITERATOR_HANDLER_TYPE()& a)

  FALCON_ITERATOR_CORE_ACCESS_HEAD(static, I&, derived, FALCON_PP_NIL)
  { return a.downcast(); }

  FALCON_ITERATOR_CORE_ACCESS_HEAD(static, const I&, derived, FALCON_PP_CONST)
  { return a.downcast(); }

#define FALCON_ITERATOR_CORE_ACCESS(result_type, member, qualifier)\
  FALCON_ITERATOR_CORE_ACCESS_HEAD(static, result_type, member, qualifier)\
  { return derived(a).member(); }

  FALCON_ITERATOR_CORE_ACCESS(IBase&, base_reference, FALCON_PP_NIL)
  FALCON_ITERATOR_CORE_ACCESS(const IBase&, base_reference, FALCON_PP_CONST)

  FALCON_ITERATOR_CORE_ACCESS(typename I::reference, dereference, FALCON_PP_NIL)
  FALCON_ITERATOR_CORE_ACCESS(typename I::reference, dereference, FALCON_PP_CONST)

  FALCON_ITERATOR_CORE_ACCESS(void, increment, FALCON_PP_NIL)
  FALCON_ITERATOR_CORE_ACCESS(void, decrement, FALCON_PP_NIL)

#undef FALCON_ITERATOR_CORE_ACCESS

  FALCON_ITERATOR_CORE_ACCESS_HEAD(friend, I&, operator++, FALCON_PP_NIL)
  {
    increment(a);
    return derived(a);
  }

  FALCON_ITERATOR_CORE_ACCESS_HEAD(friend, I&, operator--, FALCON_PP_NIL)
  {
    decrement(a);
    return derived(a);
  }

#undef FALCON_ITERATOR_CORE_ACCESS_HEAD

  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()
  friend I operator++(FALCON_ITERATOR_HANDLER_TYPE()& a, int)
  {
    I ret(derived(a));
    increment(a);
    return ret;
  }

  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()
  friend I operator--(FALCON_ITERATOR_HANDLER_TYPE()& a, int)
  {
    I ret(derived(a));
    decrement(a);
    return ret;
  }

#define FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(prefix, result_type, name)\
  template<class I, class IBase, class I2, class IBase2,\
    class C, class V, class D, class P, class R>\
  prefix result_type name(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
                          const iterator_handler<I2, IBase2, C, V, D, P, R>& b)

#define FALCON_ITERATOR_CORE_ACCESS_COMPARISON(result_type, op, member)\
  FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(static, result_type, member)\
  { return derived(a).member(derived(b)); }\
  FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(friend, result_type, operator op)\
  { return member(a, b); }

  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(bool, ==, equal)
  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(bool, <, less)
  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(typename I::difference_type, -, difference)

#undef FALCON_ITERATOR_CORE_ACCESS_COMPARISON

#define FALCON_ITERATOR_CORE_ACCESS_COMPARISON(op, core)\
  FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(friend, bool, operator op)\
  { return core; }

  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(!=, !(a==b))
  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(<=, !(b<a))
  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(>,    b<a)
  FALCON_ITERATOR_CORE_ACCESS_COMPARISON(>=, !(a<b))

#undef FALCON_ITERATOR_CORE_ACCESS_COMPARISON

#define FALCON_ITERATOR_CORE_ACCESS_MOVE(op, op2, member, member2)\
  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
  static void member(FALCON_ITERATOR_HANDLER_TYPE()& a,\
                     typename I::difference_type n)\
  { derived(a).member(n); }\
  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
  static I member2(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
                   typename I::difference_type n)\
  { return derived(a).member2(n); }\
  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
  friend I& operator op2(FALCON_ITERATOR_HANDLER_TYPE()& a,\
                         typename I::difference_type n)\
  {\
    member(a, n);\
    return derived(a);\
  }\
  FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
  friend I operator op(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
                       typename I::difference_type n)\
  { return member2(a, n); }

  FALCON_ITERATOR_CORE_ACCESS_MOVE(+, +=, advance, next)
  FALCON_ITERATOR_CORE_ACCESS_MOVE(-, -=, recoil, prev)

#undef FALCON_ITERATOR_CORE_ACCESS_MOVE

#undef FALCON_ITERATOR_HANDLER_TYPE
#undef FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD

#undef FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD
};

template<
  class Iterator
, class IteratorBase
, class Category
, class T
, class Distance
, class Pointer
, class Reference
>
class iterator_handler
: public std::iterator<Category, T, Distance, Pointer, Reference>
, public iterator_core_access
{
  friend class iterator_core_access;

  typedef std::iterator<Category, T, Distance, Pointer, Reference> inherit_type;


public:
  typedef IteratorBase iterator_type;
  typedef typename inherit_type::iterator_category iterator_category;
  typedef typename inherit_type::value_type value_type;
  typedef typename inherit_type::difference_type difference_type;
  typedef typename inherit_type::pointer pointer;
  typedef typename inherit_type::reference reference;


private:
  IteratorBase current_;


public:
  iterator_handler()
  : current_()
  {}

  explicit iterator_handler(const iterator_type& x, int)
  : current_(x)
  {}

#if __cplusplus >= 201103L
  explicit iterator_handler(iterator_type const & x)
  : current_(x)
  {}

  explicit iterator_handler(iterator_type&& x)
  : current_(std::move(x))
  {}

  explicit iterator_handler(iterator_type&& x, int)
  : current_(std::move(x))
  {}

  template<typename... Args>
  explicit iterator_handler(std::piecewise_construct_t, Args&&... args)
  : current_(std::forward<Args>(args)...)
  {}

  iterator_handler& operator=(iterator_type&& x)
  {
    current_ = std::move(x);
    return *this;
  }
#else
  explicit iterator_handler(iterator_type x)
  : current_(x)
  {}

  template<class U>
  explicit iterator_handler(U const & x)
  : current_(x)
  {}
#endif

  template<class I2, class IBase2, class C2, class T2, class D2, class P2, class R2>
  explicit iterator_handler(const iterator_handler<I2, IBase2, C2, T2, D2, P2, R2>& other)
  : current_(iterator_core_access::base_reference(other.current_))
  {}

  iterator_handler& operator=(const iterator_type& x)
  {
    current_ = x;
    return *this;
  }

  iterator_type base() const
  { return current_; }

  pointer operator->()
  { return &**this; }

  pointer operator->() const
  { return &**this; }

  reference operator[](difference_type n)
  { return *(*this + n); }

  reference operator[](difference_type n) const
  { return *(*this + n); }

  reference operator*()
  { return iterator_core_access::dereference(*this); }

  reference operator*() const
  { return iterator_core_access::dereference(*this); }

protected:
  iterator_type& base_reference()
  { return current_; }

  const iterator_type& base_reference() const
  { return current_; }

  Iterator& downcast()
  { return static_cast<Iterator&>(*this); }

  const Iterator& downcast() const
  { return static_cast<const Iterator&>(*this); }

  reference dereference() const
  { return *current_; }

  reference dereference()
  { return *current_; }

  void increment()
  { ++current_; }

  void decrement()
  { --current_; }

  bool equal(const iterator_handler& x) const
  { return current_ == x.current_; }

  bool less(const iterator_handler& x) const
  { return current_ < x.current_; }

  difference_type difference(const iterator_handler& x,
                             std::forward_iterator_tag) const
  { return current_ - x.current_; }

  difference_type difference(const iterator_handler& x) const
  { return difference(x, iterator_category()); }

  void advance(difference_type n)
  { current_ += n; }

  Iterator next(difference_type n) const
  {
    Iterator ret(downcast());
    ret += n;
    return ret;
  }

  void recoil(difference_type n)
  { downcast() += -n; }

  Iterator prev(difference_type n) const
  { return downcast() + -n; }
};

template<
  class Iterator
, class IteratorBase
, class Category = use_default
, class T = use_default
, class Distance = use_default
, class Pointer = use_default
, class Reference = use_default
>
struct iterator_handler_types
{
  typedef std::iterator_traits<IteratorBase> iterator_traits;

  typedef typename default_or_type<
    restrict_iterator_category<iterator_traits>
  , Category
  >::type iterator_category;

  typedef typename default_or_type<
    restrict_value_type<iterator_traits>
  , T
  >::type value_type;

  typedef typename default_or_type<
    restrict_difference_type<iterator_traits>
  , Distance
  >::type difference_type;

  typedef typename eval_if_c<
    is_default<Pointer>
  , eval_if_c<
      is_default<T>
    , restrict_pointer<iterator_traits>
    , FALCON_BOOST_OR_STD_NAMESPACE::add_pointer<value_type>
    >
  , use<Pointer>
  >::type pointer;

  typedef typename eval_if_c<
    is_default<Reference>
  , eval_if_c<
      is_default<T>
    , restrict_reference<iterator_traits>
    , use<value_type&>
    >
  , use<Reference>
  >::type reference;

  typedef iterator_handler<
    Iterator
  , IteratorBase
  , iterator_category
  , value_type
  , difference_type
  , pointer
  , reference
  > type;
};

}}

#endif
