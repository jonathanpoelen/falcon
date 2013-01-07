#ifndef FALCON_STRING_CONCAT_HPP
#define FALCON_STRING_CONCAT_HPP

#include <falcon/string/append.hpp>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
#endif

namespace falcon {

	template<typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const std::basic_string<_CharT, _Traits, _Alloc>& rhs)
	{ return lhs + rhs; }

	template<typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const basic_cstring<_CharT, _Traits>& rhs)
	{ return lhs + rhs; }

	template<typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const basic_cstring<_CharT, _Traits>& lhs,
				 const std::basic_string<_CharT, _Traits, _Alloc>& rhs)
	{ return lhs + rhs; }

	template<typename _CharT, typename _Traits>
	inline std::basic_string<_CharT, _Traits>
	concat(const basic_cstring<_CharT, _Traits>& lhs,
				 const basic_cstring<_CharT, _Traits>& rhs)
	{ return lhs + rhs; }

	template<typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const basic_cstring<_CharT, _Traits>& lhs,
				 const basic_cstring<_CharT, _Traits>& rhs,
				 const _Alloc& allocator)
	{
		std::basic_string<_CharT, _Traits, _Alloc> str;
		str.reserve(rhs.size() + lhs.size());
		return append(append(str, lhs), rhs);
	}

	template<std::size_t _N, typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _CharT (& rhs)[_N])
	{
		std::basic_string<_CharT, _Traits, _Alloc> str(lhs);
		return str.append(rhs, _N-1);
	}

	template<std::size_t _N, typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const basic_cstring<_CharT, _Traits>& lhs,
				 const _CharT (& rhs)[_N])
	{
		std::basic_string<_CharT, _Traits, _Alloc> str;
		str.reserve(_N-1 + lhs.size());
		return append(append(str, lhs), rhs);
	}

	template<std::size_t _N, typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const _CharT (& lhs)[_N],
				 const std::basic_string<_CharT, _Traits, _Alloc>& rhs)
	{
		std::basic_string<_CharT, _Traits, _Alloc> str;
		str.reserve(_N-1 + rhs.size());
		return append(append(str, lhs), rhs);
	}

	template<std::size_t _N, typename _CharT, typename _Traits>
	inline std::basic_string<_CharT, _Traits>
	concat(const _CharT (& lhs)[_N],
				 const basic_cstring<_CharT, _Traits>& rhs)
	{
		std::basic_string<_CharT, _Traits> str;
		str.reserve(_N-1 + rhs.size());
		return append(append(str, lhs), rhs);
	}

	template<std::size_t _N, typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const _CharT (& lhs)[_N],
				 const basic_cstring<_CharT, _Traits>& rhs,
				 const _Alloc& allocator)
	{
		std::basic_string<_CharT, _Traits, _Alloc> str(allocator);
		str.reserve(_N-1 + rhs.size());
		return append(append(str, lhs), rhs);
	}

	template<std::size_t _N, std::size_t _N2, typename _CharT>
	inline std::basic_string<_CharT>
	concat(const _CharT (& lhs)[_N],
				 const _CharT (& rhs)[_N2])
	{
		std::basic_string<_CharT> str;
		str.reserve(_N-1 + _N2-1);
		return append(append(str, lhs), rhs);
	}

	template<std::size_t _N, std::size_t _N2, typename _CharT, typename _Alloc>
	inline std::basic_string<_CharT, std::char_traits<_CharT>, _Alloc>
	concat(const _CharT (& lhs)[_N],
				 const _CharT (& rhs)[_N2],
				 const _Alloc& allocator)
	{
		std::basic_string<_CharT, std::char_traits<_CharT>, _Alloc> str(allocator);
		str.reserve(_N-1 + _N2-1);
		return append(append(str, lhs), rhs);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _Elements,
		typename _CharT = void, typename _Traits = void, typename _Alloc = void,
		typename B1 = std::true_type,
		typename B2 = std::true_type,
		typename B3 = std::true_type>
	struct __build_string;

	template<typename _CharT, typename _Traits, typename _Alloc, typename... _Elements,
		typename _CharT2, typename _Traits2, typename _Alloc2>
	struct __build_string<
		parameter_pack<std::basic_string<_CharT, _Traits, _Alloc>, _Elements...>,
		_CharT2, _Traits2, _Alloc2,
		std::true_type, std::true_type, std::true_type
	>
	: __build_string<parameter_pack<_Elements...>, _CharT, _Traits, _Alloc,
		std::integral_constant<bool,
			std::is_void<_CharT2>::value || std::is_same<_CharT, _CharT2>::value
		>,
		std::integral_constant<bool,
			std::is_void<_Traits2>::value || std::is_same<_Traits, _Traits2>::value
		>,
		std::integral_constant<bool,
			std::is_void<_Alloc2>::value || std::is_same<_Alloc, _Alloc2>::value
		>
	>
	{};

	template<typename _CharT, typename _Traits, typename... _Elements,
		typename _CharT2, typename _Traits2, typename _Alloc2>
	struct __build_string<
		parameter_pack<basic_cstring<_CharT, _Traits>, _Elements...>,
		_CharT2, _Traits2, _Alloc2,
		std::true_type, std::true_type, std::true_type
	>
	: __build_string<parameter_pack<_Elements...>, _CharT2, _Traits2, _Alloc2,
		std::integral_constant<bool,
			std::is_void<_CharT2>::value || std::is_same<_CharT, _CharT2>::value
		>,
		std::integral_constant<bool,
			std::is_void<_Traits2>::value || std::is_same<_Traits, _Traits2>::value
		>,
		std::true_type
	>
	{};

	template<typename _CharT, typename _Traits, typename... _Elements,
		typename _CharT2, typename _Traits2, typename _Alloc2>
	struct __build_string<
		parameter_pack<basic_cstring<const _CharT, _Traits>, _Elements...>,
		_CharT2, _Traits2, _Alloc2,
		std::true_type, std::true_type, std::true_type
	>
	: __build_string<parameter_pack<_Elements...>, _CharT2, _Traits2, _Alloc2,
		std::integral_constant<bool,
			std::is_void<_CharT2>::value || std::is_same<_CharT, _CharT2>::value
		>,
		std::integral_constant<bool,
			std::is_void<_Traits2>::value || std::is_same<_Traits, _Traits2>::value
		>,
		std::true_type
	>
	{};

	template<typename _CharT, typename... _Elements,
		typename _CharT2, typename _Traits2, typename _Alloc2>
	struct __build_string<
		parameter_pack<_CharT*, _Elements...>,
		_CharT2, _Traits2, _Alloc2,
		std::true_type, std::true_type, std::true_type
	>
	: __build_string<parameter_pack<_Elements...>, _CharT2, _Traits2, _Alloc2,
		std::integral_constant<bool,
			std::is_void<_CharT2>::value || std::is_same<_CharT, _CharT2>::value
		>,
		std::true_type,
		std::true_type>
	{};

	template<std::size_t _N, typename _CharT, typename... _Elements,
		typename _CharT2, typename _Traits2, typename _Alloc2>
	struct __build_string<
		parameter_pack<_CharT[_N], _Elements...>,
		_CharT2, _Traits2, _Alloc2,
		std::true_type, std::true_type, std::true_type
	>
	: __build_string<parameter_pack<_Elements...>, _CharT2, _Traits2, _Alloc2,
		std::integral_constant<bool,
			std::is_void<_CharT2>::value || std::is_same<_CharT, _CharT2>::value
		>,
		std::true_type,
		std::true_type>
	{};

	template<typename _CharT, typename _Traits, typename _Alloc>
	struct __build_string<parameter_pack<>, _CharT, _Traits, _Alloc>
	{ typedef std::basic_string<_CharT, _Traits, _Alloc> __type; };

	template<typename _StringL, typename _StringR, typename _StringR2, typename... _Strings>
	typename __build_string<parameter_pack<_StringL, _StringR, _StringR2, _Strings...>>::__type
	concat(const _StringL& lhs, const _StringR& rhs, const _StringR2& rhs2, const _Strings&... other)
	{
		typename __build_string<parameter_pack<_StringL, _StringR, _StringR2, _Strings...>>::__type str;
		return append(str, lhs, rhs, rhs2, other...);
	}
#endif

}

#endif