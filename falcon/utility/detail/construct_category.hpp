#ifndef _UTILITY_DETAIL_CONSTRUCT_CATEGORY_HPP
#define _UTILITY_DETAIL_CONSTRUCT_CATEGORY_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
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

#ifdef __GXX_EXPERIMENTAL_CXX0X__
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
