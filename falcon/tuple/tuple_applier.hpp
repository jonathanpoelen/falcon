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
	-> decltype(tuple_apply<const _Functor&>(_BuildIndexes(), _M_func,
																					 std::forward<_T>(t)))
	{
		return tuple_apply<const _Functor&>(_BuildIndexes(), _M_func, std::forward<_T>(t));
	}

	template<typename _T, typename _BuildIndexes = typename keep_parameter_index<__tag, std::tuple_size<_T>::value>::type>
	auto operator()(_T&& t)
	-> decltype(tuple_apply<_Functor&>(_BuildIndexes(), _M_func, std::forward<_T>(t)))
	{
		return tuple_apply<_Functor&>(_BuildIndexes(), _M_func, std::forward<_T>(t));
	}

	void swap(tuple_applier& other)
	{ std::swap(_M_func, other._M_func); }

	template<typename _Tag2>
	void swap(tuple_applier<_Functor, _Tag2>& other)
	{ std::swap(_M_func, other._M_func); }
};

template <typename _Functor>
tuple_applier<_Functor> make_tuple_applier(_Functor func)
{ return {std::move(func)}; }

}

namespace std {
template <typename _Functor, typename _Tag>
void swap(falcon::tuple_applier<_Functor, _Tag>& a,
					falcon::tuple_applier<_Functor, _Tag>& b)
{ a.swap(b); }
template <typename _Functor, typename _Tag, typename _Tag2>
void swap(falcon::tuple_applier<_Functor, _Tag2>& a,
					falcon::tuple_applier<_Functor, _Tag2>& b)
{ a.swap(b); }
}

#endif