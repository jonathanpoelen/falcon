#ifndef FALCON_CONTAINER_ZONE_ACCESS_HPP
#define FALCON_CONTAINER_ZONE_ACCESS_HPP

#include <falcon/container/range_access_traits.hpp>
#include <falcon/iterator/zone_iterator.hpp>

namespace falcon {

template<class Container, class Access = range_access_traits<Container> >
struct zone_access
{
private:
	typedef typename Access::iterator sub_iterator;
	typedef std::iterator_traits<sub_iterator> traits;

public:
	typedef typename traits::difference_type difference_type;
	typedef difference_type size_t;

	typedef falcon::iterator::zone_iterator<sub_iterator> iterator;

	size_t width_container_;
	size_t x_;
	size_t y_;
	size_t width_zone_;
	size_t height_zone_;
	Access access_;

	constexpr zone_access(size_t width_container,
												size_t x, size_t y,
												size_t width_zone,
												size_t height_zone,
												Access access = Access())
	: width_container_(width_container)
	, x_(x)
	, y_(y)
	, width_zone_(width_zone)
	, height_zone_(height_zone)
	, access_(access)
	{}

	iterator begin(Container& cont) const
	{
		return iterator( access_.begin(cont) + (y_ * width_container_ + x_)
                   , width_container_
                   , width_zone_);
	}

	iterator end(Container& cont) const
	{
		return iterator( access_.begin(cont) + ((y_ + height_zone_) * width_container_) + x_
                   , width_container_
                   , width_zone_);
	}
};

}

#endif
