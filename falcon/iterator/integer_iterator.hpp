#ifndef FALCON_ITERATOR_FAKE_ITERATOR_HPP
#define FALCON_ITERATOR_FAKE_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {

struct integer_iterator_full_comparison_tag {};
struct integer_iterator_less_comparison_tag {};
struct integer_iterator_equal_to_comparison_tag {};

template <typename _T, typename _ComparisonTag = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default
>
class integer_iterator;

template <typename _T, typename _ComparisonTag = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default
>
class reverse_integer_iterator;


namespace detail {

	template <template<class,class,class,class,class,class> class _Fake,
		typename _T, typename _ComparisonTag,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct __fake_base
	{
		typedef typename iterator_handler_types<
			_Fake<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>,
			_T,
			typename default_or_type<
				use<std::random_access_iterator_tag/*TODO not always*/>,
				_Category
			>::type,
			_T,
			typename default_or_type<difference<_T>, _Distance>::type,
			typename default_or_type<use<_T*>, _Pointer>::type,
			typename default_or_type<use<_T&>, _Reference>::type
		>::base base;
	};

	template <typename _T, typename _ComparisonTag,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct fake_base
	: __fake_base<integer_iterator,
		_T, _ComparisonTag,  _Category, _Reference, _Distance, _Pointer>
	{};

	template <typename _T, typename _ComparisonTag,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct reverse_fake_base
	: __fake_base<reverse_integer_iterator,
		_T, _ComparisonTag,  _Category, _Reference, _Distance, _Pointer>
	{};

}


template<typename _T, typename _ComparisonTag,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class integer_iterator
: public detail::fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base
{
	typedef typename detail::fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base __base;

	friend iterator_core_access;

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
	/*explicit*/ integer_iterator(_T&& value)
	: __base(value)
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<_T>::value && std::is_convertible<_U, _T>::value>::type>
	/*explicit*/ integer_iterator(_U&& value)
	: __base(std::forward<_U>(value))
	{}
#else
	/*explicit*/ integer_iterator(const _T& value)
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
		_ComparisonTag
	>::type __comparison_tag;

	bool equal(const integer_iterator& other, integer_iterator_less_comparison_tag) const
	{ return other.base_reference() < this->base_reference(); }

	template<typename _Tag>
	bool equal(const integer_iterator& other, _Tag) const
	{ return this->base_reference() == other.base_reference(); }

	bool equal(const integer_iterator& other) const
	{ return equal(other, __comparison_tag()); }

	bool less(const integer_iterator& other, integer_iterator_equal_to_comparison_tag) const;

	template<typename _Tag>
	bool less(const integer_iterator& other, _Tag) const
	{ return this->base_reference() < other.base_reference(); }

	bool less(const integer_iterator& other) const
	{ return less(other, __comparison_tag()); }
};


template <typename _T>
integer_iterator<_T> make_integer_iterator(const _T& value)
{ return integer_iterator<_T>(value); }

template <typename _T, typename _ComparisonTag>
integer_iterator<_T, _ComparisonTag>
make_integer_iterator(const _T& value, _ComparisonTag)
{ return integer_iterator<_T, _ComparisonTag>(value); }

template <typename _T>
integer_iterator<const _T> make_cinteger_iterator(const _T& value)
{ return integer_iterator<const _T>(value); }

template <typename _T, typename _ComparisonTag>
integer_iterator<const _T, _ComparisonTag>
make_cinteger_iterator(const _T& value, _ComparisonTag)
{ return integer_iterator<const _T, _ComparisonTag>(value); }


template<typename _T, typename _ComparisonTag,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class reverse_integer_iterator
: public detail::reverse_fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base
{
	typedef typename detail::reverse_fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base __base;

	friend iterator_core_access;

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
	/*explicit*/ reverse_integer_iterator(_T&& value)
	: __base(value)
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<_T>::value && std::is_convertible<_U, _T>::value>::type>
	/*explicit*/ reverse_integer_iterator(_U&& value)
	: __base(std::forward<_U>(value))
	{}
#else
	/*explicit*/ reverse_integer_iterator(const _T& value)
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
		_ComparisonTag
	>::type __comparison_tag;

	bool equal(const reverse_integer_iterator& other, integer_iterator_less_comparison_tag) const
	{ return other.base_reference() > this->base_reference(); }

	template<typename _Tag>
	bool equal(const reverse_integer_iterator& other, _Tag) const
	{ return this->base_reference() == other.base_reference(); }

	bool equal(const reverse_integer_iterator& other) const
	{ return equal(other, __comparison_tag()); }

	bool less(const reverse_integer_iterator& other, integer_iterator_equal_to_comparison_tag) const;

	template<typename _Tag>
	bool less(const reverse_integer_iterator& other, _Tag) const
	{ return this->base_reference() > other.base_reference(); }

	bool less(const reverse_integer_iterator& other) const
	{ return less(other, __comparison_tag()); }
};


template <typename _T>
reverse_integer_iterator<_T> make_reverse_integer_iterator(const _T& value)
{ return reverse_integer_iterator<_T>(value); }

template <typename _T, typename _ComparisonTag>
reverse_integer_iterator<_T, _ComparisonTag>
make_reverse_integer_iterator(const _T& value, _ComparisonTag)
{ return reverse_integer_iterator<_T, _ComparisonTag>(value); }

template <typename _T>
reverse_integer_iterator<const _T> make_creverse_integer_iterator(const _T& value)
{ return reverse_integer_iterator<const _T>(value); }

template <typename _T, typename _ComparisonTag>
reverse_integer_iterator<const _T, _ComparisonTag>
make_creverse_integer_iterator(const _T& value, _ComparisonTag)
{ return reverse_integer_iterator<const _T, _ComparisonTag>(value); }

}}

#endif