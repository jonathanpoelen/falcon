#ifndef _FALCON_JAVA_ITERATOR_UNTIL_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_UNTIL_ITERATOR_HPP

#include <falcon/c++/cast.hpp>
#include <falcon/java_iterator/partial_java_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

namespace java_iterator {

template <typename _Iterator>
class until_iterator
: public partial_java_iterator<_Iterator>
{
	typedef until_iterator<_Iterator> self_type;
	typedef partial_java_iterator<_Iterator> base_type;

public:
	typedef _Iterator iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;

private:
	value_type _stop;

public:
	until_iterator(const iterator& begin, const value_type& __stop)
	: base_type(begin)
	, _stop(__stop)
	{}

	until_iterator(const iterator& begin)
	: base_type(begin)
	, _stop()
	{}

	template <typename _Container>
	until_iterator(_Container& container, const value_type& __stop)
	: base_type(falcon::begin(container))
	, _stop(__stop)
	{}

	until_iterator(const self_type& other)
	: base_type(other._it)
	, _stop(other._stop)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::current(other._it);
		_stop = other._stop;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		base_type::operator=(it);
		return *this;
	}

	const iterator& stop() const
	{ return _stop; }

	void stop(const iterator& value)
	{ _stop = value; }

	bool valid() const
	{ return *base_type::_it != _stop; }

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

template <typename _Container, typename _Iterator = typename _Container::iterator, typename _Value = typename _Iterator::value_type>
until_iterator<_Iterator> make_until_iterator(_Container& c,  const _Value& stop) {
	return until_iterator<_Iterator>(c, stop);
}

template <typename _Iterator, typename _Value = typename _Iterator::value_type>
until_iterator<_Iterator> make_until_iterator(const _Iterator& begin,  const _Value& stop) {
	return until_iterator<_Iterator>(begin, stop);
}

}

template <typename _Iterator>
struct is_java_iterator<java_iterator::until_iterator<_Iterator> >
: true_type
{};

}

#endif