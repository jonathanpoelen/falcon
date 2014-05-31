#ifndef fALCON_MEMOTY_CONSTRUCT_CATEGORY_HPP
#define fALCON_MEMOTY_CONSTRUCT_CATEGORY_HPP

#include <falcon/config.hpp>

#if __cplusplus <= 201103L
#include <type_traits>
namespace std {
	template<class, std::size_t>
	class array;
}

namespace falcon {

struct normal_ctor_tag {};
struct brace_init_tag {};
struct double_brace_init_tag {};
struct dispatch_index_tag {};

template<class T>
struct construct_category
: std::conditional<
  std::has_trivial_default_constructor<T>::value,
  brace_init_tag,
  normal_ctor_tag
>
{};

template<class T, std::size_t N>
struct construct_category<std::array<T, N>>
{
	typedef double_brace_init_tag type;
};

template<class T, std::size_t N>
struct construct_category<T[N]>
{
	typedef dispatch_index_tag type;
};

template<class T>
using construct_category_t = typename construct_category<T>::type;

}
#else
namespace falcon {
	struct normal_ctor_tag {};
	template<class T>
	struct construct_category
	{
		typedef normal_ctor_tag type;
	};
}
#endif

#endif
