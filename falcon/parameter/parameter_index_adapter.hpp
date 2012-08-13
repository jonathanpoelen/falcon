#ifndef _FALCON_PARAMETER_PARAMETER_INDEX_ADAPTER
#define _FALCON_PARAMETER_PARAMETER_INDEX_ADAPTER

#include <utility>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

template <typename _Function, typename _ParameterIndexTag>
class parameter_index_adapter
{
	typedef parameter_index_adapter<_Function, _ParameterIndexTag> self_type;

	_Function _func;

public:
	constexpr parameter_index_adapter() = default;

	constexpr parameter_index_adapter(std::nullptr_t)
	: _func(nullptr)
	{}

	constexpr parameter_index_adapter(const _Function& func)
	: _func(func)
	{}

	constexpr parameter_index_adapter(_Function&& func)
	: _func(std::forward<_Function>(func))
	{}

	self_type& operator=(const self_type& other) = default;
	self_type& operator=(self_type&& other) = default;

	self_type& operator=(const _Function& func)
	{
		_func = func;
		return *this;
	}

	self_type& operator=(_Function&& func)
	{
		_func = std::move(func);
		return *this;
	}

	self_type& operator=(std::nullptr_t)
	{
		_func = nullptr;
		return *this;
	}

	template<typename... _Args,
	typename _Indexes = typename keep_parameter_index<
		_ParameterIndexTag, sizeof...(_Args)
	>::type>
	constexpr typename __call_result_of<const _Function, _Indexes, _Args...>::__type
	operator()(_Args&&... args) const
	{
		return call<const _Function&>(_Indexes(), _func,
									  std::forward<_Args>(args)...);
	}

	template<typename... _Args,
	typename _Indexes = typename keep_parameter_index<
		_ParameterIndexTag, sizeof...(_Args)
	>::type>
	typename __call_result_of<_Function, _Indexes, _Args...>::__type
	operator()(_Args&&... args)
	{
		return call<_Function&>(_Indexes(), _func,
								std::forward<_Args>(args)...);
	}

	void swap(self_type& other)
	{
		std::swap(_func, other._func);
	}
};
}

namespace std {
template <typename _Function, typename _ParameterIndexTag>
void swap(falcon::parameter_index_adapter<_Function, _ParameterIndexTag>& a, falcon::parameter_index_adapter<_Function, _ParameterIndexTag>& b)
{
	a.swap(b);
}

}

#endif
