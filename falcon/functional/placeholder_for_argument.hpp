#ifndef _FALCON_FUNCTIONAL_PLACEHOLDER_FOR_ARGUMENT_HPP
#define _FALCON_FUNCTIONAL_PLACEHOLDER_FOR_ARGUMENT_HPP

#include <utility>
#include <falcon/functional/call.hpp>
#include <falcon/type_traits/declval.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

namespace falcon {

template <int _Position, typename _Functor, typename _T>
struct placeholder_for_argument
{
	typedef _Functor functor_type;
	typedef _T first_type;

	static const int position = _Position;

private:
	_T _M_data;
	_Functor _M_functor;

public:
	constexpr placeholder_for_argument() = default;

	constexpr placeholder_for_argument(const _T& __data)
	: _M_data(__data)
	, _M_functor()
	{}

	constexpr placeholder_for_argument(const _T& __data, _Functor func)
	: _M_data(__data)
	, _M_functor(func)
	{}

	template<typename... _Args>
	constexpr placeholder_for_argument(const _T& __data, _Args&&... args)
	: _M_data(__data)
	, FALCON_PP_NOT_IDE_PARSER(_M_functor{std::forward<_Args>(args)...})
	{}

	template<typename... _Args,
		std::size_t _CutPosition = (sizeof...(_Args) < _Position ? sizeof...(_Args) : _Position) + 1,
		typename _Indexes = typename parameter_index_cat<
			typename build_range_parameter_index<1, _CutPosition>::type,
			parameter_index<0>,
			typename build_range_parameter_index<_CutPosition, sizeof...(_Args)+1>::type
		>::type
	>
	constexpr typename parameter::result_pack_of<
		const _Functor&,
		typename parameter::pack_element<
			parameter_pack<const _T&, _Args&&...>,
			_Indexes
		>::type
	>::type operator()(_Args&&... args) const
	{
		return call<const _Functor&>(_Indexes(), _M_functor, _M_data,
									 std::forward<_Args>(args)...);
	}

	template<typename... _Args,
		std::size_t _CutPosition = (sizeof...(_Args) < _Position ? sizeof...(_Args) : _Position) + 1,
		typename _Indexes = typename parameter_index_cat<
			typename build_range_parameter_index<1, _CutPosition>::type,
			parameter_index<0>,
			typename build_range_parameter_index<_CutPosition, sizeof...(_Args)+1>::type
		>::type
	>
	typename parameter::result_pack_of<
		_Functor&,
		typename parameter::pack_element<
			parameter_pack<_T&, _Args&&...>,
			_Indexes
		>::type
	>::type operator()(_Args&&... args)
	{
		return call<_Functor&>(_Indexes(), _M_functor, _M_data,
							   std::forward<_Args>(args)...);
	}

	functor_type& functor()
	{ return _M_functor; }
	constexpr const functor_type& functor() const
	{ return _M_functor; }

	first_type& data()
	{ return _M_data; }
	constexpr const first_type& data() const
	{ return _M_data; }

	void swap(placeholder_for_argument& other)
	{
		std::swap(other._M_data, _M_data);
		std::swap(other._M_functor, _M_functor);
	}
};

template<std::size_t _Position, typename _Functor, typename _T>
placeholder_for_argument<_Position, _Functor, _T> bound_argument(_Functor&& func, _T&& arg)
{
	return placeholder_for_argument<_Position, _Functor, _T>(
		std::forward<_Functor>(func), std::forward<_T>(arg)
	);
}

}

namespace std {

template <int _Position, typename _Functor, typename _T>
void swap(falcon::placeholder_for_argument<_Position, _Functor, _T>& a, falcon::placeholder_for_argument<_Position, _Functor, _T>& b)
{ a.swap(b); }

}

#endif