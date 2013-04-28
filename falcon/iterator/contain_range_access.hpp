#ifndef _FALCON_ITERATOR_CONTAIN_RANGE_ACCESS_HPP
#define _FALCON_ITERATOR_CONTAIN_RANGE_ACCESS_HPP

#include <falcon/container/range_access.hpp>

#if __cplusplus >= 201103L
# include <falcon/sfinae/function_is_call_possible.hpp>

namespace falcon {
	template <typename _T>
	class contain_range_access_iterator
	{
		FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(begin);

	public:
		static const bool value = FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(begin)<_T&>::value;
	};

	template <typename _T>
	struct contain_range_access_reverse_iterator
	{
		FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(rbegin);

	public:
		static const bool value = FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(rbegin)<_T&>::value;
	};
}

#else
#include <falcon/helper/has_type_helper.hpp>

namespace falcon {
	template <typename _T>
	struct contain_range_access_iterator
	: helper::has_type_helper<range_access_iterator<_T> >
	{};

	template <typename _T>
	struct contain_range_access_reverse_iterator
	: helper::has_type_helper<range_access_reverse_iterator<_T> >
	{};
}

#endif

#endif