#ifndef FALCON_CONTAINER_ZONE_ACCESS_HPP
#define FALCON_CONTAINER_ZONE_ACCESS_HPP

#include <falcon/container/range_access_traits.hpp>
#include <falcon/iterator/zone_iterator.hpp>

namespace falcon {

template<typename _Container, typename _Access = range_access_traits<_Container> >
struct zone_access
{
private:
	typedef typename _Access::iterator __sub_iterator;
	typedef std::iterator_traits<__sub_iterator> __traits;

public:
	typedef typename __traits::difference_type difference_type;
	typedef difference_type size_t;

	typedef falcon::iterator::zone_iterator<__sub_iterator> iterator;

	size_t width_container;
	size_t x;
	size_t y;
	size_t width_zone;
	size_t height_zone;
	_Access access;

	constexpr zone_access(size_t __width_container,
												size_t __x, size_t __y,
												size_t __width_zone,
												size_t __height_zone,
												_Access __access = _Access())
	: width_container(__width_container)
	, x(__x)
	, y(__y)
	, width_zone(__width_zone)
	, height_zone(__height_zone)
	, access(__access)
	{}

	iterator begin(_Container& cont) const
	{
		return iterator(
			access.begin(cont) + (y * width_container + x),
			width_container,
			width_zone
		);
	}

	iterator end(_Container& cont) const
	{
		return iterator(
			access.begin(cont) + ((y + height_zone) * width_container) + x,
			width_container,
			width_zone
		);
	}
};

}

#endif