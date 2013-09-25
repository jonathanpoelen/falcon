#ifndef _FALCON_UTILITY_ISTRUE_OR_FALSE_HPP
#define _FALCON_UTILITY_ISTRUE_OR_FALSE_HPP

namespace falcon {
template<typename T>
inline bool is_true(const T& a)
{
	return a ? true : false;
}

template<typename T>
inline bool is_false(const T& a)
{
	return !is_true(a);
}

struct is_true_wrapper
{
	template <typename T>
	inline bool operator()(const T& a)
	{
		return is_true(a);
	}
};

struct is_false_wrapper
{
	template <typename T>
	inline bool operator()(const T& a)
	{
		return is_false(a);
	}
};
}

#endif
