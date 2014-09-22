#ifndef FALCON_UTILITY_SYNCHRONIZER_HPP
#define FALCON_UTILITY_SYNCHRONIZER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/utility/maker.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/tuple/to_tuple_reference.hpp>
#include <falcon/tuple/tuple_for_each.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/tuple/is_tuple_like.hpp>
#include <falcon/templates/template_left_accumulator.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>
#include <falcon/preprocessor/nil.hpp>

#include <tuple>
#include <functional>
#include <type_traits>

namespace falcon
{

namespace aux_ {
#define FALCON_SYNCHRONISE_AUX_IF_AVAILABLE(               \
  op, func_type, prefix, qualifier, hidden)                \
  template<class Base, class = void>                       \
  struct prefix##_if_available                             \
  : Base                                                   \
  {                                                        \
    using Base::Base;                                      \
    using Base::operator=;                                 \
  };                                                       \
                                                           \
  template<class Base>                                     \
  struct prefix##_if_available<Base, enable_type_t<        \
    decltype(std::declval<qualifier Base>()                \
      .template call_<func_type<>>(std::tuple<>()))        \
  > > : Base                                               \
  {                                                        \
    using Base::Base;                                      \
    using Base::operator=;                                 \
                                                           \
    hidden                                                 \
                                                           \
    CPP1X_DELEGATE_FUNCTION(                               \
      operator op() qualifier,                             \
      this->template call_<func_type<>>(std::tuple<>()));  \
  }

#define FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(op, func_type, hidden) \
  FALCON_SYNCHRONISE_AUX_IF_AVAILABLE(                              \
    op, func_type, const_##func_type, const, hidden);               \
  FALCON_SYNCHRONISE_AUX_IF_AVAILABLE(                              \
    op, func_type, func_type, FALCON_PP_NIL(), hidden)

FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(->, arrow, FALCON_PP_NIL());
FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(&, address, FALCON_PP_NIL());
FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(*, pointer, using Base::operator*;);
FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(+, unary_plus, using Base::operator+;);
FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(-, unary_negate, using Base::operator-;);
FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(~, bit_not, FALCON_PP_NIL());
FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2(!, binary_negate, FALCON_PP_NIL());

#undef FALCON_SYNCHRONISE_AUX_IF_AVAILABLE2
#undef FALCON_SYNCHRONISE_AUX_IF_AVAILABLE

template <typename... Elements>
struct basic_synchronizer
: std::tuple<Elements...>
{
  typedef std::tuple<Elements...> tuple_type;

  using std::tuple<Elements...>::tuple;
  using std::tuple<Elements...>::operator=;

  constexpr const tuple_type& tuple() const
  { return reinterpret_cast<tuple_type const &>(*this); }

  CPP_CONSTEXPR_NOT_CONST tuple_type& tuple()
  { return *this; }

private:
  template <typename T>
  struct build_functor_type_
  { typedef T type; };
  template <typename T>
  struct build_functor_type_<const T*>
  { typedef const T * const type; };

  template <typename Functor, typename T>
  struct functor_wrapper_
  {
    typedef typename build_functor_type_<T>::type type;
    type& value;

    functor_wrapper_(type& x)
    : value(x)
    {}

    template<typename... Args>
    CPP1X_DELEGATE_FUNCTION(
      operator()(Args&&... args),
      Functor()(this->value, std::forward<Args>(args)...)
    )
  };

  typedef typename tuple_to_parameter_pack<tuple_type>::type parameter_pack_;
  typedef typename parameter::modifier<
    std::add_const, parameter_pack_>::type const_parameter_pack_;

  template<
    typename Maker, typename Functor,
    typename Pack = parameter_pack_, typename Tuple = tuple_type>
  struct delegate_
  {
    typedef typename parameter_pack_to_tuple<
      typename parameter::modifier<
        template_left_accumulator<functor_wrapper_, Functor>::template wrapper,
        Pack
      >::type
    >::type tuple_;

    template<typename TupleParameter>
    static CPP1X_DELEGATE_FUNCTION(
      impl(Tuple& t, TupleParameter parameters),
      tuple_compose(Maker(), tuple_(to_tuple_reference(t)), parameters)
    )
  };

  template<typename Maker, typename Functor>
  struct const_delegate_
  : delegate_<Maker, Functor, const_parameter_pack_, const tuple_type>
  {};

public:
  typedef late_maker<std::tuple> late_tupe;

  template<
    typename Function, typename TupleParameter, typename Maker = late_tupe>
  CPP1X_DELEGATE_FUNCTION(
    call_(TupleParameter parameters, Maker = Maker()),
    delegate_<Maker, Function>::impl(this->tuple(), parameters)
  )

  template<
    typename Function, typename TupleParameter, typename Maker = late_tupe>
  CPP1X_DELEGATE_FUNCTION(
    call_(TupleParameter parameters, Maker = Maker()) const,
    const_delegate_<Maker, Function>::impl(this->tuple(), parameters)
  )

public:
#define _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, qualifier) \
  template<typename U>                                                   \
  CPP1X_DELEGATE_FUNCTION(                                                \
    operator op(U&& x) qualifier,                                        \
    this->template call_<func_type<>>(std::forward_as_tuple(x)))

#define _FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)           \
  _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, const) \
  _FALCON_SYNCHRONIZER_OPERATOR_QUALIFIER(op, func_type, FALCON_PP_NIL())

#define _FALCON_SYNCHRONIZER_OPERATOR(op, op2, func_type)        \
  _FALCON_SYNCHRONIZER_OPERATOR2(op, func_type)                  \
  template<typename U>                                          \
  basic_synchronizer& operator op2(U&& x)                       \
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
#undef _FALCON_SYNCHRONIZER_OPERATOR2
#undef _FALCON_SYNCHRONIZER_OPERATOR

private:
  template<typename T, typename Member>
  struct member_to_pointer_
  {
    typedef typename std::remove_reference<Member>::type member_type;
    typename std::remove_reference<T>::type* o;
    member_type m;

    member_to_pointer_(T& object, member_type member)
    : o(&object)
    , m(member)
    {}

    template<typename... Args>
    CPP1X_DELEGATE_FUNCTION(operator()(Args&&... args) const,
    (this->o->*this->m)(std::forward<Args>(args)...))
  };

public:
  template<typename Member>
#ifdef IN_IDE_PARSER
# define FALCON_OPERATOR ->
#else
# define FALCON_OPERATOR ->*
#endif
  CPP1X_DELEGATE_FUNCTION(
    operator FALCON_OPERATOR (Member m),
    this->template call_<late_maker<member_to_pointer_>>(
      std::make_tuple(m), late_maker< ::falcon::aux_::basic_synchronizer>()))

  template<typename Member>
  CPP1X_DELEGATE_FUNCTION(
    operator FALCON_OPERATOR (Member m) const,
    this->template call_<late_maker<member_to_pointer_>>(
      std::make_tuple(m), late_maker<::falcon::aux_::basic_synchronizer>()))
#undef FALCON_OPERATOR


  template<typename... Args>
  CPP1X_DELEGATE_FUNCTION(operator()(Args&&... args),
  tuple_compose(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

  template<typename... Args>
  CPP1X_DELEGATE_FUNCTION(operator()(Args&&... args) const,
  tuple_compose(late_tupe(), this->tuple(), std::forward_as_tuple(args...)))

  basic_synchronizer& operator++()
  {
    tuple_for_each(this->tuple(), increment<>());
    return *this;
  }

  basic_synchronizer& operator--()
  {
    tuple_for_each(this->tuple(), decrement<>());
    return *this;
  }

  basic_synchronizer operator++(int)
  {
    basic_synchronizer ret(*this);
    ++*this;
    return ret;
  }

  basic_synchronizer operator--(int)
  {
    basic_synchronizer ret(*this);
    --*this;
    return ret;
  }

private:
  template<typename U>
  basic_synchronizer& assign(U& x)
  {
    tuple_for_each(
      this->tuple(),
      std::bind(assign<>(), std::placeholders::_1, std::ref(x))
    );
    return *this;
  }

public:
  template<typename U>
  basic_synchronizer& operator=(U& x)
  { return assign(x); }

  template<typename U>
  basic_synchronizer& operator=(const U& x)
  { return assign(x); }
};

template<class... Elements>
using synchronizer_base
  = arrow_if_available<
    const_arrow_if_available<
    address_if_available<
    const_address_if_available<
    pointer_if_available<
    const_pointer_if_available<
    unary_plus_if_available<
    const_unary_plus_if_available<
    unary_negate_if_available<
    const_unary_negate_if_available<
    bit_not_if_available<
    const_bit_not_if_available<
    binary_negate_if_available<
    const_binary_negate_if_available<
    basic_synchronizer<Elements...>
> > > > > > > > > > > > > >;

}

/**
 * Delegate the operation to each items
 */
template<class... Elements>
struct synchronizer
: aux_::synchronizer_base<Elements...>
{
  using aux_::synchronizer_base<Elements...>::synchronizer_base;
  using aux_::synchronizer_base<Elements...>::operator=;

private:
  using aux_::synchronizer_base<Elements...>::call_;
};


template<typename... Elements>
constexpr synchronizer<typename decay_and_strip<Elements>::type...>
make_synchronizer(Elements&&... args)
{
  return synchronizer<
    typename decay_and_strip<Elements>::type...
  >(std::forward<Elements>(args)...);
}


///Creates a @c synchronizer of lvalue references
template<typename... Elements>
constexpr synchronizer<Elements&...>
synchronize(Elements&... args)
{ return synchronizer<Elements&...>(args...); }


///Creates a @c synchronizer of lvalue references on tuple values
template<typename... Elements>
synchronizer<Elements...>&
synchronizer_cast(std::tuple<Elements...>& t)
{ return static_cast<synchronizer<Elements...>&>(t); }

///Creates a const @c synchronizer of lvalue references on tuple values
template<typename... Elements>
const synchronizer<Elements...>&
synchronizer_cast(const std::tuple<Elements...>& t)
{ return static_cast<const synchronizer<Elements...>&>(t); }

///Creates a @c synchronizer of rvalue references on tuple values
template<typename... Elements>
synchronizer<Elements...>&&
synchronizer_cast(std::tuple<Elements...>&& t)
{ return static_cast<synchronizer<Elements...>&&>(t); }

template<typename... Elements>
void swap(
  falcon::synchronizer<Elements...>& a,
  falcon::synchronizer<Elements...>& b)
{ a.swap(b); }

template<class... Elements>
struct is_tuple_like<synchronizer<Elements...>>
: std::true_type
{};

}

namespace std
{
  template<typename... Elements>
  struct tuple_size<falcon::synchronizer<Elements...>>
  { static const int value = sizeof...(Elements); };

  template<std::size_t Index, typename... Elements>
  struct tuple_element<Index, falcon::synchronizer<Elements...>>
  : tuple_element<Index, std::tuple<Elements...>>
  {};
}

#endif
