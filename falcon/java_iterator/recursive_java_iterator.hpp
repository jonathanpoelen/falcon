#ifndef _FALCON_JAVA_ITERATOR_RECURSIVE_JAVA_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_RECURSIVE_JAVA_ITERATOR_HPP

#include <falcon/java_iterator/partial_java_iterator.hpp>
#include <falcon/c++/cast.hpp>
#include <falcon/iterator/recursive_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>

namespace falcon {
namespace java_iterator {

template <typename _RecursiveIterator, typename _Iterator>
class recursive_java_iterator
: public partial_java_iterator<_RecursiveIterator>
{
	typedef recursive_java_iterator<_Iterator, _Iterator> self_type;
	typedef partial_java_iterator<_RecursiveIterator> base_type;

public:
	typedef _RecursiveIterator recursive_iterator;
	typedef _Iterator iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;

private:
	iterator _end;

public:
	recursive_java_iterator(const recursive_iterator& first, const iterator& last)
	: base_type(first)
	, _end(last)
	{}

	template <typename _Container>
	recursive_java_iterator(_Container& container)
	: base_type(container)
	, _end(falcon::end(container))
	{}

	template<typename _IteratorForRecursiveIterator, typename _IteratorForEnd>
	recursive_java_iterator(_IteratorForRecursiveIterator first, _IteratorForRecursiveIterator last, _IteratorForRecursiveIterator __end)
	: base_type(first, last)
	, _end(__end)
	{}

	recursive_java_iterator(const self_type& other)
	: base_type(other._it)
	, _end(other._end)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::current(other._it);
		_end = other._end;
		return *this;
	}

	self_type& operator=(const recursive_iterator& it)
	{
		base_type::operator=(it);
		return *this;
	}

	const iterator& end() const
	{ return _end; }

	void end(const iterator& __end)
	{ _end = __end; }

	const recursive_iterator& begin() const
	{ return base_type::_it; }

	template<typename _IteratorForRecursiveIterator>
	void begin(const _IteratorForRecursiveIterator& first)
	{ base_type::_it.begin(first); }

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

	bool operator==(const iterator& other) const
	{ return base_type::_it == other; }

	bool operator<(const iterator& other) const
	{ return base_type::_it < other; }
};

template<bool _Protect, std::size_t _Dimension, typename _Iterator, typename _CompareIterator = _Iterator>
struct __recursive_java_iterator_info
{
	typedef recursive_java_iterator<typename iterator::__recursive_iterator_info<true, _Dimension, _Iterator>::type, _CompareIterator> type;
};

template<std::size_t _Dimension, typename _Container>
typename __recursive_java_iterator_info<true, _Dimension, typename range_access_iterator<_Container>::type>::type make_recursive_java_iterator(_Container& c) {
	return typename __recursive_java_iterator_info<true, _Dimension, typename range_access_iterator<_Container>::type>::type(c);
}

template<typename _Container>
typename __recursive_java_iterator_info<true, dimension<_Container>::value, typename range_access_iterator<_Container>::type>::type make_recursive_java_iterator(_Container& c) {
	return typename __recursive_java_iterator_info<true, dimension<_Container>::value, typename range_access_iterator<_Container>::type>::type(c);
}

}
}

#endif