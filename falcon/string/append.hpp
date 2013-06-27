#ifndef FALCON_STRING_APPEND_HPP
#define FALCON_STRING_APPEND_HPP

#include <iosfwd>
#if __cplusplus >= 201103L
# include <falcon/parameter/parameter_pack.hpp>
# include <falcon/detail/string_size.hpp>
#else
# include <boost/type_traits/add_const.hpp>
#endif

namespace falcon {

	template<typename _CharT, typename _Traits, typename _Alloc, typename _T>
	inline std::basic_string<_CharT, _Traits, _Alloc>&
	append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _T& rhs)
	{ return lhs += rhs; }

	template<std::size_t _N, typename _CharT, typename _Traits, typename _Alloc>
	inline std::basic_string<_CharT, _Traits, _Alloc>&
	append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _CharT (& rhs)[_N])
	{
		if (_N)
			lhs.append(rhs, _N-1);
		return lhs;
	}

	template<typename _String, typename _T>
	inline _String& append(_String& lhs, const _T& rhs)
	{ return lhs += rhs; }

	template<std::size_t _N, typename _String>
	inline _String&
	append(_String& lhs,
#if __cplusplus >= 201103L
				 const typename _String::value_type (& rhs)[_N]
#else
				typename boost::add_const<typename _String::value_type>::type (& rhs)[_N]
#endif
	)
	{
		if (_N)
			lhs.append(rhs, _N-1);
		return lhs;
	}

#if __cplusplus >= 201103L
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

	template <std::size_t _N, typename _T, typename... _Elements>
	struct __build_keep_strlen<_N, parameter_pack<const _T*, _Elements...>>
	: __build_keep_strlen<_N+1, parameter_pack<_Elements...>>
	{};

	template <std::size_t _N>
	struct __build_keep_strlen<_N, parameter_pack<>>
	{ typedef __keep_strlen<_N> __type; };

	template<typename _KeepLen, typename _S>
	void __reserve(_S& lhs, std::size_t n, _KeepLen&)
	{ lhs.reserve(lhs.size() + n); }

	template<typename _String, typename _Traits = void>
	struct __reserve_size
	{
		template<typename _KeepLen>
		static std::size_t __impl(const _String& rhs, _KeepLen&)
		{ return detail::__string_size<_String>::size(rhs); }
		template<typename _KeepLen>
		static const _String& __mksize(const _String& rhs, _KeepLen&)
		{ return rhs; }
	};

	template<typename _CharT, typename _Traits>
	struct __reserve_size<_CharT*, _Traits>
	{
		template<typename _KeepLen>
		static std::size_t __impl(const _CharT* rhs, _KeepLen& k)
		{ return *k.p++ = _Traits::length(rhs); }
		template<typename _KeepLen>
		static auto __mksize(const _CharT* rhs, _KeepLen& k)
		-> decltype(*k.p++)
		{ return *k.p++; }
	};

	template<typename _KeepLen, typename _CharT, typename _Traits, typename _Alloc, typename _String, typename... _Strings>
	void __reserve(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								 std::size_t n, _KeepLen& k,
								 const _String& rhs, const _Strings&... other)
	{ __reserve(lhs, n + __reserve_size<_String, _Traits>::__impl(rhs, k), k, other...); }

	template<typename _KeepLen, std::size_t _N, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __reserve(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								 std::size_t n, _KeepLen& k,
								const _CharT (&)[_N], const _Strings&... other)
	{ __reserve(lhs, n + (_N?_N-1:0), k, other...); }

	template<typename _KeepLen, typename _S>
	void __append(_S&, _KeepLen&)
	{}

	template<typename _KeepLen, typename _CharT, typename _Traits, typename _Alloc, typename _String, typename... _Strings>
	void __append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								_KeepLen& k,
								const _String& rhs,
							  const _Strings&... other)
	{
		append(lhs, __reserve_size<_String>::__mksize(rhs, k));
		__append(lhs, k, other...);
	}

	template<typename _KeepLen, std::size_t _N, typename _CharT, typename _Traits, typename _Alloc, typename... _Strings>
	void __append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
								_KeepLen& k,
							  const _CharT (&rhs)[_N], const _Strings&... other)
	{
		if (_N)
			lhs.append(rhs, _N-1);
		__append(lhs, k, other...);
	}

	template<typename _CharT, typename _Traits, typename _Alloc, typename _String1, typename _String2, typename... _Strings>
	inline std::basic_string<_CharT, _Traits, _Alloc>&
	append(std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _String1& rhs, const _String2& rhs2, const _Strings&... other)
	{
		typename __build_keep_strlen<0, parameter_pack<_String1, _String2, _Strings...>>::__type k;
		__reserve(lhs, 0, k, rhs, rhs2, other...);
		k.reset();
		__append(lhs, k, rhs, rhs2, other...);
		return lhs;
	}

	template<typename String, typename _String1, typename _String2, typename... _Strings>
	inline String&
	append(String& lhs,
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
