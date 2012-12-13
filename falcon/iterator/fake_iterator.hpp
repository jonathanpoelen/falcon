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


namespace detail {

	template <typename _T, typename _ComparisonTag,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct fake_base
	{
		typedef typename iterator_handler_types<
			fake_iterator<_T, _ComparisonTag,  _Category, _Reference, _Distance, _Pointer>,
			_T,
			typename default_or_type<
				use<std::random_access_iterator_tag/*TODO not always*/>,
				_Category
			>::type,
			_T,
			typename default_or_type<use<_T>, _Distance>::type,
			typename default_or_type<use<_T*>, _Pointer>::type,
			typename default_or_type<use<_T&>, _Reference>::type
		>::base base;
	};

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


template <typename _T, typename _ComparisonTag>
fake_iterator<_T, _ComparisonTag>
make_fake_iterator(const _T& value,
									 _ComparisonTag = fake_iterator_full_comparison_tag())
{ return fake_iterator<_T, _ComparisonTag>(value); }

template <typename _T, typename _ComparisonTag>
fake_iterator<const _T, _ComparisonTag>
make_cfake_iterator(const _T& value,
										_ComparisonTag = fake_iterator_full_comparison_tag())
{ return fake_iterator<const _T, _ComparisonTag>(value); }

}}

#endif