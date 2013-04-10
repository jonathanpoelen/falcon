#ifndef _FALCON_FUNCTIONAL_CONVERTER_HPP
#define _FALCON_FUNCTIONAL_CONVERTER_HPP

#if __cplusplus > 201100L
# include <type_traits>
#endif

#include <falcon/functional/late_parameter.hpp>

namespace falcon {

template<typename _To, typename _From = late_parameter_t>
struct converter
{
	inline constexpr _To operator()(const _From& a) const
	{
		return static_cast<_To>(a);
	}

	inline constexpr _To operator()(_From& a) const
	{
		return static_cast<_To>(a);
	}

#if __cplusplus > 201100L
	inline constexpr _To operator()(_From&& a) const
	{
		return static_cast<_To>(a);
	}
#endif
};

template<typename _To>
struct converter<_To, late_parameter_t>
{
	template<typename _From>
	inline constexpr _To operator()(const _From& a) const
	{
		return static_cast<_To>(a);
	}

#if __cplusplus > 201100L
	template<typename _From>
	inline constexpr typename std::enable_if<std::is_lvalue_reference<_From>::value, _To>::type operator()(_From& a) const
	{
		return static_cast<_To>(a);
	}

	template<typename _From>
	inline constexpr typename std::enable_if<std::is_rvalue_reference<_From>::value, _To>::type operator()(_From&& a) const
	{
		return static_cast<_To>(a);
	}
#else
	template<typename _From>
	inline constexpr _To operator()(_From& a) const
	{
		return static_cast<_To>(a);
	}
#endif
};

}

#endif