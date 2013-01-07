#ifndef FALCON_STRING_APPEND_HPP
#define FALCON_STRING_APPEND_HPP

#include <iosfwd>
#include <falcon/string/cstringfwd.hpp>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <falcon/parameter/parameter_pack.hpp>
#endif

namespace falcon {

	template<typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const std::basic_string<_CharT, _Traits, _Alloc>& rhs)
	{ return lhs += rhs; }

	template<typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const basic_cstring<_CharT, _Traits>& rhs)
	{ return lhs += rhs; }

	template<typename _CharT, typename _Traits>
	inline std::basic_string<_CharT, _Traits>
	append(std::basic_string<_CharT, _Traits>& lhs,
				 const _CharT * rhs)
	{ return lhs += rhs; }

	template<std::size_t _N, typename _CharT, typename _Traits>
	inline std::basic_string<_CharT, _Traits>
	append(std::basic_string<_CharT, _Traits>& lhs,
				 const _CharT (& rhs)[_N])
	{ return lhs.append(rhs, _N-1); }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<std::size_t _N>
	struct __keep_strlen
	{
		std::size_t array[_N];
		std::size_t * p = &array[0];

		void reset()
		{ p = &array[0]; }
	};

	template<>
	struct __keep_strlen<0>
	{
		void reset()
		{}
	};

	template <std::size_t _N, typename _Elements>
	struct __build_keep_strlen;

	template <std::size_t _N, typename _T, typename... _Elements>
	struct __build_keep_strlen<_N, parameter_pack<_T, _Elements...>>
	: __build_keep_strlen<_N, parameter_pack<_Elements...>>
	{};

	template <std::size_t _N, typename _T, typename... _Elements>
	struct __build_keep_strlen<_N, parameter_pack<_T*, _Elements...>>
	: __build_keep_strlen<_N+1, parameter_pack<_Elements...>>
	{};

	template <std::size_t _N>
	struct __build_keep_strlen<_N, parameter_pack<>>
	{ typedef __keep_strlen<_N> __type; };

	template<typename _KeepLen, typename _S>
	void __reserve(_S& lhs, std::size_t n, _KeepLen&)
	{ lhs.reserve(lhs.size() + n); }

	template<typename _KeepLen, typename _S, typename _String, typename... _Strings>
	void __reserve(_S& lhs, std::size_t n, _KeepLen& k,
								 const _String& rhs, const _Strings&... other)
	{ __reserve(lhs, n + rhs.size(), k, other...); }

	template<typename _KeepLen, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __reserve(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								 std::size_t n, _KeepLen& k,
								 const _CharT * rhs, const _Strings&... other)
	{ __reserve(lhs, n + (*k.p++ = _Traits::length(rhs)), k, other...); }

	template<typename _KeepLen, std::size_t _N, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __reserve(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								 std::size_t n, _KeepLen& k,
								 const _CharT (&)[_N], const _Strings&... other)
	{ __reserve(lhs, n + _N, k, other...); }

	template<typename _KeepLen, typename _S>
	void __append(_S&, _KeepLen&)
	{}

	template<typename _KeepLen, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								_KeepLen& k,
							 const std::basic_string<_CharT, _Traits, _Alloc>& rhs,
							  const _Strings&... other)
	{
		lhs.append(rhs);
		__append(lhs, k, other...);
	}

	template<typename _KeepLen, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								_KeepLen& k,
								const basic_cstring<_CharT, _Traits>& rhs,
							  const _Strings&... other)
	{
		lhs.append(rhs.c_str(), rhs.size());
		__append(lhs, k, other...);
	}

	template<typename _KeepLen, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								_KeepLen& k,
							  const _CharT * rhs, const _Strings&... other)
	{
		lhs.append(rhs, *k.p++);
		__append(lhs, k, other...);
	}

	template<typename _KeepLen, std::size_t _N, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								_KeepLen& k,
							  const _CharT (& rhs)[_N], const _Strings&... other)
	{
		lhs.append(rhs, _N);
		__append(lhs, k, other...);
	}

	template<typename _CharT, typename _Traits, typename _Alloc, typename _String1, typename _String2, typename... _Strings>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _String1& rhs, const _String2& rhs2, const _Strings&... other)
	{
		typename __build_keep_strlen<0, parameter_pack<_String1, _String2, _Strings...>>::__type k;
		__reserve(lhs, 0, k, rhs, rhs2, other...);
		k.reset();
		__append(lhs, k, rhs, rhs2, other...);
		return lhs;
	}
#endif

}

#endif