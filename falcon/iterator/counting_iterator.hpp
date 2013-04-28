#ifndef FALCON_ITERATOR_COUNTING_ITERATOR_HPP
#define FALCON_ITERATOR_COUNTING_ITERATOR_HPP

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <boost/type_traits/remove_pointer.hpp>
#endif
#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

struct count_comparison_tag {};
struct count_and_iterator_comparison_tag {};

template <typename _Iterator, typename _ComparisonTag = count_comparison_tag,
	typename _Tp = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default>
class counting_iterator;

namespace detail {

	template <typename _Iterator, typename _ComparisonTag,
		typename _Tp,
		typename _Category,
		typename _Reference,
		typename _Distance,
		typename _Pointer>
	struct __counting_base
	{
		typedef typename iterator_handler_types<
			counting_iterator<_Iterator, _ComparisonTag, _Tp,
				_Category, _Reference, _Distance, _Pointer>,
			_Iterator,
			_Category,
			_Tp,
			_Distance,
			_Pointer,
			_Reference
		>::base base;
	};

}

template <typename _Iterator, typename _ComparisonTag,
	typename _Tp,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class counting_iterator
: public detail::__counting_base<_Iterator, _ComparisonTag, _Tp, _Category, _Reference, _Distance, _Pointer>::base
{
	friend class iterator_core_access;

	typedef typename detail::__counting_base<
		_Iterator, _ComparisonTag, _Tp, _Category, _Reference, _Distance, _Pointer
	>::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;

private:
	int _count;

public:
	explicit counting_iterator(int __count = 0)
	: __base()
	, _count(__count)
	{}

	explicit counting_iterator(iterator_type x, int __count = 0)
	: __base(x)
	, _count(__count)
	{}

	counting_iterator(int __count, iterator_type x)
	: __base(x)
	, _count(__count)
	{}

	counting_iterator(const counting_iterator& other)
	: __base(other)
	, _count(other._count)
	{}

	using __base::operator=;
#if __cplusplus >= 201103L
	counting_iterator& operator=(const counting_iterator&) = default;
#else
	counting_iterator& operator=(const counting_iterator& other)
	{
		this->base_reference() = other.base_reference();
		_count = other._count;
		return *this;
	}
#endif

	void count(int __count)
	{ _count = __count; }

	int count() const
	{ return _count; }

private:
	void increment()
	{
		__base::increment();
		++_count;
	}

	void decrement()
	{
		__base::decrement();
		--_count;
	}

	difference_type _dispath_difference(const counting_iterator& other,
																			count_comparison_tag) const
	{ return other._count - _count; }

	difference_type _dispath_difference(const counting_iterator& other,
																			count_and_iterator_comparison_tag) const
	{ return std::min(other._count - _count, __base::difference(other)); }

	difference_type difference(const counting_iterator& other) const
	{ return _dispath_difference(other, _ComparisonTag()); }

	bool _dispath_equal(const counting_iterator&, count_comparison_tag) const
	{ return false; }

	bool _dispath_equal(const counting_iterator& other,
											count_and_iterator_comparison_tag) const
	{ return __base::equal(other); }

	bool equal(const counting_iterator& other) const
	{ return _count == other._count || _dispath_equal(other, _ComparisonTag()); }

	bool _dispath_less(const counting_iterator&, count_comparison_tag) const
	{ return true; }

	bool _dispath_less(const counting_iterator& other, count_and_iterator_comparison_tag) const
	{ return __base::less(other); }

	bool less(const counting_iterator& other) const
	{ return _count < other._count && _dispath_less(other, _ComparisonTag()); }
};


template <typename _Iterator>
counting_iterator<_Iterator>
make_counting_iterator(int count, _Iterator x)
{ return counting_iterator<_Iterator>(x, count); }

template <typename _Iterator>
counting_iterator<_Iterator>
make_counting_iterator(_Iterator x, int count = 0)
{ return counting_iterator<_Iterator>(x, count); }

template <typename _Iterator, typename _ComparisonTag>
counting_iterator<_Iterator>
make_counting_iterator(int count, _Iterator x, _ComparisonTag)
{ return counting_iterator<_Iterator, _ComparisonTag>(x, count); }

template <typename _Iterator, typename _ComparisonTag>
counting_iterator<_Iterator>
make_counting_iterator(_Iterator x, int count, _ComparisonTag)
{ return counting_iterator<_Iterator, _ComparisonTag>(x, count); }

template <typename _Iterator>
counting_iterator<_Iterator, count_comparison_tag>
make_counting_iterator(_Iterator x, count_comparison_tag)
{ return counting_iterator<_Iterator, count_comparison_tag>(x); }

template <typename _Iterator>
counting_iterator<_Iterator, count_and_iterator_comparison_tag>
make_counting_iterator(_Iterator x, count_and_iterator_comparison_tag)
{ return counting_iterator<_Iterator, count_and_iterator_comparison_tag>(x); }

}}

#endif