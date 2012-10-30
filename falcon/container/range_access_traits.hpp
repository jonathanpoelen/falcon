#ifndef _FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP
#define _FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP

#include <falcon/container/range_access.hpp>

namespace falcon {

template<typename _Container, typename _Iterator = typename range_access_iterator<_Container>::type>
struct range_access_traits
{
	typedef _Container container_type;
	typedef _Iterator iterator;

	static iterator begin(_Container& cont)
	{ return falcon::begin(cont); }
	static iterator end(_Container& cont)
	{ return falcon::end(cont); }
};

// template<typename _Container, typename _Iterator = typename range_access_iterator<_Container>::type>
// struct const_range_access_traits
// {
// 	typedef _Container container_type;
// 	typedef _Iterator iterator;
//
// 	static iterator begin(const _Container& cont)
// 	{ return falcon::begin(cont); }
// 	static iterator end(const _Container& cont)
// 	{ return falcon::end(cont); }
// };
//
// template<typename _Container, typename _Iterator>
// struct range_access_traits<const _Container, _Iterator>
// : const_range_access_traits<const _Container, _Iterator>
// {};

template<typename _Container, typename _Iterator = typename range_access_reverse_iterator<_Container>::type>
struct reverse_range_access_traits
{
	typedef _Container container_type;
	typedef _Iterator iterator;

	static iterator begin(_Container& cont)
	{ return falcon::rbegin(cont); }
	static iterator end(_Container& cont)
	{ return falcon::rend(cont); }
};

// template<typename _Container, typename _Iterator = typename range_access_reverse_iterator<_Container>::type>
// struct const_reverse_range_access_traits
// {
// 	typedef _Container container_type;
// 	typedef _Iterator iterator;
//
// 	static iterator begin(const _Container& cont)
// 	{ return falcon::rbegin(cont); }
// 	static iterator end(const _Container& cont)
// 	{ return falcon::rend(cont); }
// };
//
// template<typename _Container, typename _Iterator>
// struct reverse_range_access_traits<const _Container, _Iterator>
// : const_reverse_range_access_traits<const _Container, _Iterator>
// {};

}

#endif