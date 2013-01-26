#ifndef _FALCON_JAVA_ITERATOR_COUNTING_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_COUNTING_ITERATOR_HPP

#include <falcon/java_iterator/java_iterator_handler.hpp>

namespace falcon {
namespace java_iterator {

template <typename _Iterator,
	typename _Tp = use_default,
	typename _Reference = use_default>
class counting_iterator;

namespace detail {
	template <typename _Iterator, typename _Tp, typename _Reference>
	struct counting_base
	{
		typedef typename java_iterator_handler_types<
			counting_iterator<_Iterator, _Tp, _Reference>,
			_Iterator,
			use_default,
			_Tp,
			_Reference
		>::base base;
	};
}

template <typename _Iterator, typename _Tp, typename _Reference>
class counting_iterator
: public detail::counting_base<_Iterator, _Tp, _Reference>::base
{
	friend class java_iterator_core_access;

	typedef typename detail::counting_base<_Iterator, _Tp, _Reference>::base __base;

public:
	typedef _Iterator iterator_type;

private:
	int _n;

public:
	counting_iterator(iterator_type begin, int n)
	: __base(begin)
	, _n(n)
	{}

	counting_iterator(const counting_iterator& other)
	: __base(other.base_reference())
	, _n(other._n)
	{}

	counting_iterator& operator=(const counting_iterator& x)
	{
		__base::operator=(x);
		_n = x._n;
		return *this;
	}

	counting_iterator& operator=(const iterator_type& x)
	{
		__base::operator=(x);
		return *this;
	}

	void count(int n)
	{ _n = n; }

	int count() const
	{ return _n; }

protected:
	bool do_valid() const
	{ return _n; }

	void advance()
	{
		--_n;
		__base::advance();
	}

	void recoil()
	{
		++_n;
		__base::recoil();
	}
};

template <typename _Iterator>
counting_iterator<_Iterator> make_counting_iterator(_Iterator x, int n)
{ return counting_iterator<_Iterator>(x, n); }

}
}

#endif
