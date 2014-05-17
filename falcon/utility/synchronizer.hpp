#ifndef FALCON_UTILITY_SYNCHRONIZER_HPP
#define FALCON_UTILITY_SYNCHRONIZER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/utility/maker.hpp>
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
#include <functional>
#include <type_traits>

namespace falcon
{

/**
 * Delegate the operation to each items
 */
template <typename... Elements>
struct synchronizer
: std::tuple<Elements...>
{
  typedef std::tuple<Elements...> tuple_type;


public:
  using std::tuple<Elements...>::tuple;
  using std::tuple<Elements...>::operator=;

  constexpr const tuple_type& tuple() const
  { return *this; }

  CPP_CONSTEXPR_NOT_CONST tuple_type& tuple()
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

  typedef typename tuple_to_parameter_pack<tuple_type>::type __parameter_pack;
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
    static CPP1X_DELEGATE_FUNCTION(
      __impl(_Tuple& t, _TupleParameter parameters),
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
              this->__call<func_type<>>(std::forward_as_tuple(x)))

#define _FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)\
  _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, const)\
  _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type,)

#define _FALCON_SYNCHRONIZER_OPERATOR(op, op2, func_type)        \
  _FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)                  \
  template<typename _U>                                          \
  synchronizer& operator op2(_U&& x)                             \
  { tuple_for_each(tuple()                                       \
  , std::bind(func_type##_equal<>(), std::placeholders::_1, x)); \
  return *this; }

  _FALCON_SYNCHRONIZER_OPERATOR(+, +=, plus)
  _FALCON_SYNCHRONIZER_OPERATOR(-, -=, minus)
  _FALCON_SYNCHRONIZER_OPERATOR(*, *=, multiplies)
  _FALCON_SYNCHRONIZER_OPERATOR(/, /=, divides)
  _FALCON_SYNCHRONIZER_OPERATOR(%, %=, modulus)

  _FALCON_SYNCHRONIZER_OPERATOR(<<, <<=, left_shift)
  _FALCON_SYNCHRONIZER_OPERATOR(>>, >>=, right_shift)

  _FALCON_SYNCHRONIZER_OPERATOR(&, &=, bit_and)
  _FALCON_SYNCHRONIZER_OPERATOR(|, |=, bit_or)
  _FALCON_SYNCHRONIZER_OPERATOR(^, ^=, bit_xor)

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
              this->__call<func_type<>>(std::tuple<>()))

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
#ifdef IN_IDE_PARSER
# define FALCON_OPERATOR ->
#else
# define FALCON_OPERATOR ->*
#endif
  CPP1X_DELEGATE_FUNCTION(operator FALCON_OPERATOR (_Member m),
  this->__call<late_maker<__member_to_pointer>>(std::make_tuple(m), late_maker<synchronizer>()))

  template<typename _Member>
  CPP1X_DELEGATE_FUNCTION(operator FALCON_OPERATOR (_Member m) const,
  this->__call<late_maker<__member_to_pointer>>(std::make_tuple(m), late_maker<synchronizer>()))
#undef FALCON_OPERATOR

  template<typename... _Args>
  CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args),
  tuple_compose(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

  template<typename... _Args>
  CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
  tuple_compose(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

  synchronizer& operator++()
  {
    tuple_for_each(this->tuple(), increment<>());
    return *this;
  }

  synchronizer& operator--()
  {
    tuple_for_each(this->tuple(), decrement<>());
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
      std::bind(affect<>(), std::placeholders::_1, std::ref(x))
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
};

template<typename... Elements>
constexpr synchronizer<typename decay_and_strip<Elements>::type...>
make_synchronizer(Elements&&... __args)
{
  return synchronizer<
    typename decay_and_strip<Elements>::type...
  >(std::forward<Elements>(__args)...);
}


///Creates a @c synchronizer of lvalue references
template<typename... Elements>
constexpr synchronizer<Elements&...> synchronize(Elements&... __args)
{ return synchronizer<Elements&...>(__args...); }


///Creates a @c synchronizer of lvalue references on tuple values
template<typename... Elements>
synchronizer<Elements...>& synchronizer_cast(std::tuple<Elements...>& t)
{ return static_cast<synchronizer<Elements...>&>(t); }

///Creates a const @c synchronizer of lvalue references on tuple values
template<typename... Elements>
const synchronizer<Elements...>& synchronizer_cast(const std::tuple<Elements...>& t)
{ return static_cast<const synchronizer<Elements...>&>(t); }

///Creates a @c synchronizer of rvalue references on tuple values
template<typename... Elements>
synchronizer<Elements...>&& synchronizer_cast(std::tuple<Elements...>&& t)
{ return static_cast<synchronizer<Elements...>&&>(t); }

template<typename... Elements>
void swap(falcon::synchronizer<Elements...>& a,
          falcon::synchronizer<Elements...>& b)
{ a.swap(b); }

}

namespace std
{
  template<typename... Elements>
  struct tuple_size<falcon::synchronizer<Elements...>>
  { static const int value = sizeof...(Elements); };

  template<std::size_t _Index, typename... Elements>
  struct tuple_element<_Index, falcon::synchronizer<Elements...>>
  : tuple_element<_Index, std::tuple<Elements...>>
  {};
}

#endif
