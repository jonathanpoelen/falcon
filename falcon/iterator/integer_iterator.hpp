#ifndef FALCON_ITERATOR_INTEGER_ITERATOR_HPP
#define FALCON_ITERATOR_INTEGER_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {

struct integer_iterator_full_comparison_tag {};
struct integer_iterator_less_comparison_tag {};
struct integer_iterator_equal_to_comparison_tag {};

template <typename T, typename ComparisonTag = use_default,
	typename Category = use_default,
	typename Reference = use_default,
	typename Distance = use_default,
	typename Pointer = use_default
>
class integer_iterator;

template <typename T, typename ComparisonTag = use_default,
	typename Category = use_default,
	typename Reference = use_default,
	typename Distance = use_default,
	typename Pointer = use_default
>
class reverse_integer_iterator;


namespace detail {

	template <template<class,class,class,class,class,class> class IntegerIterator,
		typename T, typename ComparisonTag,
		typename Category, typename Reference, typename Distance, typename Pointer>
	struct __integer_base
	{
		typedef typename iterator_handler_types<
			IntegerIterator<T, ComparisonTag, Category, Reference, Distance, Pointer>,
			T,
			typename default_or_type<
				use<std::random_access_iterator_tag /*TODO not always*/>,
				Category
			>::type,
			T,
			typename default_or_type<difference<T>, Distance>::type,
			typename default_or_type<use<T*>, Pointer>::type,
			typename default_or_type<use<T&>, Reference>::type
		>::base base;
	};

	template <typename T, typename ComparisonTag,
		typename Category, typename Reference, typename Distance, typename Pointer>
	struct integer_base
	: __integer_base<integer_iterator,
		T, ComparisonTag,  Category, Reference, Distance, Pointer>
	{};

	template <typename T, typename ComparisonTag,
		typename Category, typename Reference, typename Distance, typename Pointer>
	struct reverse_integer_base
	: __integer_base<reverse_integer_iterator,
		T, ComparisonTag,  Category, Reference, Distance, Pointer>
	{};

}


template<typename T, typename ComparisonTag,
	typename Category,
	typename Reference,
	typename Distance,
	typename Pointer
>
class integer_iterator
: public detail::integer_base<T, ComparisonTag, Category, Reference, Distance, Pointer>::base
{
	typedef typename detail::integer_base<T, ComparisonTag, Category, Reference, Distance, Pointer>::base __base;

	friend class iterator_core_access;

public:
	typedef typename __base::reference reference;

public:
	integer_iterator()
	: __base()
	{}

	integer_iterator(const integer_iterator& other)
	: __base(other)
	{}

#if __cplusplus >= 201103L
	explicit integer_iterator(T&& value)
  : __base(std::forward<T>(value))
	{}

	template<typename U, class Enable = typename
	std::enable_if<!std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
	explicit integer_iterator(U&& value)
	: __base(std::piecewise_construct, std::forward<U>(value))
	{}
#else
	explicit integer_iterator(const T& value)
	: __base(value, 1)
	{}
#endif

	using __base::operator=;

private:
	reference dereference()
	{ return this->base_reference(); }

	reference dereference() const
	{ return this->base_reference(); }

	typedef typename default_or_type<
		use<integer_iterator_full_comparison_tag>,
		ComparisonTag
	>::type __comparison_tag;

	bool equal(const integer_iterator& other, integer_iterator_less_comparison_tag) const
	{ return other.base_reference() < this->base_reference(); }

	template<typename Tag>
	bool equal(const integer_iterator& other, Tag) const
	{ return this->base_reference() == other.base_reference(); }

	bool equal(const integer_iterator& other) const
	{ return equal(other, __comparison_tag()); }

	bool less(const integer_iterator& other, integer_iterator_equal_to_comparison_tag) const;

	template<typename Tag>
	bool less(const integer_iterator& other, Tag) const
	{ return this->base_reference() < other.base_reference(); }

	bool less(const integer_iterator& other) const
	{ return less(other, __comparison_tag()); }
};


template <typename T>
integer_iterator<T> make_integer_iterator(const T& value)
{ return integer_iterator<T>(value); }

template <typename T, typename ComparisonTag>
integer_iterator<T, ComparisonTag>
make_integer_iterator(const T& value, ComparisonTag)
{ return integer_iterator<T, ComparisonTag>(value); }

template <typename T>
integer_iterator<const T> make_cinteger_iterator(const T& value)
{ return integer_iterator<const T>(value); }

template <typename T, typename ComparisonTag>
integer_iterator<const T, ComparisonTag>
make_cinteger_iterator(const T& value, ComparisonTag)
{ return integer_iterator<const T, ComparisonTag>(value); }


template<typename T, typename ComparisonTag,
	typename Category,
	typename Reference,
	typename Distance,
	typename Pointer
>
class reverse_integer_iterator
: public detail::reverse_integer_base<T, ComparisonTag, Category, Reference, Distance, Pointer>::base
{
	typedef typename detail::reverse_integer_base<T, ComparisonTag, Category, Reference, Distance, Pointer>::base __base;

	friend class iterator_core_access;

public:
	typedef typename __base::reference reference;
	typedef typename __base::difference_type difference_type;

public:
	reverse_integer_iterator()
	: __base()
	{}

	reverse_integer_iterator(const reverse_integer_iterator& other)
	: __base(other)
	{}

#if __cplusplus >= 201103L
	explicit reverse_integer_iterator(T&& value)
  : __base(std::forward<T>(value))
	{}

	template<typename U, class Enable = typename
	std::enable_if<!std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
	explicit reverse_integer_iterator(U&& value)
  : __base(std::piecewise_construct, std::forward<U>(value))
	{}
#else
	explicit reverse_integer_iterator(const T& value)
	: __base(value, 1)
	{}
#endif

	using __base::operator=;

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

	void recoil(difference_type n)
	{ this->base_reference() += n; }

	difference_type difference(const reverse_integer_iterator& other) const
	{ return other.base_reference() - this->base_reference(); }

	typedef typename default_or_type<
		use<integer_iterator_full_comparison_tag>,
		ComparisonTag
	>::type __comparison_tag;

	bool equal(const reverse_integer_iterator& other, integer_iterator_less_comparison_tag) const
  { return this->base_reference() < other.base_reference(); }

	template<typename Tag>
	bool equal(const reverse_integer_iterator& other, Tag) const
	{ return this->base_reference() == other.base_reference(); }

	bool equal(const reverse_integer_iterator& other) const
	{ return equal(other, __comparison_tag()); }

	bool less(const reverse_integer_iterator& other, integer_iterator_equal_to_comparison_tag) const;

	template<typename Tag>
	bool less(const reverse_integer_iterator& other, Tag) const
  { return other.base_reference() < this->base_reference(); }

	bool less(const reverse_integer_iterator& other) const
	{ return less(other, __comparison_tag()); }
};


template <typename T>
reverse_integer_iterator<T> make_reverse_integer_iterator(const T& value)
{ return reverse_integer_iterator<T>(value); }

template <typename T, typename ComparisonTag>
reverse_integer_iterator<T, ComparisonTag>
make_reverse_integer_iterator(const T& value, ComparisonTag)
{ return reverse_integer_iterator<T, ComparisonTag>(value); }

template <typename T>
reverse_integer_iterator<const T> make_creverse_integer_iterator(const T& value)
{ return reverse_integer_iterator<const T>(value); }

template <typename T, typename ComparisonTag>
reverse_integer_iterator<const T, ComparisonTag>
make_creverse_integer_iterator(const T& value, ComparisonTag)
{ return reverse_integer_iterator<const T, ComparisonTag>(value); }


template <typename T, typename ComparisonTag = use_default,
  typename Category = use_default,
  typename Reference = use_default,
  typename Distance = use_default,
  typename Pointer = use_default
>
class integer_iterator_with_step
: public detail::__integer_base<
  integer_iterator_with_step
, T, ComparisonTag, Category, Reference, Distance, Pointer>::base
{
  typedef typename detail::__integer_base<
    integer_iterator_with_step
  , T, ComparisonTag, Category, Reference, Distance, Pointer
  >::base __base;

  friend class iterator_core_access;

public:
  typedef typename __base::reference reference;
  typedef typename __base::iterator_type iterator_type;
  typedef typename __base::difference_type difference_type;

public:
  integer_iterator_with_step()
  : __base()
  , m_step(1)
  {}

  integer_iterator_with_step(const iterator_type& other)
  : __base(other)
  , m_step(1)
  {}

  integer_iterator_with_step(const iterator_type& other, difference_type step)
  : __base(other)
  , m_step(other.m_step)
  {}

  integer_iterator_with_step(const integer_iterator_with_step& other)
  : __base(other)
  , m_step(other.m_step)
  {}

  integer_iterator_with_step(const integer_iterator_with_step& other, difference_type step)
  : __base(other)
  , m_step(other.m_step)
  {}

#if __cplusplus >= 201103L
  explicit integer_iterator_with_step(T&& value)
  : __base(std::piecewise_construct, std::forward<T>(value))
  , m_step(1)
  {}

  integer_iterator_with_step(T&& value, difference_type step)
  : __base(std::piecewise_construct, std::forward<T>(value))
  , m_step(step)
  {}

  template<typename U, class Enable = typename
  std::enable_if<!std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  explicit integer_iterator_with_step(U&& value)
  : __base(std::piecewise_construct, std::forward<U>(value))
  , m_step(1)
  {}

  template<typename U, class Enable = typename
  std::enable_if<!std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  integer_iterator_with_step(U&& value, difference_type step)
  : __base(std::piecewise_construct, std::forward<U>(value))
  , m_step(step)
  {}
#else
  explicit integer_iterator_with_step(const T& value)
  : __base(iterator_type(value), 1)
  , m_step(1)
  {}

  integer_iterator_with_step(const T& value, difference_type step)
  : __base(iterator_type(value), 1)
  , m_step(step)
  {}
#endif

  using __base::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }

  typedef typename default_or_type<
    use<integer_iterator_full_comparison_tag>,
    ComparisonTag
  >::type __comparison_tag;

  bool equal(const integer_iterator_with_step& other, integer_iterator_less_comparison_tag) const
  { return other.base_reference() < this->base_reference(); }

  template<typename Tag>
  bool equal(const integer_iterator_with_step& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const integer_iterator_with_step& other) const
  { return equal(other, __comparison_tag()); }

  bool less(const integer_iterator_with_step& other, integer_iterator_equal_to_comparison_tag) const;

  template<typename Tag>
  bool less(const integer_iterator_with_step& other, Tag) const
  { return this->base_reference() < other.base_reference(); }

  bool less(const integer_iterator_with_step& other) const
  { return less(other, __comparison_tag()); }

  void increment()
  { this->base_reference() += m_step; }

  void decrement()
  { this->base_reference() -= m_step; }

  void advance(difference_type n)
  { this->base_reference() += n * m_step; }

  void recoil(difference_type n)
  { this->base_reference() -= n * m_step; }

  difference_type m_step;
};

template <typename T, typename ComparisonTag = use_default,
  typename Category = use_default,
  typename Reference = use_default,
  typename Distance = use_default,
  typename Pointer = use_default
>
class reverse_integer_iterator_with_step
: public detail::__integer_base<
  reverse_integer_iterator_with_step
, integer_iterator<T, ComparisonTag, Category, Reference, Distance, Pointer>
, ComparisonTag, Category, Reference, Distance, Pointer>::base
{
  typedef typename detail::__integer_base<
    reverse_integer_iterator_with_step
  , integer_iterator<T, ComparisonTag, Category, Reference, Distance, Pointer>
  , ComparisonTag, Category, Reference, Distance, Pointer
  >::base __base;

  friend class iterator_core_access;

public:
  typedef typename __base::reference reference;
  typedef typename __base::iterator_type iterator_type;
  typedef typename __base::difference_type difference_type;

public:
  reverse_integer_iterator_with_step()
  : __base()
  , m_step(1)
  {}

  reverse_integer_iterator_with_step(const iterator_type& other)
  : __base(other)
  , m_step(1)
  {}

  reverse_integer_iterator_with_step(const iterator_type& other, difference_type step)
  : __base(other)
  , m_step(step)
  {}

  reverse_integer_iterator_with_step(const reverse_integer_iterator_with_step& other)
  : __base(other)
  , m_step(1)
  {}

  reverse_integer_iterator_with_step(const reverse_integer_iterator_with_step& other,
                                     difference_type step)
  : __base(other)
  , m_step(step)
  {}

#if __cplusplus >= 201103L
  explicit reverse_integer_iterator_with_step(T&& value)
  : __base(std::piecewise_construct, std::forward<T>(value))
  , m_step(1)
  {}

  reverse_integer_iterator_with_step(T&& value, difference_type step)
  : __base(std::piecewise_construct, std::forward<T>(value))
  , m_step(step)
  {}

  template<typename U, class Enable = typename
  std::enable_if<!std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  explicit reverse_integer_iterator_with_step(U&& value)
  : __base(std::piecewise_construct, std::forward<U>(value))
  , m_step(1)
  {}

  template<typename U, class Enable = typename
  std::enable_if<!std::is_reference<T>::value && std::is_convertible<U, T>::value>::type>
  reverse_integer_iterator_with_step(U&& value, difference_type step)
  : __base(std::piecewise_construct, std::forward<U>(value))
  , m_step(step)
  {}
#else
  explicit reverse_integer_iterator_with_step(const T& value)
  : __base(iterator_type(value), 1)
  , m_step(1)
  {}

  reverse_integer_iterator_with_step(const T& value, difference_type step)
  : __base(iterator_type(value), 1)
  , m_step(step)
  {}
#endif

  using __base::operator=;

private:
  reference dereference()
  { return this->base_reference(); }

  reference dereference() const
  { return this->base_reference(); }

  void increment()
  { this->base_reference() -= m_step; }

  void decrement()
  { this->base_reference() += m_step; }

  void advance(difference_type n)
  { this->base_reference() -= n * m_step; }

  void recoil(difference_type n)
  { this->base_reference() += n * m_step; }

  difference_type difference(const reverse_integer_iterator_with_step& other) const
  { return other.base_reference() - this->base_reference(); }

  typedef typename default_or_type<
    use<integer_iterator_full_comparison_tag>,
    ComparisonTag
  >::type __comparison_tag;

  bool equal(const reverse_integer_iterator_with_step& other,
             integer_iterator_less_comparison_tag) const
  { return this->base_reference() < other.base_reference(); }

  template<typename Tag>
  bool equal(const reverse_integer_iterator_with_step& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const reverse_integer_iterator_with_step& other) const
  { return equal(other, __comparison_tag()); }

  bool less(const reverse_integer_iterator_with_step& other,
            integer_iterator_equal_to_comparison_tag) const;

  template<typename Tag>
  bool less(const reverse_integer_iterator_with_step& other, Tag) const
  { return other.base_reference() < this->base_reference(); }

  bool less(const reverse_integer_iterator_with_step& other) const
  { return less(other, __comparison_tag()); }

  difference_type m_step;
};

template <typename T>
reverse_integer_iterator_with_step<T>
make_reverse_integer_iterator_with_step(const T& value,
                                        typename reverse_integer_iterator_with_step<T>
                                          ::difference_type step)
{ return reverse_integer_iterator_with_step<T>(value, step); }

template <typename T, typename ComparisonTag>
reverse_integer_iterator_with_step<T, ComparisonTag>
make_reverse_integer_iterator_with_step(const T& value,
                                        typename reverse_integer_iterator_with_step<T>
                                          ::difference_type step,
                                        ComparisonTag)
{ return reverse_integer_iterator_with_step<T, ComparisonTag>(value, step); }

template <typename T>
reverse_integer_iterator_with_step<const T>
make_creverse_integer_iterator_with_step(const T& value,
                                         typename reverse_integer_iterator_with_step<T>
                                           ::difference_type step)
{ return reverse_integer_iterator_with_step<const T>(value, step); }

template <typename T, typename ComparisonTag>
reverse_integer_iterator_with_step<const T, ComparisonTag>
make_creverse_integer_iterator_with_step(const T& value,
                                        typename reverse_integer_iterator_with_step<T>
                                          ::difference_type step,
                                        ComparisonTag)
{ return reverse_integer_iterator_with_step<const T, ComparisonTag>(value, step); }

}}

#endif
