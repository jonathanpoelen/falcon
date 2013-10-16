#ifndef FALCON_UTILITY_SYNCHRONIZER_HPP
#define FALCON_UTILITY_SYNCHRONIZER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/utility/maker.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/tuple/to_tuple_reference.hpp>
#include <falcon/tuple/tuple_for_each.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/templates/template_left_accumulator.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

#include <tuple>
#include <type_traits>

namespace falcon
{

/**
 * Delegate the operation to each items
 */
template <typename... _Elements>
class synchronizer
: public std::tuple<_Elements...>
{
private:
	typedef std::tuple<_Elements...> __base;

public:
	typedef __base tuple_type;


public:
	using std::tuple<_Elements...>::tuple;
	using std::tuple<_Elements...>::operator=;

	const tuple_type& tuple() const
	{ return *this; }

	tuple_type& tuple()
	{ return *this; }

private:
	template <typename _T>
	struct __build_functor_type
	{ typedef _T __type; };
	template <typename _T>
	struct __build_functor_type<const _T*>
	{ typedef const _T * const __type; };

	template <typename _Functor, typename _T>
	struct __functor_wrapper
	{
		typedef typename __build_functor_type<_T>::__type __type;
		__type& value;

		__functor_wrapper(__type& x)
		: value(x)
		{}

		template<typename... _Args>
		CPP1X_DELEGATE_FUNCTION(
			operator()(_Args&&... args),
			_Functor()(this->value, std::forward<_Args>(args)...)
		)
	};

	typedef typename tuple_to_parameter_pack<__base>::type __parameter_pack;
	typedef typename parameter::modifier<std::add_const, __parameter_pack>::type __const_parameter_pack;

	typedef late_maker<std::tuple> late_tupe;

	template<typename _Maker, typename _Functor, typename _Pack = __parameter_pack, typename _Tuple = tuple_type>
	struct __delegate
	{
		typedef typename parameter_pack_to_tuple<
			typename parameter::modifier<
				template_left_accumulator<__functor_wrapper, _Functor>::template wrapper,
				_Pack
			>::type
		>::type __tuple;

		template<typename _TupleParameter>
		CPP1X_DELEGATE_FUNCTION(
			static __impl(_Tuple& t, _TupleParameter parameters),
			tuple_compose(_Maker(), __tuple(to_tuple_reference(t)), parameters)
		)
	};

	template<typename _Maker, typename _Functor>
	struct __const_delegate
	: __delegate<_Maker, _Functor, __const_parameter_pack, const tuple_type>
	{};

	template<typename _Function, typename _TupleParameter, typename _Maker = late_tupe>
	CPP1X_DELEGATE_FUNCTION(
		__call(_TupleParameter parameters, _Maker = _Maker()),
		__delegate<_Maker, _Function>::__impl(this->tuple(), parameters)
	)

	template<typename _Function, typename _TupleParameter, typename _Maker = late_tupe>
	CPP1X_DELEGATE_FUNCTION(
		__call(_TupleParameter parameters, _Maker = _Maker()) const,
		__const_delegate<_Maker, _Function>::__impl(this->tuple(), parameters)
	)

public:
#define _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, override)\
	template<typename _U>\
	CPP1X_DELEGATE_FUNCTION(operator op(_U&& x) override,\
							this->__call<late_##func_type>(std::forward_as_tuple(x)))

#define _FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)\
	_FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, const)\
	_FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type,)

#define _FALCON_SYNCHRONIZER_OPERATOR(op, func_type)\
	_FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)\
	template<typename _U>\
	synchronizer& operator op##=(_U&& x)\
	{ tuple_for_each(tuple(), placeholder_for_argument<1, late_##func_type##_equal, _U&>(x));\
	return *this; }

	_FALCON_SYNCHRONIZER_OPERATOR(+, plus)
	_FALCON_SYNCHRONIZER_OPERATOR(-, minus)
	_FALCON_SYNCHRONIZER_OPERATOR(*, multiplies)
	_FALCON_SYNCHRONIZER_OPERATOR(/, divides)
	_FALCON_SYNCHRONIZER_OPERATOR(%, modulus)

	_FALCON_SYNCHRONIZER_OPERATOR(<<, left_shift)
	_FALCON_SYNCHRONIZER_OPERATOR(>>, right_shift)

	_FALCON_SYNCHRONIZER_OPERATOR(&, bit_and)
	_FALCON_SYNCHRONIZER_OPERATOR(|, bit_or)
	_FALCON_SYNCHRONIZER_OPERATOR(^, bit_xor)

#undef _FALCON_SYNCHRONIZER_OPERATOR
#define _FALCON_SYNCHRONIZER_OPERATOR(op, func_type)\
	_FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)

	_FALCON_SYNCHRONIZER_OPERATOR([], index)

	_FALCON_SYNCHRONIZER_OPERATOR(==, equal_to)
	_FALCON_SYNCHRONIZER_OPERATOR(<, less)

	_FALCON_SYNCHRONIZER_OPERATOR(&&, logical_and)
	_FALCON_SYNCHRONIZER_OPERATOR(||, logical_or)

#undef _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER
#define _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, override)\
	template<typename _U = void>\
	CPP1X_DELEGATE_FUNCTION(operator op() override,\
							this->__call<late_##func_type>(std::tuple<>()))

	_FALCON_SYNCHRONIZER_OPERATOR(->, arrow)
	_FALCON_SYNCHRONIZER_OPERATOR(&, address)
	_FALCON_SYNCHRONIZER_OPERATOR(*, pointer)
	_FALCON_SYNCHRONIZER_OPERATOR(+, unary_plus)
	_FALCON_SYNCHRONIZER_OPERATOR(-, unary_negate)
	_FALCON_SYNCHRONIZER_OPERATOR(~, bit_not)
	_FALCON_SYNCHRONIZER_OPERATOR(!, binary_negate)

#undef _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER
#undef _FALCON_SYNCHRONIZER_OPERATOR2
#undef _FALCON_SYNCHRONIZER_OPERATOR

private:
	template<typename _T, typename _Member>
	struct __member_to_pointer
	{
		typedef typename std::remove_reference<_Member>::type member_type;
		typename std::remove_reference<_T>::type* o;
		member_type m;

		__member_to_pointer(_T& object, member_type member)
		: o(&object)
		, m(member)
		{}

		template<typename... _Args>
		CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
		(this->o->*this->m)(std::forward<_Args>(args)...))
	};

public:
	template<typename _Member>
	CPP1X_DELEGATE_FUNCTION(operator FALCON_PP_NOT_IDE_PARSER(->*)(_Member m),
	this->__call<late_maker<__member_to_pointer>>(std::make_tuple(m), late_maker<synchronizer>()))

	template<typename _Member>
	CPP1X_DELEGATE_FUNCTION(operator FALCON_PP_NOT_IDE_PARSER(->*)(_Member m) const,
	this->__call<late_maker<__member_to_pointer>>(std::make_tuple(m), late_maker<synchronizer>()))

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args),
	tuple_compose(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
	tuple_compose(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

	synchronizer& operator++()
	{
		tuple_for_each(this->tuple(), late_increment());
		return *this;
	}

	synchronizer& operator--()
	{
		tuple_for_each(this->tuple(), late_decrement());
		return *this;
	}

	synchronizer operator++(int)
	{
		synchronizer ret(*this);
		++*this;
		return ret;
	}

	synchronizer operator--(int)
	{
		synchronizer ret(*this);
		--*this;
		return ret;
	}

private:
	template<typename _U>
	synchronizer& assign(_U& x)
	{
		tuple_for_each(
			this->tuple(),
			placeholder_for_argument<1, late_affect, _U&>(x)
		);
		return *this;
	}

public:
	template<typename _U>
	synchronizer& operator=(_U& x)
	{ return assign(x); }

	template<typename _U>
	synchronizer& operator=(const _U& x)
	{ return assign(x); }

	void swap(synchronizer& other)
	{
      using std::swap;
      swap(this->tuple(), other.tuple());
    }
};

template<typename... _Elements>
constexpr synchronizer<typename decay_and_strip<_Elements>::type...>
make_synchronizer(_Elements&&... __args)
{
	return synchronizer<
		typename decay_and_strip<_Elements>::type...
	>(std::forward<_Elements>(__args)...);
}


template<std::size_t I, typename... Elements>
auto get(synchronizer<Elements...>& t) noexcept
-> decltype(std::get<I>(t))
{ return std::get<I>(t); }

template<std::size_t I, typename... Elements>
auto get(const synchronizer<Elements...>& t) noexcept
-> decltype(std::get<I>(t))
{ return std::get<I>(t); }

template<std::size_t I, typename... Elements>
auto get(synchronizer<Elements...>&& t) noexcept
-> decltype(std::get<I>(std::forward<synchronizer<Elements...>>(t)))
{ return std::get<I>(std::forward<synchronizer<Elements...>>(t)); }


///Creates a @c synchronizer of lvalue references
template<typename... _Elements>
constexpr synchronizer<_Elements&...> synchronize(_Elements&... __args)
{ return synchronizer<_Elements&...>(__args...); }

///Creates a @c synchronizer of lvalue references on tuple values
template<typename... _Elements>
synchronizer<_Elements...>& tuple_synchronise(std::tuple<_Elements...>& t)
{ return static_cast<synchronizer<_Elements...>&>(t); }

///Creates a const @c synchronizer of lvalue references on tuple values
template<typename... _Elements>
const synchronizer<_Elements...>& tuple_synchronise(const std::tuple<_Elements...>& t)
{ return static_cast<const synchronizer<_Elements...>&>(t); }

template<typename... _Elements>
void swap(falcon::synchronizer<_Elements...>& a,
          falcon::synchronizer<_Elements...>& b)
{ a.swap(b); };

}

namespace std
{
	template<typename... _Elements>
	struct tuple_size<falcon::synchronizer<_Elements...>>
	{ static const int value = sizeof...(_Elements); };

	template<std::size_t _Index, typename... _Elements>
	struct tuple_element<_Index, falcon::synchronizer<_Elements...>>
	: tuple_element<_Index, std::tuple<_Elements...>>
	{};
}

#endif
