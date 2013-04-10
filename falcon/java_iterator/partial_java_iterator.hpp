#ifndef _FALCON_JAVA_ITERATOR_PARTIAL_JAVA_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_PARTIAL_JAVA_ITERATOR_HPP

#include <falcon/c++0x/keywords.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/java_iterator/detail/iterator_traits.hpp>

namespace falcon {

namespace java_iterator {

template <typename _Iterator>
class partial_java_iterator
{
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _Iterator iterator;
	typedef typename iterator_traits::value_type value_type;
	//typedef typename iterator_traits::pointer pointer;
	typedef iterator pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

protected:
	iterator _it;

	typedef partial_java_iterator<_Iterator> self_type;

#if __cplusplus > 201100L
	template<typename... _Args>
	partial_java_iterator(_Args&&... args)
	: _it(std::forward<_Args>(args)...)
	{}
#endif

public:
	partial_java_iterator(const iterator& begin)
	: _it(begin)
	{}

	partial_java_iterator(const self_type& other)
	: _it(other._it)
	{}

	self_type& operator=(const self_type& other)
	{
		_it = other._it;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		_it = it;
		return *this;
	}

	const reference& current() const
	{ return *_it; }

	reference& current()
	{ return *_it; }

	const iterator& current_iterator() const
	{ return _it; }

	iterator& current_iterator()
	{ return _it; }

	void current_iterator(const iterator& it)
	{ _it = it; }

	reference operator*()
	{ return current(); }

	pointer operator->()
	{ return _it.operator->(); }

	reference next()
	{
		reference r = *_it;
		++_it;
		return r;
	}

	reference prev()
	{
		reference r = *_it;
		--_it;
		return r;
	}

	bool operator==(const self_type& other) const
	{ return _it == other._it; }

	bool operator<(const self_type& other) const
	{ return _it < other._it; }

	FALCON_MEMBER_COMPARISON_OTHER_OPERATOR(self_type)
};

}

}

#endif