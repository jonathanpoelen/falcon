#ifndef FALCON_ITERATOR_CONTAIN_RANGE_ACCESS_HPP
#define FALCON_ITERATOR_CONTAIN_RANGE_ACCESS_HPP

#include <falcon/container/range_access.hpp>

#if __cplusplus >= 201103L
# include <falcon/sfinae/function_is_callable.hpp>

namespace falcon {
	template <typename T>
	class contain_range_access_iterator
	{
    FALCON_FUNCTION_IS_CALLABLE_TRAIT_DEF(begin);

	public:
		static const bool value = begin_is_callable<T&>::value;
	};

	template <typename T>
	struct contain_range_access_reverse_iterator
	{
    FALCON_FUNCTION_IS_CALLABLE_TRAIT_DEF(rbegin);

	public:
    static const bool value = rbegin_is_callable<T&>::value;
	};
}

#else
#include <falcon/helper/has_type.hpp>

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
