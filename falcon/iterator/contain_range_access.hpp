#ifndef _FALCON_ITERATOR_CONTAIN_RANGE_ACCESS_HPP
#define _FALCON_ITERATOR_CONTAIN_RANGE_ACCESS_HPP

#include <falcon/container/range_access.hpp>

#if __cplusplus >= 201103L
# include <falcon/sfinae/function_is_call_possible.hpp>

namespace falcon {
	template <typename T>
	class contain_range_access_iterator
	{
		FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(begin);

	public:
		static const bool value = FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(begin)<T&>::value;
	};

	template <typename T>
	struct contain_range_access_reverse_iterator
	{
		FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(rbegin);

	public:
		static const bool value = FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(rbegin)<T&>::value;
	};
}

#else
#include <falcon/type_traits/has.hpp>

namespace falcon {
	template <typename T>
	struct contain_range_access_iterator
	: has_type<range_access_iterator<T> >
	{};

	template <typename T>
	struct contain_range_access_reverse_iterator
	: has_type<range_access_reverse_iterator<T> >
	{};
}

#endif

#endif
