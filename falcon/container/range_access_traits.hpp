#ifndef _FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP
#define _FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP

#include <falcon/container/range_access.hpp>

namespace falcon {

template<typename _Container, typename _ToIterator,
	typename _Iterator = typename range_access_iterator<_Container>::type>
struct __range_access_traits
{
	static _ToIterator begin(_Container& cont)
	{ return _ToIterator(falcon::begin(cont)); }
	static _ToIterator end(_Container& cont)
	{ return _ToIterator(falcon::end(cont)); }
};

template<typename _Container, typename _ToIterator>
struct __range_access_traits<_Container, _ToIterator, _ToIterator>
{
	static _ToIterator begin(_Container& cont)
	{ return falcon::begin(cont); }
	static _ToIterator end(_Container& cont)
	{ return falcon::end(cont); }
};

template<typename _Container, typename _Iterator = typename range_access_iterator<_Container>::type>
struct range_access_traits
{
	typedef _Container container_type;
	typedef _Iterator iterator;

	static iterator begin(container_type& cont)
	{ return __range_access_traits<_Container, _Iterator>::begin(cont); }
	static iterator end(container_type& cont)
	{ return __range_access_traits<_Container, _Iterator>::end(cont); }
};


template<typename _Container, typename _ToIterator,
	typename _Iterator = typename range_access_reverse_iterator<_Container>::type>
struct __reverse_range_access_traits
{
	static _ToIterator begin(_Container& cont)
	{ return _ToIterator(rbegin(cont)); }
	static _ToIterator end(_Container& cont)
	{ return _ToIterator(rend(cont)); }
};

template<typename _Container, typename _ToIterator>
struct __reverse_range_access_traits<_Container, _ToIterator, _ToIterator>
{
	static _ToIterator begin(_Container& cont)
	{ return rbegin(cont); }
	static _ToIterator end(_Container& cont)
	{ return rend(cont); }
};

template<typename _Container, typename _Iterator = typename range_access_reverse_iterator<_Container>::type>
struct reverse_range_access_traits
{
	typedef _Container container_type;
	typedef _Iterator iterator;

	static iterator begin(container_type& cont)
	{ return __reverse_range_access_traits<_Container, _Iterator>::begin(cont); }
	static iterator end(container_type& cont)
	{ return __reverse_range_access_traits<_Container, _Iterator>::end(cont); }
};

}

#endif