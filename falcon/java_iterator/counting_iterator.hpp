#ifndef _FALCON_JAVA_ITERATOR_COUNTING_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_COUNTING_ITERATOR_HPP

#include <falcon/c++/cast.hpp>
#include <falcon/java_iterator/partial_java_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

namespace java_iterator {

template <typename _Iterator>
class counting_iterator
	: partial_java_iterator<_Iterator>
{
	typedef counting_iterator<_Iterator> self_type;
	typedef partial_java_iterator<_Iterator> base_type;

public:
	typedef _Iterator iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;

private:
	int _n;

public:
	counting_iterator(const iterator& begin, int n)
		: base_type(begin)
		, _n(n)
	{}

	counting_iterator(const self_type& other)
		: base_type(other._it)
		, _n(other._n)
	{}

	self_type& operator=(const iterator& it)
	{
		base_type::operator=(it);
		return *this;
	}

	int& count()
	{
		return _n;
	}

	const int& count() const
	{
		return _n;
	}

	bool valid() const
	{
		return _n;
	}

	reference next()
	{
		reference r = *base_type::_it;
		++*this;
		return r;
	}
	reference prev()
	{
		reference r = *base_type::_it;
		--*this;
		return r;
	}

	FALCON_MEMBER_INCREMENT(self_type, --_n; ++base_type::_it)
	FALCON_MEMBER_DECREMENT(self_type, ++_n; --base_type::_it)

	CPP_EXPLICIT_BOOL_CAST(valid())
};

template <typename _Container, typename _Iterator = typename _Container::iterator>
counting_iterator<_Iterator> make_counting_iterator(_Container& c, int n) {
	return counting_iterator<_Iterator>(begin(c), n);
}

template <typename _Iterator>
counting_iterator<_Iterator> make_counting_iterator(const _Iterator& it, int n) {
	return counting_iterator<_Iterator>(it, n);
}

}

template <typename _Iterator>
struct is_java_iterator<java_iterator::counting_iterator<_Iterator> >
		: true_type
	{};

}

#endif
