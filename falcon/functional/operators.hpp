#ifndef FALCON_FUNCTIONAL_OPERATORS_HPP
#define FALCON_FUNCTIONAL_OPERATORS_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
#include <falcon/c++1x/syntax.hpp>
#endif

#include <iosfwd>
#include FALCON_BOOST_OR_STD_TRAITS(remove_const)
#include <boost/concept_check.hpp>

namespace falcon {

/**
 * Arithmetic operations
 * @{
 */
template<typename T = void, typename U = T>
struct plus;
template<typename T = void, typename U = T>
struct minus;
template<typename T = void, typename U = T>
struct multiplies;
template<typename T = void, typename U = T>
struct modulus;
template<typename T = void, typename U = T>
struct divides;

CPP_GLOBAL_CONSTEXPR plus<> plus_f;
CPP_GLOBAL_CONSTEXPR minus<> minus_f;
CPP_GLOBAL_CONSTEXPR multiplies<> multiplies_f;
CPP_GLOBAL_CONSTEXPR modulus<> modulus_f;
CPP_GLOBAL_CONSTEXPR divides<> divides_f;

template<typename T = void, typename U = T>
struct plus_equal;
template<typename T = void, typename U = T>
struct minus_equal;
template<typename T = void, typename U = T>
struct multiplies_equal;
template<typename T = void, typename U = T>
struct modulus_equal;
template<typename T = void, typename U = T>
struct divides_equal;

CPP_GLOBAL_CONSTEXPR plus_equal<> plus_equal_f;
CPP_GLOBAL_CONSTEXPR minus_equal<> minus_equal_f;
CPP_GLOBAL_CONSTEXPR multiplies_equal<> multiplies_equal_f;
CPP_GLOBAL_CONSTEXPR modulus_equal<> modulus_equal_f;
CPP_GLOBAL_CONSTEXPR divides_equal<> divides_equal_f;


template<typename T = void>
struct increment;
template<typename T = void>
struct decrement;
template<typename T = void>
struct post_increment;
template<typename T = void>
struct post_decrement;

CPP_GLOBAL_CONSTEXPR increment<> increment_f;
CPP_GLOBAL_CONSTEXPR decrement<> decrement_f;
CPP_GLOBAL_CONSTEXPR post_increment<> post_increment_f;
CPP_GLOBAL_CONSTEXPR post_decrement<> post_decrement_f;

template<typename T = void>
struct increment_emulation;
template<typename T = void>
struct decrement_emulation;

CPP_GLOBAL_CONSTEXPR increment_emulation<> increment_emulation_f;
CPP_GLOBAL_CONSTEXPR decrement_emulation<> decrement_emulation_f;

template<typename T = void>
struct unary_negate;
template<typename T = void>
struct unary_plus;

CPP_GLOBAL_CONSTEXPR unary_negate<> unary_negate_f;
CPP_GLOBAL_CONSTEXPR binary_negate<> binary_negate_f;
//@}

/**
 * Comparisons
 * @{
 */
template<typename T = void, typename U = T>
struct equal_to;
template<typename T = void, typename U = T>
struct not_equal_to;
template<typename T = void, typename U = T>
struct greater;
template<typename T = void, typename U = T>
struct less;
template<typename T = void, typename U = T>
struct greater_equal;
template<typename T = void, typename U = T>
struct less_equal;
template<typename T = void, typename U = T>
struct equivalent;

CPP_GLOBAL_CONSTEXPR equal_to<> equal_to_f;
CPP_GLOBAL_CONSTEXPR not_equal_to<> not_equal_to_f;
CPP_GLOBAL_CONSTEXPR greater<> greater_f;
CPP_GLOBAL_CONSTEXPR less<> less_f;
CPP_GLOBAL_CONSTEXPR greater_equal<> greater_equal_f;
CPP_GLOBAL_CONSTEXPR less_equal<> less_equal_f;
CPP_GLOBAL_CONSTEXPR equivalent<> equivalent_f;
//@}

/**
 * Logical operations
 * @{
 */
template<typename T = void, typename U = T>
struct logical_and;
template<typename T = void, typename U = T>
struct logical_or;

CPP_GLOBAL_CONSTEXPR logical_and<> logical_and_f;
CPP_GLOBAL_CONSTEXPR logical_or<> logical_or_f;
//@}

/**
 * Bitwise operations
 * @{
 */
template<typename T = void, typename U = T>
struct bit_and;
template<typename T = void, typename U = T>
struct bit_or;
template<typename T = void, typename U = T>
struct bit_xor;
template<typename T = void, typename U = T>
struct left_shift;
template<typename T = void, typename U = T>
struct right_shift;

CPP_GLOBAL_CONSTEXPR bit_and<> bit_and_f;
CPP_GLOBAL_CONSTEXPR bit_or<> bit_or_f;
CPP_GLOBAL_CONSTEXPR bit_xor<> bit_xor_f;
CPP_GLOBAL_CONSTEXPR left_shift<> left_shift_f;
CPP_GLOBAL_CONSTEXPR right_shift<> right_shift_f;

template<typename T = void, typename U = T>
struct bit_and_equal;
template<typename T = void, typename U = T>
struct bit_or_equal;
template<typename T = void, typename U = T>
struct bit_xor_equal;
template<typename T = void, typename U = T>
struct left_shift_equal;
template<typename T = void, typename U = T>
struct right_shift_equal;

CPP_GLOBAL_CONSTEXPR bit_and_equal<> bit_and_equal_f;
CPP_GLOBAL_CONSTEXPR bit_or_equal<> bit_or_equal_f;
CPP_GLOBAL_CONSTEXPR bit_xor_equal<> bit_xor_equal_f;
CPP_GLOBAL_CONSTEXPR left_shift_equal<> left_shift_equal_f;
CPP_GLOBAL_CONSTEXPR right_shift_equal<> right_shift_equal_f;

template<typename T = void>
struct bit_not;

CPP_GLOBAL_CONSTEXPR bit_not<> bit_not_f;
//@}

/**
 * Negators
 * @{
 */
template<typename T = void>
struct binary_negate;

CPP_GLOBAL_CONSTEXPR binary_negate<> binary_negate_f;
//@}

/**
 * Accessor operations
 * @{
 */
template<typename T = void>
struct pointer;
template<typename T = void>
struct address;
template<typename T = void>
struct arrow;
template<typename T = void, typename Index = void>
struct index;
template<typename T = void, typename Index = void>
struct index_emulation;

CPP_GLOBAL_CONSTEXPR pointer<> pointer_f;
CPP_GLOBAL_CONSTEXPR address<> address_f;
CPP_GLOBAL_CONSTEXPR arrow<> arrow_f;
CPP_GLOBAL_CONSTEXPR index<> index_f;
CPP_GLOBAL_CONSTEXPR index_emulation<> index_emulation_f;
//@}

/**
 * Affectation
 * @{
 */
template<typename T = void, typename U = T>
struct affect;

CPP_GLOBAL_CONSTEXPR affect<> affect_f;
//@}

/**
 * @{
 */
template<typename T = void, typename U = T>
struct comma;

CPP_GLOBAL_CONSTEXPR comma<> comma_f;

#if __cplusplus >= 201103L
template<typename T = void, typename Member = void>
struct pointer_to_member;

CPP_GLOBAL_CONSTEXPR pointer_to_member<> pointer_to_member_f;
#endif
//@}


#define FALCON_CREATE_OPERATOR(name, op, T1, R)         \
  template<typename T, typename U>                      \
  struct name                                           \
  {                                                     \
    typedef T first_argument_type;                      \
    typedef U second_argument_type;                     \
    typedef T result_type;                              \
                                                        \
    CPP_CONSTEXPR R operator()(T1& a, const U& b) const \
    { return a op b; }                                  \
  };

#if __cplusplus >= 201103L

#define FALCON_CREATE_OPERATOR_VOID(name, op, X) \
  template<>                                     \
  struct name<void, void>                        \
  {                                              \
    template<typename T, typename U>             \
    constexpr CPP1X_DELEGATE_FUNCTION(           \
      operator()(T&& a, U&& b) const             \
    , std::forward<T>(a) op std::forward<U>(b))  \
  };

#else

#define FALCON_CREATE_OPERATOR_VOID(name, op, T1) \
  template<>                                      \
  struct name<void, void>                         \
  {                                               \
    template<typename T, typename U>              \
    typename name<T>::result_type                 \
    operator()(T1& a, const U& b) const           \
    { return a op b; }                            \
  };

#endif

#define FALCON_CREATE_OPERATOR2(name, op)      \
  FALCON_CREATE_OPERATOR(name, op, const T, T) \
  FALCON_CREATE_OPERATOR(name##_equal, op##=, T, T&)

#define FALCON_CREATE_OPERATOR_VOID2(name, op)   \
  FALCON_CREATE_OPERATOR_VOID(name, op, const T) \
  FALCON_CREATE_OPERATOR_VOID(name##_equal, op##=, T)

#define FALCON_CREATE_OPERATORS(name, op) \
  FALCON_CREATE_OPERATOR2(name, op)       \
  FALCON_CREATE_OPERATOR_VOID2(name, op)

FALCON_CREATE_OPERATORS(plus      , +)
FALCON_CREATE_OPERATORS(minus     , -)
FALCON_CREATE_OPERATORS(multiplies, *)
FALCON_CREATE_OPERATORS(modulus   , %)
FALCON_CREATE_OPERATORS(divides   , /)

FALCON_CREATE_OPERATORS(bit_and   , &)
FALCON_CREATE_OPERATORS(bit_or    , |)
FALCON_CREATE_OPERATORS(bit_xor   , ^)

template<typename T, typename U>
struct affect
{
  typedef T argument_type;
  typedef T result_type;

  CPP_CONSTEXPR T& operator()(T& a, U CPP_RVALUE_OR_CONST_REFERENCE b) const
  { return a = FALCON_FORWARD(U, b); }
};

FALCON_CREATE_OPERATOR_VOID(affect, =, noop)

FALCON_CREATE_OPERATOR2(left_shift , <<)
FALCON_CREATE_OPERATOR2(right_shift, >>)

template<typename CharT, typename Traits, typename T>
struct left_shift<std::basic_ostream<CharT, Traits>, T>
{
  typedef std::basic_ostream<CharT, Traits> first_argument_type;
  typedef T second_argument_type;
  typedef first_argument_type& result_type;

  result_type operator()(first_argument_type& os, const T& b) const
  { return os << b; }
};

template<typename CharT, typename Traits, typename T>
struct right_shift<std::basic_istream<CharT, Traits>, T>
{
  typedef std::basic_istream<CharT, Traits> first_argument_type;
  typedef T second_argument_type;
  typedef first_argument_type& result_type;

  result_type operator()(first_argument_type& is, const T& b) const
  { return is >> b; }
};

#if __cplusplus >= 201103L
FALCON_CREATE_OPERATOR_VOID(left_shift_equal , <<=, noop)
FALCON_CREATE_OPERATOR_VOID(right_shift_equal, >>=, noop)

template<>
struct left_shift<void, void>
{
  template<typename T, typename U>
  constexpr auto operator()(const T& a, const U& b) const
  -> decltype(a<<b)
  { return a << b; }

  template<typename CharT, typename Traits, typename T>
  std::basic_ostream<CharT, Traits>&
  operator()(std::basic_ostream<CharT, Traits>& os, const T& b) const
  { return os << b; }
};

template<>
struct right_shift<void, void>
{
  template<typename T, typename U>
  constexpr auto operator()(const T& a, const U& b) const
  -> decltype(a>>b)
  { return a >> b; }

  template<typename CharT, typename Traits, typename T>
  std::basic_istream<CharT, Traits>&
  operator()(std::basic_istream<CharT, Traits>& is, T& b) const
  { return is >> b; }
};
#endif

#undef FALCON_CREATE_OPERATORS

#if __cplusplus >= 201103L
# define FALCON_CREATE_OPERATORS(name, op)        \
  FALCON_CREATE_OPERATOR(name, op, const T, bool) \
  FALCON_CREATE_OPERATOR_VOID(name, op, const T)
#else
# define FALCON_CREATE_OPERATORS(name, op) \
  FALCON_CREATE_OPERATOR(name, op, const T, bool)
#endif

FALCON_CREATE_OPERATORS(equal_to     , ==)
FALCON_CREATE_OPERATORS(not_equal_to , !=)
FALCON_CREATE_OPERATORS(greater      , >)
FALCON_CREATE_OPERATORS(less         , <)
FALCON_CREATE_OPERATORS(greater_equal, >=)
FALCON_CREATE_OPERATORS(less_equal   , <=)

FALCON_CREATE_OPERATORS(logical_and  , &&)
FALCON_CREATE_OPERATORS(logical_or   , ||)


#undef FALCON_CREATE_OPERATOR
#undef FALCON_CREATE_OPERATOR_VOID
#undef FALCON_CREATE_OPERATORS

#define FALCON_CREATE_OPERATOR(name, op)     \
  template<typename T>                       \
  struct name                                \
  {                                          \
    typedef T argument_type;                 \
    typedef FALCON_UNARY_RETURN result_type; \
                                             \
    CPP_CONSTEXPR result_type                \
    operator()(FALCON_UNARY_PARAM & a) const \
    { return op a; }                         \
  };

#define FALCON_UNARY_RETURN T
#define FALCON_UNARY_PARAM const T

#if __cplusplus >= 201103L

#define FALCON_CREATE_OPERATOR_VOID(name, op) \
  template<>                                  \
  struct name<void>                           \
  {                                           \
    template<typename T>                      \
    constexpr CPP1X_DELEGATE_FUNCTION(        \
      operator()(T && a) const                \
    , op std::forward<T>(a))                  \
  };

#else

#define FALCON_CREATE_OPERATOR_VOID(name, op) \
  template<>                                  \
  struct name<void>                           \
  {                                           \
    template<typename T>                      \
    typename name<T>::result_type             \
    operator()(FALCON_UNARY_PARAM & a) const  \
    { return op FALCON_FORWARD(T, a); }       \
  };

#endif

#define FALCON_CREATE_OPERATORS(name, op) \
  FALCON_CREATE_OPERATOR(name, op)        \
  FALCON_CREATE_OPERATOR_VOID(name, op)

FALCON_CREATE_OPERATORS(unary_negate , -)
FALCON_CREATE_OPERATORS(unary_plus   , +)
FALCON_CREATE_OPERATORS(binary_negate, !)
FALCON_CREATE_OPERATORS(bit_not      , ~)

#undef FALCON_UNARY_RETURN
#define FALCON_UNARY_RETURN T &

#undef FALCON_UNARY_PARAM
#define FALCON_UNARY_PARAM T

FALCON_CREATE_OPERATORS(increment, ++)
FALCON_CREATE_OPERATORS(decrement, --)

#undef FALCON_UNARY_RETURN
#define FALCON_UNARY_RETURN T *

FALCON_CREATE_OPERATORS(address, &)

FALCON_CREATE_OPERATOR_VOID(pointer, *)

template<typename T>
struct pointer
{
  typedef T argument_type;
  typedef typename T::value_type& result_type;

  CPP_CONSTEXPR result_type
  operator()(T & a) const
  { return *a; }
};

template<typename T>
struct pointer<const T>
{
  typedef T argument_type;
  typedef const typename T::value_type& result_type;

  CPP_CONSTEXPR result_type
  operator()(const T & a) const
  { return *a; }
};

template<typename T>
struct pointer<T*>
{
  typedef T* argument_type;
  typedef T& result_type;

  CPP_CONSTEXPR result_type
  operator()(T* a) const
  { return *a; }
};

template<typename T>
struct pointer<T[]> : pointer<T*>
{};

template<typename T, std::size_t N>
struct pointer<T[N]> : pointer<T*>
{ typedef T argument_type[N]; };


template<typename T, typename U>
struct equivalent
{
  typedef T first_argument_type;
  typedef U second_argument_type;
  typedef bool result_type;

  CPP_CONSTEXPR bool operator()(const T& a, const U& b) const
  { return !(a < b || a > b); }
};

template<>
struct equivalent<void, void>
{
  template<typename T, typename U>
  constexpr bool operator()(const T& a, const U& b) const
  { return !(a < b || a > b); }
};


template<typename T>
struct post_increment
{
  typedef T argument_type;
  typedef T& result_type;

  CPP_CONSTEXPR result_type operator()(T& a) const
  { return a++; }
};

template<>
struct post_increment<void>
{
  template<typename T>
  CPP_CONSTEXPR T& operator()(T& a) const
  { return a++; }
};


template<typename T>
struct post_decrement
{
  typedef T argument_type;
  typedef T& result_type;

  CPP_CONSTEXPR result_type operator()(T& a) const
  { return a--; }
};

template<>
struct post_decrement<void>
{
  template<typename T>
  CPP_CONSTEXPR T& operator()(T& a) const
  { return a--; }
};


template<typename T>
struct increment_emulation
{
  typedef T argument_type;
  typedef T& result_type;

  result_type operator()(T& a) const
  {
    a = static_cast<T>(a + 1);
    return a;
  }
};

template<>
struct increment_emulation<void>
{
  template<typename T>
  T& operator()(T& a) const
  {
    a = static_cast<T>(a + 1);
    return a;
  }
};


template<typename T>
struct decrement_emulation
{
  typedef T argument_type;
  typedef T& result_type;

  result_type operator()(T& a) const
  {
    a = static_cast<T>(a - 1);
    return a;
  }
};

template<>
struct decrement_emulation<void>
{
  template<typename T>
  T& operator()(T& a) const
  {
    a = static_cast<T>(a - 1);
    return a;
  }
};


template<typename T>
struct arrow
{
  typedef T argument_type;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE
    ::remove_const<T>::type::type& result_type;

  CPP_CONSTEXPR result_type operator()(T& a) const
  { return a.operator->(); }
};

template<>
struct arrow<void>
{
#if __cplusplus >= 201103L
  template<typename T>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T&& a) const
  , std::forward<T>(a).operator->())
#else
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<T>::type::type&
  operator()(T& a) const
  { return a.operator->(); }
#endif
};


template<typename T, typename Index>
struct index
{
  typedef T first_argument_type;
  typedef typename default_or_type<std::size_t, Index, void>
    ::type second_argument_type;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE
    ::remove_const<T>::type::value_type& result_type;

  CPP_CONSTEXPR result_type operator()(T& a, second_argument_type i) const
  { return a[i]; }
};

template<typename T, typename Index>
struct index<T*, Index>
{
  typedef T* first_argument_type;
  typedef typename default_or_type<std::size_t, Index, void>
    ::type second_argument_type;
  typedef T& result_type;

  CPP_CONSTEXPR result_type operator()(T& a, second_argument_type i) const
  { return a[i]; }
};

template<typename T, typename Index>
struct index<T[], Index>
: index<T*, Index>
{};

template<typename T, std::size_t N, typename Index>
struct index<T[N], Index>
: index<T*, Index>
{ typedef T first_argument_type[N]; };

template<>
struct index<void, void>
{
  template<typename T, typename Index>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T& a, const Index& i) const
  , a[i])
#else
  typename index<T, Index>::result_type
  operator()(T& a, const Index& i) const
  { return a[i]; }
#endif
};


template<typename T, typename Index>
struct index_emulation
{
  typedef T first_argument_type;
  typedef typename default_or_type<std::size_t, Index, void>
    ::type second_argument_type;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE
    ::remove_const<T>::type::type& result_type;

  CPP_CONSTEXPR result_type operator()(T& a, second_argument_type i) const
  { return *(a + i); }
};

template<typename T, typename Index>
struct index_emulation<T*, Index>
: index<T*, Index>
{};

template<typename T, typename Index>
struct index_emulation<T[], Index>
: index<T*, Index>
{};

template<typename T, std::size_t N, typename Index>
struct index_emulation<T[N], Index>
: index<T*, Index>
{ typedef T first_argument_type[N]; };

template<>
struct index_emulation<void, void>
{
  template<typename T, typename Index>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T& a, const Index& i) const
  , *(a + i))
#else
  typename index_emulation<T, Index>::result_type
  operator()(T& a, const Index& i) const
  { return *(a + i); }
#endif
};


template<typename T, typename U>
struct comma
{
  typedef T first_argument_type;
  typedef U second_argument_type;
  typedef T& result_type;

  constexpr result_type operator()(T& a, U& b) const
  { return (a , b); }
};

template<>
struct comma<void, void>
{
  template<typename T, typename U>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, U& b) const, (a , b))
#else
  typename comma<T, U>::result_type
  operator()(T& a, U& b) const
  { return (a , b); }
#endif
};

#if __cplusplus >= 201103L
template<typename T, typename Member>
struct pointer_to_member
{
  typedef T first_argument_type;
  typedef Member second_argument_type;
  typedef decltype(std::declval<T>().*std::declval<Member>()) result_type;

  constexpr result_type operator()(T& a, Member m) const
  { return a.*m; };
};

template<>
struct pointer_to_member<void, void>
{
  template<typename T, typename Member>
  constexpr CPP1X_DELEGATE_FUNCTION(operator()(T& a, Member m) const, a.*m)
};
#endif

#undef FALCON_CREATE_OPERATOR
#undef FALCON_CREATE_OPERATOR2
#undef FALCON_CREATE_OPERATOR_VOID
#undef FALCON_CREATE_OPERATOR_VOID2
#undef FALCON_CREATE_OPERATORS
#undef FALCON_UNARY_RETURN
#undef FALCON_UNARY_PARAM

}

#endif
