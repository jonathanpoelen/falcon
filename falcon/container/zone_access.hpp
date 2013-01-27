#ifndef FALCON_CONTAINER_ZONE_ACCESS_HPP
#define FALCON_CONTAINER_ZONE_ACCESS_HPP

#include <falcon/container/range_access_traits.hpp>
#include <falcon/iterator/nexter_iterator.hpp>

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

private:
	struct __nexter
	{
		__sub_iterator end;
		size_t n, step;

		__nexter()
		{}

		__nexter(__sub_iterator __end, size_t __n, size_t __step)
		: end(__end)
		, n(__n)
		, step(__step)
		{}

		void operator()(__sub_iterator& it)
		{
			if (it == end)
			{
				it = end + step;
				end = it + n;
			}
			else
				++it;
		}

		void operator()(__sub_iterator& it, difference_type __n)
		{
			difference_type d = end - it;
			if (__n > d)
			{
				__n -= d;
				it = end + n + (__n / (n + 1)) * step + __n % (n + 1);
				end += (__n / (n + 1) + 1) * step + n;
			}
			else
				it += __n;
		}
	};

public:
	typedef falcon::iterator::nexter_iterator<__sub_iterator, __nexter> iterator;

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
			__nexter(
				access.begin(cont) + (y * width_container + x + height_zone - 1),
				width_zone - 1,
				width_container - width_zone + 1
			)
		);
	}

	iterator end(_Container& cont) const
	{
		return iterator(access.begin(cont) + ((y + height_zone) * width_container) + x);
	}
};

}

#endif