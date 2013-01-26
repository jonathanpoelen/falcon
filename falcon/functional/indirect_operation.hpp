#ifndef FALCON_FUNCTIONAL_INDIRECT_OPERATION_HPP
#define FALCON_FUNCTIONAL_INDIRECT_OPERATION_HPP

#include <falcon/functional/late_parameter.hpp>
#include <falcon/c++0x/syntax.hpp>

namespace falcon {

/**
	* Indirect operations
	* @{
	*/
template<typename _Functor, typename _T>
struct ptr_unary_operation;
template<typename _Functor, typename _T, typename _U = _T>
struct ptr_binary_operation;
template<typename _Functor, typename _Indirect, typename _T, typename _U = _T>
struct indirect_binary_operation;
//@}

/**
	* Lazy indirect operations
	* @{
	*/
template<typename _Functor>
using late_ptr_unary_operation = ptr_unary_operation<_Functor, late_parameter_t>;
template<typename _Functor>
using late_ptr_binary_operation = ptr_binary_operation<_Functor, late_parameter_t>;
template<typename _Functor, typename _Indirect>
using late_indirect_binary_operation = indirect_binary_operation<_Functor, _Indirect, late_parameter_t>;
//@}


template<typename _Functor, typename _T>
struct ptr_unary_operation
{
	_Functor _operation;

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T* v) const,
																					 _operation(*v))

	inline CPP0X_DELEGATE_FUNCTION(operator()(_T* v), _operation(*v))

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T* v) const,
																					 _operation(*v))

	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T* v), _operation(*v))
};

template<typename _Functor>
struct ptr_unary_operation<_Functor, late_parameter_t>
{
	_Functor _operation;

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T* v) const,
																					 _operation(*v))

	template<typename _T>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T* v), _operation(*v))

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T* v) const,
																					 _operation(*v))

	template<typename _T>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T* v), _operation(*v))
};

template<typename _Functor>
ptr_unary_operation<_Functor, late_parameter_t>
make_ptr_binary_operation(_Functor func)
{ return {func}; }

template<typename _Functor, typename _T, typename _U>
struct ptr_binary_operation
{
	_Functor _operation;

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2) const,
																					 _operation(*v, *v2))

	inline CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2), _operation(*v, *v2))

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2) const,
																					 _operation(*v, *v2))

	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2),
																 _operation(*v, *v2))
};

template<typename _Functor, typename _U>
struct ptr_binary_operation<_Functor, late_parameter_t, _U>
{
	_Functor _operation;

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2) const,
																					 _operation(*v, *v2))

	template<typename _T>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2), _operation(*v, *v2))

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2) const,
																					 _operation(*v, *v2))

	template<typename _T>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2),
																 _operation(*v, *v2))
};

template<typename _Functor, typename _T>
struct ptr_binary_operation<_Functor, _T, late_parameter_t>
{
	_Functor _operation;

	template<typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2) const,
																					 _operation(*v, *v2))

	template<typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2), _operation(*v, *v2))

	template<typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2) const,
																					 _operation(*v, *v2))

	template<typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2),
																 _operation(*v, *v2))
};

template<typename _Functor>
struct ptr_binary_operation<_Functor, late_parameter_t, late_parameter_t>
{
	_Functor _operation;

	template<typename _T, typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2) const,
																					 _operation(*v, *v2))

	template<typename _T, typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T* v, _U* v2), _operation(*v, *v2))

	template<typename _T, typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2) const,
																					 _operation(*v, *v2))

	template<typename _T, typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T* v, const _U* v2),
																 _operation(*v, *v2))
};

template<typename _Functor>
ptr_binary_operation<_Functor, late_parameter_t, late_parameter_t>
make_ptr_binary_operation(_Functor func)
{ return {func}; }

template<typename _Functor, typename _Indirect, typename _T, typename _U>
struct indirect_binary_operation
{
	_Functor _operation;
	_Indirect _indirect;

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	inline CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2),
																 _operation(_indirect(v), _indirect(v2)))

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2),
																 _operation(_indirect(v), _indirect(v2)))
};

template<typename _Functor, typename _Indirect, typename _U>
struct indirect_binary_operation<_Functor, _Indirect, late_parameter_t, _U>
{
	_Functor _operation;
	_Indirect _indirect;

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	template<typename _T>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2),
																 _operation(_indirect(v), _indirect(v2)))

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	template<typename _T>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2),
																 _operation(_indirect(v), _indirect(v2)))
};

template<typename _Functor, typename _Indirect, typename _T>
struct indirect_binary_operation<_Functor, _Indirect, _T, late_parameter_t>
{
	_Functor _operation;
	_Indirect _indirect;

	template<typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	template<typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2),
																 _operation(_indirect(v), _indirect(v2)))

	template<typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	template<typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2),
																 _operation(_indirect(v), _indirect(v2)))
};

template<typename _Functor, typename _Indirect>
struct indirect_binary_operation<_Functor, _Indirect, late_parameter_t, late_parameter_t>
{
	_Functor _operation;
	_Indirect _indirect;

	template<typename _T, typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	template<typename _T, typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_T& v, _U& v2),
																 _operation(_indirect(v), _indirect(v2)))

	template<typename _T, typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2) const,
																					 _operation(_indirect(v), _indirect(v2)))

	template<typename _T, typename _U>
	inline CPP0X_DELEGATE_FUNCTION(operator()(const _T& v, const _U& v2),
																 _operation(_indirect(v), _indirect(v2)))
};

template<typename _Functor, typename _Indirect>
indirect_binary_operation<_Functor, _Indirect, late_parameter_t, late_parameter_t>
make_indirect_binary_operation(_Functor func, _Indirect indirect)
{ return {func, indirect}; }

}

#endif