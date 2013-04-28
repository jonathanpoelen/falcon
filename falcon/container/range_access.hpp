#ifndef _FALCON_ITERATOR_RANGE_ACCESS_HPP
#define _FALCON_ITERATOR_RANGE_ACCESS_HPP

#include <iterator>
#include <falcon/type_traits/declval.hpp>

/// @defgroup sequences Sequences

#if __cplusplus >= 201103L

namespace falcon {
	using std::begin;
	using std::end;

	template<class _Container>
	inline auto rbegin(_Container& cont)
	-> decltype(cont.rbegin())
	{ return cont.rbegin(); }

	template<class _Container>
	inline auto rbegin(const _Container& cont)
	-> decltype(cont.rbegin())
	{ return cont.rbegin(); }

	template<class _Container>
	inline auto rend(_Container& cont)
	-> decltype(cont.rend())
	{ return cont.rend(); }

	template<class _Container>
	inline auto rend(const _Container& cont)
	-> decltype(cont.rend())
	{ return cont.rend(); }

	template<class _Container>
	inline auto cbegin(const _Container& cont)
	-> decltype(begin(cont))
	{ return begin(cont); }

	template<class _Container>
	inline auto cend(const _Container& cont)
	-> decltype(end(cont))
	{ return end(cont); }

	template<class _Container>
	inline auto crbegin(const _Container& cont)
	-> decltype(rbegin(cont))
	{ return rbegin(cont); }

	template<class _Container>
	inline auto crend(const _Container& cont)
	-> decltype(rend(cont))
	{ return rend(cont); }
}

#else

# include <cstddef>
# include <falcon/type_traits/use_if.hpp>

namespace falcon {

	template <typename _Container>
	struct range_access_iterator
	: use_if<use_iterator<_Container>, use_const_iterator<_Container> >
	{};

	template <typename _T, std::size_t _N>
	struct range_access_iterator<_T[_N]>
	{
		typedef _T* type;
	};

	template <typename _Container>
	struct range_access_iterator<const _Container>
	: use_if<use_const_iterator<_Container>, use_iterator<_Container> >
	{};

	template <typename _Container>
	struct range_access_reverse_iterator
	: use_if<use_reverse_iterator<_Container>, use_const_reverse_iterator<_Container> >
	{};

	template <typename _T, std::size_t _N>
	struct range_access_reverse_iterator<_T[_N]>
	{
		typedef _T* type;
	};

	template <typename _Container>
	struct range_access_reverse_iterator<const _Container>
	: use_if<use_const_reverse_iterator<_Container>, use_reverse_iterator<_Container> >
	{};

	template<typename _Container>
	inline typename range_access_iterator<_Container>::type begin(_Container& cont)
	{ return cont.begin(); }

	template<typename _Container>
	inline typename range_access_iterator<_Container>::type end(_Container& cont)
	{ return cont.end(); }

	template<class _Tp, size_t _Nm>
	inline _Tp* begin(_Tp (&arr)[_Nm])
	{ return arr; }

	template<class _Tp, size_t _Nm>
	inline _Tp* end(_Tp (&arr)[_Nm])
	{ return arr + _Nm; }

	template<typename _Container>
	inline typename range_access_reverse_iterator<_Container>::type rbegin(_Container& cont)
	{ return cont.rbegin(); }

	template<typename _Container>
	inline typename range_access_reverse_iterator<_Container>::type rend(_Container& cont)
	{ return cont.rend(); }

	template<typename _Container>
	inline typename range_access_iterator<const _Container>::type cbegin(const _Container& cont)
	{ return begin(cont); }

	template<typename _Container>
	inline typename range_access_iterator<const _Container>::type cend(const _Container& cont)
	{ return end(cont); }

	template<typename _Container>
	inline typename range_access_reverse_iterator<const _Container>::type crbegin(const _Container& cont)
	{ return rbegin(cont); }

	template<typename _Container>
	inline typename range_access_reverse_iterator<const _Container>::type crend(const _Container& cont)
	{ return rend(cont); }
}
#endif

namespace falcon {
	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<_Tp*> rbegin(_Tp (&arr)[_Nm])
	{ return std::reverse_iterator<_Tp*>(begin(arr)); }

	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<_Tp*> rend(_Tp (&arr)[_Nm])
	{ return std::reverse_iterator<_Tp*>(end(arr)); }

	template<class _Tp, size_t _Nm>
	inline const _Tp* cbegin(const _Tp (&arr)[_Nm])
	{ return begin(arr); }

	template<class _Tp, size_t _Nm>
	inline const _Tp* cend(const _Tp (&arr)[_Nm])
	{ return begin(arr); }

	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<const _Tp*> crbegin(const _Tp (&arr)[_Nm])
	{ return rbegin(arr); }

	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<const _Tp*> crend(const _Tp (&arr)[_Nm])
	{ return rbegin(arr); }
}

#if __cplusplus >= 201103L

# include <type_traits>

namespace falcon {
	template <typename _Container>
	struct range_access_iterator
	{
		typedef decltype(begin(std::declval<_Container&>())) type;
	};

	template <typename _Container>
	struct range_access_reverse_iterator
	{
		typedef decltype(rbegin(std::declval<_Container&>())) type;
	};
}
#endif

namespace falcon {

	template <typename _Container>
	struct range_access_subtype
	{
		typedef typename std::iterator_traits<
			typename range_access_iterator<_Container>::type
		>::value_type type;
	};

}

#endif