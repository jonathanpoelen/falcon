#ifndef FALCON_UTILITY_SYNCHRONIZER_HPP
#define FALCON_UTILITY_SYNCHRONIZER_HPP

#include <tuple>
#include <type_traits>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/utility/maker.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/functional/arguments_wrapper.hpp>
#include <falcon/tuple/tuple_for_each.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/tuple/to_tuple_reference.hpp>
#include <falcon/templates/template_left_accumulator.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>

namespace falcon
{

template <typename... _Elements>
class synchronizer
: public std::tuple<_Elements...>
{
private:
	typedef std::tuple<_Elements...> __base;

public:
	typedef __base tuple_type;


	constexpr synchronizer() = default;

	explicit constexpr synchronizer(const _Elements&... __elements)
	: __base(__elements...)
	{}

	template<typename... _UElements>
	explicit constexpr synchronizer(_UElements&&... __elements)
	: __base(std::forward<_Elements>(__elements)...)
	{}

	constexpr synchronizer(const tuple_type& t)
	: __base(t)
	{}

	constexpr synchronizer(tuple_type&& t)
	: __base(std::forward<tuple_type>(t))
	{}

	constexpr synchronizer(const synchronizer&) = default;
	constexpr synchronizer(synchronizer&&) = default;
	template<typename... _UElements>
	constexpr synchronizer(synchronizer<_UElements...>&& other)
	: __base(std::forward<std::tuple<_UElements...>>(other))
	{}

	template<typename... _UElements>
	constexpr synchronizer(const std::tuple<_UElements...>& __in)
	: __base(__in)
	{}

	template<typename... _UElements>
	constexpr synchronizer(std::tuple<_UElements...>&& __in)
	: __base(__in)
	{}

	template<typename _Alloc>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a)
	: __base(__tag, __a)
	{}

	template<typename _Alloc>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a,
					   const _Elements&... __elements)
	: __base(__tag, __a, __elements...)
	{}

	template<typename _Alloc, typename... _UElements>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a,
					   _UElements&&... __elements)
	: __base(__tag, __a, std::forward<_UElements>(__elements)...)
	{}

	template<typename _Alloc>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a,
					   const tuple_type& __in)
	: __base(__tag, __a, __in)
	{}

	template<typename _Alloc>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a,
					   tuple_type&& __in)
	: __base(__tag, __a, __in)
	{}

	template<typename _Alloc, typename... _UElements>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a,
					   const std::tuple<_UElements...>& __in)
	: __base(__tag, __a, __in)
	{}

	template<typename _Alloc, typename... _UElements>
	synchronizer(std::allocator_arg_t __tag, const _Alloc& __a,
					   std::tuple<_UElements...>&& __in)
	: __base(__tag, __a, std::forward<std::tuple<_UElements...>>(__in))
	{}

	using __base::operator=;

	const tuple_type& tuple() const
	{ return *this; }

	tuple_type& tuple()
	{ return *this; }

///TODO
// private:
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
		auto operator()(_Args&&... args)
		-> decltype(_Functor()(this->value, std::forward<_Args>(args)...))
		{ return _Functor()(value, std::forward<_Args>(args)...); }
	};

	typedef typename tuple_to_parameter_pack<__base>::type __parameter_pack;
	typedef typename parameter::pack_modifier<std::add_const, __parameter_pack>::type __const_parameter_pack;

	typedef late_maker<std::tuple> late_tupe;

	template<typename _ToTuple, typename _Tuple, bool>
	struct __delegate_to_tuple
	{
		static _ToTuple __impl(_Tuple& t)
		{ return _ToTuple(t); }
	};

	template<typename _ToTuple, typename _Tuple>
	struct __delegate_to_tuple<_ToTuple, _Tuple, false>
	{
		static _ToTuple __impl(_Tuple& t)
		{ return _ToTuple(to_tuple_reference(t)); }
	};

	template<typename _Maker, typename _Functor, typename _Pack = __parameter_pack, typename _Tuple = tuple_type>
	struct __delegate
	{
		typedef typename parameter_pack_to_tuple<
			typename parameter::pack_modifier<
				template_left_accumulator<__functor_wrapper, _Functor>::template wrapper,
				_Pack
			>::type
		>::type __tuple;

		typedef __delegate_to_tuple<__tuple, _Tuple, std::is_same<late_tupe, _Maker>::value> __to_tuple;

		template<typename _TupleParameter>
		static auto __impl(_Tuple& t, _TupleParameter parameters)
		-> decltype(tuple_compose<>(_Maker(), __to_tuple::__impl(t), parameters))
		{ return tuple_compose<>(_Maker(), __to_tuple::__impl(t), parameters); }
	};

	template<typename _Maker, typename _Functor>
	struct __const_delegate
	: __delegate<_Maker, _Functor, __const_parameter_pack, const tuple_type>
	{};

	template<typename _Function, typename _TupleParameter, typename _Maker = late_tupe>
	auto __call(_TupleParameter parameters, _Maker = _Maker())
	-> decltype(__delegate<_Maker, _Function>::__impl(this->tuple(), parameters))
	{ return __delegate<_Maker, _Function>::__impl(tuple(), parameters); }

	template<typename _Function, typename _TupleParameter, typename _Maker = late_tupe>
	auto __call(_TupleParameter parameters, _Maker = _Maker()) const
	-> decltype(__const_delegate<_Maker, _Function>::__impl(this->tuple(), parameters))
	{ return __const_delegate<_Maker, _Function>::__impl(tuple(), parameters); }

public:
#define _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, override)\
	template<typename _U>\
	CPP0X_DELEGATE_FUNCTION(operator op(_U&& x) override,\
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
	CPP0X_DELEGATE_FUNCTION(operator op() override,\
							this->__call<late_##func_type>(std::tuple<>()))

	_FALCON_SYNCHRONIZER_OPERATOR(->, arrow)
	_FALCON_SYNCHRONIZER_OPERATOR(&, address)
	_FALCON_SYNCHRONIZER_OPERATOR(*, pointer)
	_FALCON_SYNCHRONIZER_OPERATOR(+, unary_plus)
	_FALCON_SYNCHRONIZER_OPERATOR(-, unary_negate)
	_FALCON_SYNCHRONIZER_OPERATOR(~, complement)
	_FALCON_SYNCHRONIZER_OPERATOR(!, binary_negate)

#undef _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER
#undef _FALCON_SYNCHRONIZER_OPERATOR2
#undef _FALCON_SYNCHRONIZER_OPERATOR

// private:
	template<typename _T, typename _Member>
	class __member_to_pointer
	{
		///TODO private
	public:
		typename std::remove_reference<_T>::type* o;
		_Member m;

	public:
		__member_to_pointer(const __member_to_pointer&) = default;
		__member_to_pointer& operator=(const __member_to_pointer&) = default;
		__member_to_pointer(_T& object, _Member member)
		: o(&object)
		, m(member)
		{}

		template<typename... _Args>
		CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
		(this->o->*this->m)(std::forward<_Args>(args)...))
	};

public:
	///TODO
	template<typename _Member>
	CPP0X_DELEGATE_FUNCTION(operator->*(_Member m),
	this->__call<late_maker<__member_to_pointer>>(std::make_tuple(m), late_maker<synchronizer>()))

	template<typename _Member>
	CPP0X_DELEGATE_FUNCTION(operator->*(_Member m) const,
	this->__call<late_maker<__member_to_pointer>>(std::make_tuple(m), late_maker<synchronizer>()))

	///TODO
	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args),
	tuple_compose<>(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
	tuple_compose<>(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

	synchronizer& operator++()
	{
		tuple_for_each(tuple(), late_increment());
		return *this;
	}

	synchronizer& operator--()
	{
		tuple_for_each(tuple(), late_decrement());
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

	template<typename _U>
	synchronizer& operator=(_U&& x)
	{
		tuple_for_each(tuple(), placeholder_for_argument<1, late_affect, _U&>(x));
		return *this;
	}

	void swap(synchronizer& other)
	{ std::swap(tuple(), other.tuple()); }
};

template<typename... _Elements>
constexpr synchronizer<typename decay_and_strip<_Elements>::type...>
make_synchronizer(_Elements&&... __args)
{
	return synchronizer<
		typename decay_and_strip<_Elements>::type...
	>(std::forward<_Elements>(__args)...);
}

template<typename... _Elements>
constexpr synchronizer<_Elements&...>
synchronize(_Elements&... __args)
{ return synchronizer<_Elements&...>(__args...); }

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

	template<typename... _Elements>
	void swap(falcon::synchronizer<_Elements...>& a,
			  falcon::synchronizer<_Elements...>& b)
	{ a.swap(b); };
}

#endif