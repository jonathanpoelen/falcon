#ifndef _FALCON_UTILITY_IS_TRUE_OR_FALSE_HPP
#define _FALCON_UTILITY_IS_TRUE_OR_FALSE_HPP

namespace falcon {
template<typename _T>
inline bool is_true(const _T& a)
{
	return static_cast<bool>(a);
}

template<typename _T>
inline bool is_false(const _T& a)
{
	return !is_true<>(a);
}

struct is_true_wrapper
{
	template <typename _T>
	inline bool operator()(const _T& a)
	{
		return is_true(a);
	}
};

struct is_false_wrapper
{
	template <typename _T>
	inline bool operator()(const _T& a)
	{
		return is_false(a);
	}
};
}

#endif
