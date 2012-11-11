#ifndef _FALCON_TUPLE_TUPLE_APPLIER_HPP
#define _FALCON_TUPLE_TUPLE_APPLIER_HPP

#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

/**
 * \brief Functor for used \p tuple_apply()
 *
 * Tag is \link indexes-tag indexes-tag \endlink or \p parameter_index
 */
template <typename _Functor, typename _Tag = full_parameter_index_tag>
struct tuple_applier
{
	_Functor _M_func;

private:
	typedef typename parameter_index_or_tag_to_tag<_Tag>::type __tag;

public:
	template<typename _T, typename _BuildIndexes = typename keep_parameter_index<__tag, std::tuple_size<_T>::value>::type>
	constexpr auto operator()(_T&& t) const
	-> decltype(tuple_apply<const _Functor&>(_BuildIndexes(), std::forward<_T>(t),
											 _M_func))
	{
		return tuple_apply<const _Functor&>(_BuildIndexes(), std::forward<_T>(t),
											_M_func);
	}

	template<typename _T, typename _BuildIndexes = typename keep_parameter_index<__tag, std::tuple_size<_T>::value>::type>
	auto operator()(_T&& t)
	-> decltype(tuple_apply<_Functor&>(_BuildIndexes(), std::forward<_T>(t), _M_func))
	{
		return tuple_apply<_Functor&>(_BuildIndexes(), std::forward<_T>(t), _M_func);
	}

	void swap(tuple_applier& other)
	{
		std::swap(_M_func, other._M_func);
	}
};

}

namespace std {
template <typename _Functor, typename _Tag>
void swap(falcon::tuple_applier<_Functor, _Tag>& a,
		  falcon::tuple_applier<_Functor, _Tag>& b)
{ (a.swap(b); }
}

#endif