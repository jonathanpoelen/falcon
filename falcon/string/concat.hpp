#ifndef FALCON_STRING_CONCAT2_HPP
#define FALCON_STRING_CONCAT2_HPP

#if __cplusplus > 201100L
# include <utility>
# include <type_traits>
#else
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_integral.hpp>
#endif
#include <falcon/detail/string_size.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/string/append.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>

namespace falcon {
	template <typename _T>
	struct __concat_result_traits
	{
		typedef typename _T::value_type __char_type;
		typedef typename _T::traits_type __traits_type;
		typedef typename use_if<use_allocator_type<_T>, use<void> >::type __allocator;
	};

	template <typename _CharT>
	struct __concat_result_traits<const _CharT *>
	{
		typedef _CharT __char_type;
		typedef void __traits_type;
		typedef void __allocator;
	};

	template <typename _CharT>
	struct __concat_result_traits<_CharT *>
	{
		typedef _CharT __char_type;
		typedef void __traits_type;
		typedef void __allocator;
	};

	template <typename _CharT, std::size_t _N>
	struct __concat_result_traits<_CharT[_N]>
	{
		typedef _CharT __char_type;
		typedef void __traits_type;
		typedef void __allocator;
	};

	template <typename _CharT, std::size_t _N>
	struct __concat_result_traits<const _CharT[_N]>
	{
		typedef _CharT __char_type;
		typedef void __traits_type;
		typedef void __allocator;
	};


	template<typename, typename>
	struct __concat_char;

	template<typename _T>
	struct __concat_char<_T,_T>
	{ typedef _T __char_type; };


	template<typename, typename, typename>
	struct __concat_traits;

	template<typename _CharT, typename _T>
	struct __concat_traits<_CharT, _T,_T>
	{ typedef _T __traits_type; };

	template<typename _CharT, typename _T>
	struct __concat_traits<_CharT, _T, void>
	{ typedef _T __traits_type; };

	template<typename _CharT, typename _T>
	struct __concat_traits<_CharT, void, _T>
	{ typedef _T __traits_type; };

	template<typename _CharT>
	struct __concat_traits<_CharT, void, void>
	{ typedef std::char_traits<_CharT> __traits_type; };


	template<typename, typename _T, typename>
	struct __concat_allocator_impl
	{ typedef _T __allocator; };

	template<typename _CharT, typename _T>
	struct __concat_allocator_impl<_CharT, void, _T>
	{ typedef _T __allocator; };

	template<typename _CharT>
	struct __concat_allocator_impl<_CharT, void, void>
	{ typedef std::allocator<_CharT> __allocator; };

	template<typename, typename, typename, typename _Alloc>
	struct __concat_allocator
	{ typedef _Alloc __allocator; };

	template<typename _CharT, typename _T, typename _U>
	struct __concat_allocator<_CharT, _T, _U, void>
	: __concat_allocator_impl<_CharT, _T, _U>
	{};

	template <bool A, bool B, typename _T, typename _U, typename _Alloc>
	struct __concat_result_impl
	{
		typedef typename __concat_char<
			typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<
				typename __concat_result_traits<_T>::__char_type
			>::type,
			typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<
				typename __concat_result_traits<_U>::__char_type
			>::type
		>::__char_type __char_type;
		typedef std::basic_string<
			__char_type,
			typename __concat_traits<
				__char_type,
				typename __concat_result_traits<_T>::__traits_type,
				typename __concat_result_traits<_U>::__traits_type
			>::__traits_type,
			typename __concat_allocator<
				__char_type,
				typename __concat_result_traits<_T>::__allocator,
				typename __concat_result_traits<_U>::__allocator,
				_Alloc
			>::__allocator
		> __result_type;
	};

	template <typename _CharT, typename _T, typename _Alloc,
		typename _Check = typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<
			typename __concat_result_traits<_T>::__char_type
		>::type
	>
	struct __concat_result_impl2;

	template <typename _CharT, typename _T, typename _Alloc>
	struct __concat_result_impl2<_CharT, _T, _Alloc, _CharT>
	{
		typedef std::basic_string<
			_CharT,
			typename __concat_traits<
				_CharT,
				void,
				typename __concat_result_traits<_T>::__traits_type
			>::__traits_type,
			typename __concat_allocator_impl<
				_CharT,
				void,
				_Alloc
			>::__allocator
		> __result_type;
	};

	template <typename _CharT, typename _T, typename _Alloc>
	struct __concat_result_impl<true, false, _CharT, _T, _Alloc>
	: __concat_result_impl2<_CharT, _T, _Alloc>
	{};

	template <typename _T, typename _CharT, typename _Alloc>
	struct __concat_result_impl<false, true, _T, _CharT, _Alloc>
	: __concat_result_impl2<_CharT, _T, _Alloc>
	{};

	template <typename _CharT, typename _Alloc>
	struct __concat_result_impl<true, true, _CharT, _CharT, _Alloc>
	: __concat_result_impl2<_CharT, _CharT, _Alloc>
	{
		typedef std::basic_string<
			_CharT,
			std::char_traits<_CharT>,
			typename __concat_allocator_impl<
				_CharT,
				void,
				_Alloc
			>::__allocator
		> __result_type;
	};

	template <typename _T, typename _U, typename _Alloc = void>
	struct __concat_result
	: __concat_result_impl<
		FALCON_BOOST_OR_STD_NAMESPACE::is_integral<_T>::value,
		FALCON_BOOST_OR_STD_NAMESPACE::is_integral<_U>::value,
		_T, _U, _Alloc
	>{};


	template<typename _CharT, typename _Traits, typename _Alloc, typename _T>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(const std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _T& rhs)
	{
		std::basic_string<_CharT, _Traits, _Alloc> ret;
		typedef typename detail::__string_size<_T>::__reference __reference;
		__reference __rhs(rhs);
		ret.reserve(lhs.size() + detail::__string_size<_T>::size(__rhs));
		append(append(ret, lhs), __rhs);
		return ret;
	}

#if __cplusplus > 201100L
	template<typename _CharT, typename _Traits, typename _Alloc, typename _T>
	inline std::basic_string<_CharT, _Traits, _Alloc>
	concat(std::basic_string<_CharT, _Traits, _Alloc>&& lhs, const _T& rhs)
	{
		typedef typename detail::__string_size<_T>::__reference __reference;
		__reference __rhs(rhs);
		lhs.reserve(lhs.size() + detail::__string_size<_T>::size(__rhs));
		append(lhs, __rhs);
		return std::move(lhs);
	}
#endif

	template<typename _S, typename _T, typename _U>
	inline void __append2(_S& ret, const _T& lhs, const _U& rhs)
	{
#if __cplusplus > 201100L
		append(ret, lhs, rhs);
#else
		typedef typename detail::__string_size<_T>::__reference __reference;
		typedef typename detail::__string_size<_U>::__reference __reference2;
		__reference __lhs(lhs);
		__reference2 __rhs(rhs);
		ret.reserve(ret.size() + detail::__string_size<_T>::size(__lhs) + detail::__string_size<_U>::size(__rhs));
		append(append(ret, __lhs), __rhs);
#endif
	}

	template<typename _T, typename _U>
	inline typename __concat_result<_T, _U>::__result_type
	concat(const _T& lhs, const _U& rhs)
	{
		typedef typename __concat_result<_T, _U>::__result_type __reult_type;
		__reult_type ret;
		__append2(ret, lhs, rhs);
		return ret;
	}

	template<typename _T, typename _U, typename _Alloc>
	inline typename __concat_result<_T, _U, _Alloc>::__result_type
	concat_with_alloc(const _Alloc& alloc, const _T& lhs, const _U& rhs)
	{
		typedef typename __concat_result<_T, _U, _Alloc>::__result_type __reult_type;
		__reult_type ret(alloc);
		__append2(ret, lhs, rhs);
		return ret;
	}

#if __cplusplus > 201100L
	template<typename _Elements, typename _Result, typename _Alloc = void>
	struct __build_string;

	template<typename _T, typename... _Elements, typename _Alloc>
	struct __build_string<parameter_pack<_T, _T, _Elements...>, _T, _Alloc>
	: __build_string<parameter_pack<_T, _Elements...>, _T, _Alloc>
	{};

	template<typename _T, typename... _Elements, typename _Result, typename _Alloc>
	struct __build_string<parameter_pack<_T, _T, _Elements...>, _Result, _Alloc>
	: __build_string<parameter_pack<_T, _Elements...>, _Result, _Alloc>
	{};

	template<typename _T, typename _U, typename... _Elements, typename _Alloc>
	struct __build_string<parameter_pack<_T, _U, _Elements...>, _T, _Alloc>
	: __build_string<parameter_pack<_U, _Elements...>, _T, _Alloc>
	{};

	template<typename _T, typename _U, typename _Alloc,
		bool _Is1 = std::is_integral<_T>::value,
		bool _Is2 = std::is_integral<_U>::value>
	struct __build_string_impl
	: __concat_result_impl<_Is1, _Is2, _T, _U, _Alloc>
	{};

	template<typename _T, typename _Alloc>
	struct __build_string_impl<_T, _T, _Alloc, true, true>
	{ typedef _T __result_type; };

	template<typename _T, typename _U, typename... _Elements,
		typename _Result, typename _Alloc>
	struct __build_string<parameter_pack<_T, _U, _Elements...>, _Result, _Alloc>
	: __build_string<
		parameter_pack<_U, _Elements...>,
		typename __build_string_impl<_T, _Result, _Alloc>::__result_type,
		_Alloc
	>{};

	template<typename _T, typename _Result, typename _Alloc>
	struct __build_string<parameter_pack<_T>, _Result, _Alloc>
	: __concat_result<_T, _Result, _Alloc>
	{};

	template<typename _Result, typename _Alloc>
	struct __build_string<parameter_pack<>, _Result, _Alloc>
	: __concat_result<_Result, _Result, _Alloc>
	{};

	template<typename _StringL, typename _StringR,
		typename _StringR2, typename... _Strings>
	typename __build_string<
		parameter_pack<_StringR, _StringR2, _Strings...>,
		_StringL
	>::__result_type
	concat(const _StringL& lhs, const _StringR& rhs,
				 const _StringR2& rhs2, const _Strings&... other)
	{
		typename __build_string<
			parameter_pack<_StringR, _StringR2, _Strings...>,
			_StringL
		>::__result_type str;
		append(str, lhs, rhs, rhs2, other...);
		return str;
	}

	template<typename _CharT, typename _Traits, typename _Alloc,
		typename _StringR, typename _StringR2, typename... _Strings>
	std::basic_string<_CharT, _Traits, _Alloc>
	concat(const std::basic_string<_CharT, _Traits, _Alloc>& lhs,
				 const _StringR& rhs, const _StringR2& rhs2,
				 const _Strings&... other)
	{
		typename __build_string<
			parameter_pack<_StringR, _StringR2, _Strings...>,
			std::basic_string<_CharT, _Traits, _Alloc>
		>::__result_type str;
		append(str, lhs, rhs, rhs2, other...);
		return str;
	}

	template<typename _CharT, typename _Traits, typename _Alloc,
		typename _StringR, typename _StringR2, typename... _Strings>
	std::basic_string<_CharT, _Traits, _Alloc>
	concat(std::basic_string<_CharT, _Traits, _Alloc>&& lhs,
				 const _StringR& rhs, const _StringR2& rhs2,
				 const _Strings&... other)
	{
		append(lhs, rhs, rhs2, other...);
		return std::move(lhs);

		// check if @lhs is compatible with @result_type
		(void)typename __build_string<
			parameter_pack<_StringR, _StringR2, _Strings...>,
			std::basic_string<_CharT, _Traits, _Alloc>
		>::__result_type(lhs);
	}

	template<typename _Alloc, typename _StringL, typename _StringR,
		typename _StringR2, typename... _Strings>
	typename __build_string<
		parameter_pack<_StringR, _StringR2, _Strings...>,
		_StringL
	>::__result_type
	concat_with_alloc(const _Alloc& alloc, const _StringL& lhs,
										const _StringR& rhs, const _StringR2& rhs2,
									  const _Strings&... other)
	{
		typename __build_string<
			parameter_pack<_StringR, _StringR2, _Strings...>,
			_StringL, _Alloc
		>::__result_type str(alloc);
		append(str, lhs, rhs, rhs2, other...);
		return str;
	}
#endif

}

#endif