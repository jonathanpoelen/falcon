#ifndef _FALCON_JAVA_ITERATOR_RANGE_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_RANGE_ITERATOR_HPP

#include <falcon/c++/cast.hpp>
#include <falcon/java_iterator/partial_java_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

namespace java_iterator {

template <typename _Iterator>
class range_iterator
: public partial_java_iterator<_Iterator>
{
	typedef range_iterator<_Iterator> self_type;
	typedef partial_java_iterator<_Iterator> base_type;

public:
	typedef _Iterator iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;

private:
	iterator _end;

public:
	range_iterator(const iterator& begin, const iterator& __end)
	: base_type(begin)
	, _end(__end)
	{}

	range_iterator(const iterator& begin)
	: base_type(begin)
	, _end()
	{}

	template <typename _Container>
	range_iterator(_Container& container)
	: base_type(falcon::begin(container))
	, _end(falcon::end(container))
	{}

	range_iterator(const self_type& other)
	: base_type(other._it)
	, _end(other._end)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::current(other._it);
		_end = other._end;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		base_type::operator=(it);
		return *this;
	}

	const iterator& end() const
	{ return _end; }

	void end(const iterator& __end)
	{ _end = __end; }

	bool valid() const
	{ return base_type::_it != _end; }

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

	FALCON_MEMBER_INCREMENT(self_type, ++base_type::_it)
	FALCON_MEMBER_DECREMENT(self_type, --base_type::_it)

	CPP_EXPLICIT_BOOL_CAST(valid())
};

template <typename _Container, typename _Iterator = typename _Container::iterator>
range_iterator<_Iterator> make_range_iterator(_Container& c) {
	return range_iterator<_Iterator>(c);
}

template <typename _Iterator>
range_iterator<_Iterator> make_range_iterator(const _Iterator& begin, const _Iterator& end) {
	return range_iterator<_Iterator>(begin, end);
}

}

template <typename _Iterator>
struct is_java_iterator<java_iterator::range_iterator<_Iterator> >
: true_type
{};

}

#endif