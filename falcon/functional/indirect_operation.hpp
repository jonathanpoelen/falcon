#ifndef FALCON_FUNCTIONAL_INDIRECT_OPERATION_HPP
#define FALCON_FUNCTIONAL_INDIRECT_OPERATION_HPP

#include <falcon/functional/late_parameter.hpp>
#include <falcon/c++1x/syntax.hpp>

namespace falcon {

/**
 * Indirect operations
 * @{
 */
template<typename Functor, typename T>
struct ptr_unary_operation;
template<typename Functor, typename T, typename _U = T>
struct ptr_binary_operation;
template<typename Functor, typename Indirect, typename T, typename _U = T>
struct indirect_binary_operation;
//@}

/**
 * Lazy indirect operations
 * @{
 */
template<typename Functor>
using late_ptr_unary_operation = ptr_unary_operation<Functor, late_parameter_t>;
template<typename Functor>
using late_ptr_binary_operation = ptr_binary_operation<Functor, late_parameter_t>;
template<typename Functor, typename Indirect>
using late_indirect_binary_operation = indirect_binary_operation<Functor, Indirect, late_parameter_t>;
//@}


template<typename Functor, typename T>
struct ptr_unary_operation
{
	Functor _operation;

	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T* v) const, _operation(*v))
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T* v) const, _operation(*v))
};

template<typename Functor>
struct ptr_unary_operation<Functor, late_parameter_t>
{
	Functor _operation;

	template<typename T>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T* v) const, _operation(*v))

	template<typename T>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T* v) const, _operation(*v))
};

template<typename Functor>
ptr_unary_operation<Functor, late_parameter_t>
make_ptr_binary_operation(Functor func)
{ return {func}; }

template<typename Functor, typename T, typename _U>
struct ptr_binary_operation
{
	Functor _operation;

	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T* v, _U* v2) const,
                                      _operation(*v, *v2))

	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T* v, const _U* v2) const,
                                      _operation(*v, *v2))
};

template<typename Functor, typename _U>
struct ptr_binary_operation<Functor, late_parameter_t, _U>
{
	Functor _operation;

	template<typename T>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T* v, _U* v2) const,
                                      _operation(*v, *v2))

	template<typename T>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T* v, const _U* v2) const,
                                      _operation(*v, *v2))
};

template<typename Functor, typename T>
struct ptr_binary_operation<Functor, T, late_parameter_t>
{
	Functor _operation;

	template<typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T* v, _U* v2) const,
                                      _operation(*v, *v2))

	template<typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T* v, const _U* v2) const,
                                      _operation(*v, *v2))
};

template<typename Functor>
struct ptr_binary_operation<Functor, late_parameter_t, late_parameter_t>
{
	Functor _operation;

	template<typename T, typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T* v, _U* v2) const,
                                      _operation(*v, *v2))

	template<typename T, typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T* v, const _U* v2) const,
                                      _operation(*v, *v2))
};

template<typename Functor>
ptr_binary_operation<Functor, late_parameter_t, late_parameter_t>
make_ptr_binary_operation(Functor func)
{ return {func}; }

template<typename Functor, typename Indirect, typename T, typename _U>
struct indirect_binary_operation
{
	Functor _operation;
	Indirect _indirect;

	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& v, _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))

	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& v, const _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))
};

template<typename Functor, typename Indirect, typename _U>
struct indirect_binary_operation<Functor, Indirect, late_parameter_t, _U>
{
	Functor _operation;
	Indirect _indirect;

	template<typename T>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& v, _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))

	template<typename T>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& v, const _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))
};

template<typename Functor, typename Indirect, typename T>
struct indirect_binary_operation<Functor, Indirect, T, late_parameter_t>
{
	Functor _operation;
	Indirect _indirect;

	template<typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& v, _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))

	template<typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& v, const _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))
};

template<typename Functor, typename Indirect>
struct indirect_binary_operation<Functor, Indirect, late_parameter_t, late_parameter_t>
{
	Functor _operation;
	Indirect _indirect;

	template<typename T, typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& v, _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))

	template<typename T, typename _U>
	constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& v, const _U& v2) const,
                                      _operation(_indirect(v), _indirect(v2)))
};

template<typename Functor, typename Indirect>
indirect_binary_operation<Functor, Indirect, late_parameter_t, late_parameter_t>
make_indirect_binary_operation(Functor func, Indirect indirect)
{ return {func, indirect}; }

}

#endif
