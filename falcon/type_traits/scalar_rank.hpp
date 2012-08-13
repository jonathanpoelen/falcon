#ifndef _FALCON_TYPE_TRAITS_SCALAR_RANK_HPP
#define _FALCON_TYPE_TRAITS_SCALAR_RANK_HPP

#include <cstddef>

namespace falcon {

template <typename _T>
struct scalar_rank;

template <std::size_t _Rank>
struct scalar_rank_to_type;

#define __MAKE_RANK(_Type, _Rank)\
	template <>\
	struct scalar_rank<_Type>\
	{\
		typedef _Type type;\
		static const std::size_t value = _Rank;\
	};\
	template <>\
	struct scalar_rank_to_type<_Rank>\
	{\
		typedef _Type type;\
		static const std::size_t value = _Rank;\
	};

__MAKE_RANK(char, 0)
__MAKE_RANK(short, 1)
__MAKE_RANK(int, 2)
__MAKE_RANK(long, 3)
__MAKE_RANK(long long, 4)

__MAKE_RANK(float, 5)
__MAKE_RANK(double, 6)
__MAKE_RANK(long double, 7)

#undef __MAKE_RANK

}

#endif
