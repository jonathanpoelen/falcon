#ifndef _FALCON_UTILITY_MAKER_HPP
#define _FALCON_UTILITY_MAKER_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
# include <falcon/utility/detail/construct_category.hpp>
#endif

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _Tp, typename _Tag>
struct __maker
{
	constexpr __maker()
	{}

	template<typename _Up, typename _Tag2>
	constexpr __maker(const __maker<_Up, _Tag2>&)
	{}

	_Tp operator()() const
	{
		return _Tp();
	}

	_Tp operator()(const _Tp& v) const
	{
		return _Tp(v);
	}

	template<typename... _Args>
	_Tp operator()(_Args&&... args) const
	{
		return _Tp{std::forward<_Args>(args)...};
	}
};

template<typename _Tp>
struct __maker<_Tp, ::falcon::detail::initilizer_list_construct_tag>
{
	constexpr __maker()
	{}

	template<typename _Up, typename _Tag>
	constexpr __maker(const __maker<_Up, _Tag>&)
	{}

	_Tp operator()() const
	{
		return _Tp();
	}

	_Tp operator()(const _Tp& v) const
	{
		return _Tp(v);
	}

	template<typename... _Args>
	_Tp operator()(_Args&&... args) const
	{
		return _Tp{{std::forward<_Args>(args)...}};
	}
};

///wrapper of construct object
template<typename _Tp>
struct maker
: __maker< _Tp, typename ::falcon::detail::construct_category<_Tp>::type>
{};

#else

///wrapper of construct object
template<typename _Tp>
struct maker
{
	maker()
	{}

	template<typename _Up>
	maker(const maker<_Up>&)
	{}

	_Tp operator()() const
	{
		return _Tp();
	}

	_Tp operator()(const _Tp& v) const
	{
		return _Tp(v);
	}
};
#endif

}

#endif
