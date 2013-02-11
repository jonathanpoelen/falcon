#ifndef FALCON_ITERATOR_OPPOSITE_DIRECTION_ITERATOR_HPP
#define FALCON_ITERATOR_OPPOSITE_DIRECTION_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename _T,
	typename _Tp = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default
>
class opposite_direction_iterator;

namespace detail {

	template <typename _Iterator, typename _Tp, typename _Category,
		typename _Reference, typename _Distance, typename _Pointer>
	struct opposite_direction_base
	{
		typedef typename iterator_handler_types<
			opposite_direction_iterator<_Iterator, _Tp,
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

template <typename _Iterator, typename _Tp, typename _Category,
	typename _Reference, typename _Distance, typename _Pointer
>
class opposite_direction_iterator
: public detail::opposite_direction_base<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base
{
	friend class iterator_core_access;

	typedef typename detail::opposite_direction_base<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;


public:
	opposite_direction_iterator()
	: __base()
	{}

	explicit opposite_direction_iterator(iterator_type __x)
	: __base(__x)
	{}

	opposite_direction_iterator(const opposite_direction_iterator& __x)
	: __base(__x)
	{}

	using __base::operator=;

protected:
	void increment()
	{ __base::decrement(); }

	void decrement()
	{ __base::increment(); }

	difference_type difference(const opposite_direction_iterator& x) const
	{ return x.__base::difference(*this); }

	void advance(difference_type n)
	{ __base::recoil(n); }

	void recoil(difference_type n)
	{ __base::advance(n); }
};

template <typename _Iterator>
opposite_direction_iterator<_Iterator>
make_opposite_direction_iterator(_Iterator x)
{ return opposite_direction_iterator<_Iterator>(x); }

}
}

#endif