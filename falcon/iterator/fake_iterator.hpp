#ifndef FALCON_ITERATOR_FAKE_ITERATOR_HPP
#define FALCON_ITERATOR_FAKE_ITERATOR_HPP

#include <falcon/iterator/detail/handler_iterator.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {
	struct fake_iterator_full_comparison_tag {};
	struct fake_iterator_less_comparison_tag {};
	struct fake_iterator_equal_to_comparison_tag {};

	template <typename _T, typename _ComparisonTag = fake_iterator_full_comparison_tag>
	class fake_iterator;
}}

namespace std
{
	template <typename _T, typename _ComparisonTag>
	struct iterator_traits< ::falcon::iterator::fake_iterator<_T, _ComparisonTag> >
	{
		typedef typename ::falcon::difference<_T>::type difference_type;
		///TODO not always
		typedef std::random_access_iterator_tag iterator_category;
		typedef _T value_type;
		typedef value_type& reference;
		typedef value_type* pointer;
	};

	template <typename _T, typename _ComparisonTag>
	struct iterator_traits< ::falcon::iterator::fake_iterator<_T&, _ComparisonTag> >
	{
		typedef typename ::falcon::difference<_T>::type difference_type;
		///TODO not always
		typedef std::random_access_iterator_tag iterator_category;
		typedef _T& value_type;
		typedef _T& reference;
		typedef _T* pointer;
	};
}

namespace falcon {
namespace iterator {

template<typename _T, typename _ComparisonTag>
struct __fake_iterator_traits_base
: detail::handler_iterator_trait<fake_iterator<_T, _ComparisonTag>, _T>
{
	typedef fake_iterator<_T, _ComparisonTag> __fake_iterator;
	typedef typename std::iterator_traits<__fake_iterator>::reference reference;

	static reference dereference(__fake_iterator& it)
	{ return it._M_current; }

	static reference dereference(const __fake_iterator& it)
	{ return it._M_current; }
};

template<typename>
class __fake_iterator_traits;

template<typename _T, typename _ComparisonTag>
struct __fake_iterator_traits<fake_iterator<_T, _ComparisonTag> >
: __fake_iterator_traits_base<_T, _ComparisonTag>
{};

template<typename _T>
struct __fake_iterator_traits<fake_iterator<_T, fake_iterator_equal_to_comparison_tag> >
: __fake_iterator_traits_base<_T, fake_iterator_equal_to_comparison_tag>
{
	typedef fake_iterator<_T, fake_iterator_equal_to_comparison_tag> __fake_iterator;
	static bool lt(const __fake_iterator& a, const __fake_iterator& b);
};

template<typename _T>
struct __fake_iterator_traits<fake_iterator<_T, fake_iterator_less_comparison_tag> >
: __fake_iterator_traits_base<_T, fake_iterator_less_comparison_tag>
{
	typedef fake_iterator<_T, fake_iterator_less_comparison_tag> __fake_iterator;
	static bool eq(const __fake_iterator& a, const __fake_iterator& b)
	{ return !(a._M_current < b._M_current); }
};


template<typename _T, typename _ComparisonTag>
class fake_iterator
: public detail::handler_iterator<
	fake_iterator<_T, _ComparisonTag>,
	_T,
	__fake_iterator_traits<fake_iterator<_T, _ComparisonTag> >
>
{
	typedef __fake_iterator_traits<fake_iterator> __traits;
	typedef detail::handler_iterator<fake_iterator, _T, __traits> __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::value_type value_type;

public:
	fake_iterator()
	: __base()
	{}

	fake_iterator(const fake_iterator& other)
	: __base(other._M_current)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/*explicit*/ fake_iterator(_T&& value)
	: __base(value)
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<iterator_type>::value && std::is_convertible<_U, iterator_type>::value>::type>
	/*explicit*/ fake_iterator(_U&& value)
	: __base(std::forward<_U>(value))
	{}
#else
	/*explicit*/ fake_iterator(const _T& value)
	: __base(value, 1)
	{}
#endif

	using __base::operator=;

	const value_type& operator*() const
	{ return __traits::dereference(this->downcast()); }

	using __base::operator*;

	const value_type* operator->() const
	{ return &(operator*()); }

	using __base::operator->;
};

template <typename _T, typename _ComparisonTag>
fake_iterator<_T, _ComparisonTag>
make_fake_iterator(const _T& value,
				   const _ComparisonTag& = _ComparisonTag())
{ return fake_iterator<_T, _ComparisonTag>(value); }

template <typename _T, typename _ComparisonTag>
fake_iterator<const _T, _ComparisonTag>
make_cfake_iterator(const _T& value,
					const _ComparisonTag& = _ComparisonTag())
{ return fake_iterator<const _T, _ComparisonTag>(value); }

}}

#endif