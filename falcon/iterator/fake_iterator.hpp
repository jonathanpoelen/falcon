#ifndef FALCON_ITERATOR_FAKE_ITERATOR_HPP
#define FALCON_ITERATOR_FAKE_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {

struct fake_iterator_full_comparison_tag {};
struct fake_iterator_less_comparison_tag {};
struct fake_iterator_equal_to_comparison_tag {};

template <typename _T, typename _ComparisonTag = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default
>
class fake_iterator;

template <typename _T, typename _ComparisonTag = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default
>
class reverse_fake_iterator;


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
	: __fake_base<fake_iterator,
		_T, _ComparisonTag,  _Category, _Reference, _Distance, _Pointer>
	{};

	template <typename _T, typename _ComparisonTag,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct reverse_fake_base
	: __fake_base<reverse_fake_iterator,
		_T, _ComparisonTag,  _Category, _Reference, _Distance, _Pointer>
	{};

}


template<typename _T, typename _ComparisonTag,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class fake_iterator
: public detail::fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base
{
	typedef typename detail::fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base __base;

	friend iterator_core_access;

public:
	typedef typename __base::reference reference;

public:
	fake_iterator()
	: __base()
	{}

	fake_iterator(const fake_iterator& other)
	: __base(other)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/*explicit*/ fake_iterator(_T&& value)
	: __base(value)
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<_T>::value && std::is_convertible<_U, _T>::value>::type>
	/*explicit*/ fake_iterator(_U&& value)
	: __base(std::forward<_U>(value))
	{}
#else
	/*explicit*/ fake_iterator(const _T& value)
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
		use<fake_iterator_full_comparison_tag>,
		_ComparisonTag
	>::type __comparison_tag;

	bool equal(const fake_iterator& other, fake_iterator_less_comparison_tag) const
	{ return other.base_reference() < this->base_reference(); }

	template<typename _Tag>
	bool equal(const fake_iterator& other, _Tag) const
	{ return this->base_reference() == other.base_reference(); }

	bool equal(const fake_iterator& other) const
	{ return equal(other, __comparison_tag()); }

	bool less(const fake_iterator& other, fake_iterator_equal_to_comparison_tag) const;

	template<typename _Tag>
	bool less(const fake_iterator& other, _Tag) const
	{ return this->base_reference() < other.base_reference(); }

	bool less(const fake_iterator& other) const
	{ return less(other, __comparison_tag()); }
};


template <typename _T>
fake_iterator<_T> make_fake_iterator(const _T& value)
{ return fake_iterator<_T>(value); }

template <typename _T, typename _ComparisonTag>
fake_iterator<_T, _ComparisonTag>
make_fake_iterator(const _T& value, _ComparisonTag)
{ return fake_iterator<_T, _ComparisonTag>(value); }

template <typename _T>
fake_iterator<const _T> make_cfake_iterator(const _T& value)
{ return fake_iterator<const _T>(value); }

template <typename _T, typename _ComparisonTag>
fake_iterator<const _T, _ComparisonTag>
make_cfake_iterator(const _T& value, _ComparisonTag)
{ return fake_iterator<const _T, _ComparisonTag>(value); }


template<typename _T, typename _ComparisonTag,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class reverse_fake_iterator
: public detail::reverse_fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base
{
	typedef typename detail::reverse_fake_base<_T, _ComparisonTag, _Category, _Reference, _Distance, _Pointer>::base __base;

	friend iterator_core_access;

public:
	typedef typename __base::reference reference;
	typedef typename __base::difference_type difference_type;

public:
	reverse_fake_iterator()
	: __base()
	{}

	reverse_fake_iterator(const reverse_fake_iterator& other)
	: __base(other)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/*explicit*/ reverse_fake_iterator(_T&& value)
	: __base(value)
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<_T>::value && std::is_convertible<_U, _T>::value>::type>
	/*explicit*/ reverse_fake_iterator(_U&& value)
	: __base(std::forward<_U>(value))
	{}
#else
	/*explicit*/ reverse_fake_iterator(const _T& value)
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

	difference_type difference(const reverse_fake_iterator& other) const
	{ return other.base_reference() - this->base_reference(); }

	typedef typename default_or_type<
		use<fake_iterator_full_comparison_tag>,
		_ComparisonTag
	>::type __comparison_tag;

	bool equal(const reverse_fake_iterator& other, fake_iterator_less_comparison_tag) const
	{ return other.base_reference() > this->base_reference(); }

	template<typename _Tag>
	bool equal(const reverse_fake_iterator& other, _Tag) const
	{ return this->base_reference() == other.base_reference(); }

	bool equal(const reverse_fake_iterator& other) const
	{ return equal(other, __comparison_tag()); }

	bool less(const reverse_fake_iterator& other, fake_iterator_equal_to_comparison_tag) const;

	template<typename _Tag>
	bool less(const reverse_fake_iterator& other, _Tag) const
	{ return this->base_reference() > other.base_reference(); }

	bool less(const reverse_fake_iterator& other) const
	{ return less(other, __comparison_tag()); }
};


template <typename _T>
reverse_fake_iterator<_T> make_reverse_fake_iterator(const _T& value)
{ return reverse_fake_iterator<_T>(value); }

template <typename _T, typename _ComparisonTag>
reverse_fake_iterator<_T, _ComparisonTag>
make_reverse_fake_iterator(const _T& value, _ComparisonTag)
{ return reverse_fake_iterator<_T, _ComparisonTag>(value); }

template <typename _T>
reverse_fake_iterator<const _T> make_creverse_fake_iterator(const _T& value)
{ return reverse_fake_iterator<const _T>(value); }

template <typename _T, typename _ComparisonTag>
reverse_fake_iterator<const _T, _ComparisonTag>
make_creverse_fake_iterator(const _T& value, _ComparisonTag)
{ return reverse_fake_iterator<const _T, _ComparisonTag>(value); }

}}

#endif