#ifndef _FALCON_FUNCTIONAL_OPERATORS_HPP
#define _FALCON_FUNCTIONAL_OPERATORS_HPP

#include <iosfwd>
#include <utility>
#include <type_traits>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/late_parameter.hpp>

namespace falcon {

/**
 * Arithmetic operations
 * @{
 */
template<typename T, typename U = T>
struct plus;
template<typename T, typename U = T>
struct minus;
template<typename T, typename U = T>
struct multiplies;
template<typename T, typename U = T>
struct modulus;
template<typename T, typename U = T>
struct divides;

template<typename T, typename U = T>
struct plus_equal;
template<typename T, typename U = T>
struct minus_equal;
template<typename T, typename U = T>
struct multiplies_equal;
template<typename T, typename U = T>
struct modulus_equal;
template<typename T, typename U = T>
struct divides_equal;

template<typename T>
struct increment;
template<typename T>
struct decrement;
template<typename T>
struct post_increment;
template<typename T>
struct post_decrement;

template<typename T>
struct unary_negate;
template<typename T>
struct unary_plus;
//@}

/**
 * Lazy Arithmetic operations
 * @{
 */
typedef plus<late_parameter_t> late_plus;
typedef minus<late_parameter_t> late_minus;
typedef multiplies<late_parameter_t> late_multiplies;
typedef modulus<late_parameter_t> late_modulus;
typedef divides<late_parameter_t> late_divides;

typedef plus_equal<late_parameter_t> late_plus_equal;
typedef minus_equal<late_parameter_t> late_minus_equal;
typedef multiplies_equal<late_parameter_t> late_multiplies_equal;
typedef modulus_equal<late_parameter_t> late_modulus_equal;
typedef divides_equal<late_parameter_t> late_divides_equal;

typedef increment<late_parameter_t> late_increment;
typedef decrement<late_parameter_t> late_decrement;
typedef post_increment<late_parameter_t> late_post_increment;
typedef post_decrement<late_parameter_t> late_post_decrement;

typedef unary_negate<late_parameter_t> late_unary_negate;
typedef unary_plus<late_parameter_t> late_unary_plus;
//@}

/**
 * Comparisons
 * @{
 */
template<typename T, typename U = T>
struct equal_to;
template<typename T, typename U = T>
struct not_equal_to;
template<typename T, typename U = T>
struct greater;
template<typename T, typename U = T>
struct less;
template<typename T, typename U = T>
struct greater_equal;
template<typename T, typename U = T>
struct less_equal;
template<typename T, typename U = T>
struct equivalent;
//@}

/**
 * Lazy comparisons
 * @{
 */
typedef equal_to<late_parameter_t> late_equal_to;
typedef not_equal_to<late_parameter_t> late_not_equal_to;
typedef greater<late_parameter_t> late_greater;
typedef less<late_parameter_t> late_less;
typedef greater_equal<late_parameter_t> late_greater_equal;
typedef less_equal<late_parameter_t> late_less_equal;
typedef equivalent<late_parameter_t> late_equivalent;
//@}

/**
 * Logical operations
 * @{
 */
template<typename T, typename U = T>
struct logical_and;
template<typename T, typename U = T>
struct logical_or;
//@}

/**
 * Lazy logical operations
 * @{
 */
typedef logical_and<late_parameter_t> late_logical_and;
typedef logical_or<late_parameter_t> late_logical_or;
//@}

/**
 * Bitwise operations
 * @{
 */
template<typename T, typename U = T>
struct bit_and;
template<typename T, typename U = T>
struct bit_or;
template<typename T, typename U = T>
struct bit_xor;
template<typename T, typename U = T>
struct left_shift;
template<typename T, typename U = T>
struct right_shift;

template<typename T, typename U = T>
struct bit_and_equal;
template<typename T, typename U = T>
struct bit_or_equal;
template<typename T, typename U = T>
struct bit_xor_equal;
template<typename T, typename U = T>
struct left_shift_equal;
template<typename T, typename U = T>
struct right_shift_equal;

template<typename T>
struct bit_not;
//@}

/**
 * Lazy bitwise operations
 * @{
 */
typedef bit_and<late_parameter_t> late_bit_and;
typedef bit_or<late_parameter_t> late_bit_or;
typedef bit_xor<late_parameter_t> late_bit_xor;
typedef left_shift<late_parameter_t> late_left_shift;
typedef right_shift<late_parameter_t> late_right_shift;

typedef bit_and_equal<late_parameter_t> late_bit_and_equal;
typedef bit_or_equal<late_parameter_t> late_bit_or_equal;
typedef bit_xor_equal<late_parameter_t> late_bit_xor_equal;
typedef left_shift_equal<late_parameter_t> late_left_shift_equal;
typedef right_shift_equal<late_parameter_t> late_right_shift_equal;

typedef bit_not<late_parameter_t> late_bit_not;
//@}

/**
 * Negators
 * @{
 */
template<typename T>
struct binary_negate;
//@}

/**
 * Lazy negators
 * @{
 */
typedef binary_negate<late_parameter_t> late_binary_negate;
//@}

/**
 * Accessor operations
 * @{
 */
template<typename T>
struct pointer;
template<typename T>
struct address;
template<typename T>
struct arrow;
template<typename T, typename _Index>
struct index;
template<typename T, typename _Index>
struct index_emulation;
template<typename T>
struct dereference;
//@}

/**
 * Lazy accessor operations
 * @{
 */
typedef pointer<late_parameter_t> late_pointer;
typedef address<late_parameter_t> late_address;
typedef arrow<late_parameter_t> late_arrow;
typedef index<late_parameter_t, late_parameter_t> late_index;
typedef index_emulation<late_parameter_t, late_parameter_t> late_index_emulation;
typedef dereference<late_parameter_t> late_dereference;
//@}

/**
 * Affectation
 * @{
 */
template<typename T, typename U>
struct affect;
//@}

/**
 * Lazy affectation
 * @{
 */
typedef affect<late_parameter_t, late_parameter_t> late_affect;
//@}

/**
 * @{
 */
template<typename T, typename U>
struct comma;
template<typename T, typename _Member>
struct pointer_to_member;
template<typename T>
struct parenthesis;

typedef comma<late_parameter_t, late_parameter_t> late_comma;
typedef pointer_to_member<late_parameter_t, late_parameter_t> late_pointer_to_member;
typedef parenthesis<late_parameter_t> late_parenthesis;
//@}


#define __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, T1, T2, _M)\
  template<typename T, typename U>\
  struct name\
  {\
    constexpr _M(operator()(T1& a, T2& b) const, a op b)\
  };\
  template<typename T>\
  struct name<T, late_parameter_t>\
  {\
    template<typename U>\
    constexpr _M(operator()(T1& a, T2& b) const, a op b)\
  };\
  template<typename U>\
  struct name<late_parameter_t, U>\
  {\
    template<typename T>\
    constexpr _M(operator()(T1& a, T2& b) const, a op b)\
  };\
  template<>\
  struct name<late_parameter_t, late_parameter_t>\
  {\
    template<typename T, typename U>\
    constexpr _M(operator()(T1& a, T2& b) const, a op b)\
  };

#define __FALCON_FUNCTIONAL_OPERATORSTRANSFORM(_Proto, _Code) T& _Proto { return _Code; }

#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
  __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, const T, const U, CPP1X_DELEGATE_FUNCTION)\
  __FALCON_CREATE_FUNCTIONAL_OPERATORS(name##_equal, op##=, T, const U, __FALCON_FUNCTIONAL_OPERATORSTRANSFORM)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(plus      , +)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(minus     , -)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(multiplies, *)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(modulus   , %)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(divides   , /)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_and   , &)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_or    , |)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_xor   , ^)

template<typename T, typename U>
struct left_shift
{
  constexpr auto operator()(const T& a, const U& b) const -> decltype(a<<b)
  { return a << b; }
};

template<typename _CharT, typename Traits, typename T>
struct left_shift<std::basic_ostream<_CharT, Traits>, T>
{
  typedef std::basic_ostream<_CharT, Traits> ostream_type;

  ostream_type& operator()(ostream_type& os, const T& b) const
  { return os << b; }
};

template<typename T>
struct left_shift<T, late_parameter_t>
{
  template<typename U>
  constexpr auto operator()(const T& a, const U& b) const -> decltype(a<<b)
  { return a << b; }
};

template<typename _CharT, typename Traits>
struct left_shift<std::basic_ostream<_CharT, Traits>, late_parameter_t>
{
  typedef std::basic_ostream<_CharT, Traits> ostream_type;

  template<typename T>
  ostream_type& operator()(ostream_type& os, const T& b) const
  { return os << b; }

  ostream_type& operator()(ostream_type& os,
                                  ostream_type&(*manipulator)(ostream_type&)) const
  { return manipulator(os); }
};

template<>
struct left_shift<late_parameter_t, late_parameter_t>
{
  template<typename T, typename U>
  constexpr auto operator()(const T& a, const U& b) const -> decltype(a<<b)
  { return a << b; }

  template<typename _CharT, typename Traits, typename T>
  std::basic_ostream<_CharT, Traits>&
  operator()(std::basic_ostream<_CharT, Traits>& os, const T& b) const
  { return os << b; }
};

template<typename T, typename U>
struct right_shift
{
  constexpr auto operator()(const T& a, const U& b) const -> decltype(a>>b)
  { return a >> b; }
};

template<typename _CharT, typename Traits, typename T>
struct right_shift<std::basic_istream<_CharT, Traits>, T>
{
  typedef std::basic_istream<_CharT, Traits> istream_type;

  istream_type& operator()(istream_type& is, T& b) const
  { return is >> b; }
};

template<typename T>
struct right_shift<T, late_parameter_t>
{
  template<typename U>
  constexpr auto operator()(const T& a, const U& b) const -> decltype(a>>b)
  { return a >> b; }
};

template<typename _CharT, typename Traits>
struct right_shift<std::basic_istream<_CharT, Traits>, late_parameter_t>
{
  typedef std::basic_istream<_CharT, Traits> istream_type;

  template<typename T>
  istream_type& operator()(istream_type& is, T& b) const
  { return is >> b; }

  istream_type& operator()(istream_type& os,
                                  istream_type&(*manipulator)(istream_type&)) const
  { return manipulator(os); }
};

template<>
struct right_shift<late_parameter_t, late_parameter_t>
{
  template<typename T, typename U>
  constexpr auto operator()(const T& a, const U& b) const -> decltype(a>>b)
  { return a >> b; }

  template<typename _CharT, typename Traits, typename T>
  std::basic_istream<_CharT, Traits>&
  operator()(std::basic_istream<_CharT, Traits>& is, T& b) const
  { return is >> b; }
};

#undef __FALCON_FUNCTIONAL_OPERATORSTRANSFORM

#define _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS const

#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS
#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
  __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS T, const U, CPP1X_DELEGATE_FUNCTION)\

_FALCON_CREATE_FUNCTIONAL_OPERATORS(equal_to     , ==)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(not_equal_to , !=)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(greater      , >)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(less         , <)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(greater_equal, >=)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(less_equal   , <=)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(logical_and  , &&)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(logical_or   , ||)

#undef __FALCON_CREATE_FUNCTIONAL_OPERATORS
#define __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, Type)\
  template<typename T>\
  struct name\
  {\
    constexpr CPP1X_DELEGATE_FUNCTION(operator()(Type& a) const, op(a))\
  };\
  template<>\
  struct name<late_parameter_t>\
  {\
    template<typename T>\
    constexpr CPP1X_DELEGATE_FUNCTION(operator()(Type& a) const, op(a))\
  };

#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS
#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
  __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS T)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(unary_negate , -)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(unary_plus   , +)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(binary_negate, !)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_not      , ~)


#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS
#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
  __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS T)

#undef _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS
#define _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS

_FALCON_CREATE_FUNCTIONAL_OPERATORS(increment, ++)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(decrement, --)

#undef _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS
#undef __FALCON_CREATE_FUNCTIONAL_OPERATORS
#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS

#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
  template<typename T>\
  struct name\
  {\
    constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, op(a))\
    constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a) const, op(a))\
  };\
  template<>\
  struct name<late_parameter_t>\
  {\
    template<typename T>\
    constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, op(a))\
    template<typename T>\
    constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a) const, op(a))\
  };

_FALCON_CREATE_FUNCTIONAL_OPERATORS(address    , &)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(pointer    , *)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(dereference, *&)

#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS


template<typename T, typename U>
struct affect
{
  T& operator()(T& a, const U& b) const
  { return a = b; }
};

template<typename T>
struct affect<T, late_parameter_t>
{
  template<typename U>
  T& operator()(T& a, const U& b) const
  { return a = b; }
};

template<typename U>
struct affect<late_parameter_t, U>
{
  template<typename T>
  T& operator()(T& a, const U& b) const
  { return a = b; }
};

template<>
struct affect<late_parameter_t, late_parameter_t>
{
  template<typename T, typename U>
  T& operator()(T& a, const U& b) const
  { return a = b; }
};


template<typename T, typename U>
struct equivalent
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const U& b) const,
                                    !(a < b || a > b))
};

template<typename T>
struct equivalent<T, late_parameter_t>
{
  template<typename U>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const U& b) const,
                                    !(a < b || a > b))
};

template<typename U>
struct equivalent<late_parameter_t, U>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const U& b) const,
                                    !(a < b || a > b))
};

template<>
struct equivalent<late_parameter_t, late_parameter_t>
{
  template<typename T, typename U>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const U& b) const,
                                    !(a < b || a > b))
};


template<typename T>
struct post_increment
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, a++)
};

template<>
struct post_increment<late_parameter_t>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, a++)
};


template<typename T>
struct post_decrement
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, a--)
};

template<>
struct post_decrement<late_parameter_t>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, a--)
};


template<typename T>
struct arrow
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, a.operator->())
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a) const, a.operator->())
};

template<>
struct arrow<late_parameter_t>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a) const, a.operator->())
};


template<typename T, typename _Index = int>
struct index
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& __index) const,
                                    a[__index])
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const _Index& __index) const,
                                    a[__index])
};

template<typename T>
struct index<T, late_parameter_t>
{
  template<typename _Index>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& __index) const,
                                    a[__index])
};

template<typename _Index>
struct index<late_parameter_t, _Index>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& __index) const,
                                    a[__index])
};

template<>
struct index<late_parameter_t, late_parameter_t>
{
  template<typename T, typename _Index>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& __index) const,
                                    a[__index])
};


template<typename T, typename _Index = int>
struct index_emulation
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& index) const,
                                    *(a + index))
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const _Index& index) const,
                                    *(a + index))
};

template<typename T>
struct index_emulation<T, late_parameter_t>
{
  template<typename _Index>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& index) const,
                                    *(a + index))
};

template<typename _Index>
struct index_emulation<late_parameter_t, _Index>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& index) const,
                                    *(a + index))
};

template<>
struct index_emulation<late_parameter_t, late_parameter_t>
{
  template<typename T, typename _Index>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const _Index& index) const,
                                    *(a + index))
};


template<typename T, typename U>
struct comma
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, U& b) const, (a , b))
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, const U& b) const, (a , b))
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, U& b) const, (a , b))
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& a, const U& b) const, (a , b))
};
template<typename T>
struct comma<T, late_parameter_t>
{
  template<typename U>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, U& b) const, (a , b))
};
template<typename U>
struct comma<late_parameter_t, U>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, U& b) const, (a , b))
};
template<>
struct comma<late_parameter_t, late_parameter_t>
{
  template<typename T, typename U>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, U& b) const, (a , b))
};


template<typename T, typename _Member>
struct pointer_to_member
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, _Member m) const, ((a.*m)()))

  template<typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, _Member m, _Args&&... args) const,
                                    (a.*m)(std::forward<_Args>(args)...))
};

template<typename T>
struct pointer_to_member<T, late_parameter_t>
{
  template<typename _Member>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, _Member m) const, ((a.*m)()))

  template<typename _Member, typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, _Member m, _Args&&... args) const,
                                    (a.*m)(std::forward<_Args>(args)...))
};

template<>
struct pointer_to_member<late_parameter_t, late_parameter_t>
{
  template<typename T, typename _Member>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, _Member m) const, ((a.*m)()))

  template<typename T, typename _Member, typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, _Member m, _Args&&... args) const,
                                    (a.*m)(std::forward<_Args>(args)...))
};

template<typename _Result, typename T, typename... _Args>
struct pointer_to_member<late_parameter_t, _Result(T::*)(_Args...)>
: pointer_to_member<T, _Result(T::*)(_Args...)>
{};

template<typename _Result, typename T, typename... _Args>
struct pointer_to_member<late_parameter_t, _Result(T::*)(_Args...) const>
: pointer_to_member<T, _Result(T::*)(_Args...) const>
{};

template<typename T>
struct parenthesis
{
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& f) const, f())

  template<typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& f, _Args&&... args) const,
                                    f(std::forward<_Args>(args)...))

  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& f) const, f())

  template<typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& f, _Args&&... args) const,
                                    f(std::forward<_Args>(args)...))
};

template<>
struct parenthesis<late_parameter_t>
{
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& f) const, f())

  template<typename T, typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& f, _Args&&... args) const,
                                    f(std::forward<_Args>(args)...))

  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& f) const, f())

  template<typename T, typename... _Args>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(const T& f, _Args&&... args) const,
                                    f(std::forward<_Args>(args)...))
};

}

#endif
