#ifndef _UTILITY_DETAIL_CONSTRUCT_CATEGORY_HPP
#define _UTILITY_DETAIL_CONSTRUCT_CATEGORY_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
namespace std {
	template<typename, std::size_t>
	class array;
}
#endif

namespace falcon {
namespace detail {

struct normal_construct_tag {};

template<typename _Tag>
struct construct_category
{
	typedef normal_construct_tag type;
};

#if __cplusplus >= 201103L
struct initilizer_list_construct_tag {};

template<typename _T, std::size_t _N>
struct construct_category<std::array<_T, _N>>
{
	typedef initilizer_list_construct_tag type;
};
#endif

}
}

#endif
