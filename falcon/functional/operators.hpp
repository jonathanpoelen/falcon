#ifndef FALCON_FUNCTIONAL_OPERATORS_HPP
#define FALCON_FUNCTIONAL_OPERATORS_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/default_or_type.hpp>
#include <falcon/type_traits/internal_reference.hpp>

#include <utility>
#include <type_traits>
#if __cplusplus > 201103L
# include <functional>
#endif

namespace falcon {

  namespace aux_ {
    struct is_transparent_t;
  }

  /**
   * Arithmetic operations
   * @{
   */
#if __cplusplus > 201103L
  template<class T = void> using plus = std::plus<T>;
  template<class T = void> using minus = std::minus<T>;
  template<class T = void> using multiplies = std::multiplies<T>;
  template<class T = void> using divides = std::divides<T>;
  template<class T = void> using modulus = std::modulus<T>;
#else
  template<class T = void> struct plus;
  template<class T = void> struct minus;
  template<class T = void> struct multiplies;
  template<class T = void> struct modulus;
  template<class T = void> struct divides;
#endif

  template<class T = void> struct plus_equal;
  template<class T = void> struct minus_equal;
  template<class T = void> struct multiplies_equal;
  template<class T = void> struct modulus_equal;
  template<class T = void> struct divides_equal;

  template<class T = void> struct increment;
  template<class T = void> struct decrement;
  template<class T = void> struct post_increment;
  template<class T = void> struct post_decrement;

  /// \brief T += 1
  template<class T = void> struct increment2;
  /// \brief T -= 1
  template<class T = void> struct decrement2;

  /// \brief T = static_cast< T>(T + 1)
  template<class T = void> struct increment3;
  /// \brief T = static_cast< T>(T - 1)
  template<class T = void> struct decrement3;

#if __cplusplus > 201103L
  template<class T = void> using negate = std::negate<T>;
#else
  template<class T = void> struct negate;
#endif
  template<class T = void> struct unary_plus;
  //@}


  /**
   * Comparisons
   * @{
   */
#if __cplusplus > 201103L
  template<class T = void> using equal_to = std::equal_to<T>;
  template<class T = void> using not_equal_to = std::not_equal_to<T>;
  template<class T = void> using greater = std::greater<T>;
  template<class T = void> using less = std::less<T>;
  template<class T = void> using greater_equal = std::greater_equal<T>;
  template<class T = void> using less_equal = std::less_equal<T>;
#else
  template<class T = void> struct equal_to;
  template<class T = void> struct not_equal_to;
  template<class T = void> struct greater;
  template<class T = void> struct less;
  template<class T = void> struct greater_equal;
  template<class T = void> struct less_equal;
#endif

  template<class T = void> struct equivalent;
  template<class T = void> struct equivalent2;
  //@}


  /**
   * Logical operations
   * @{
   */
#if __cplusplus > 201103L
  template<class T = void> using logical_and = std::logical_and<T>;
  template<class T = void> using logical_or = std::logical_or<T>;
  template<class T = void> using logical_not = std::logical_not<T>;
#else
  template<class T = void> struct logical_and;
  template<class T = void> struct logical_or;
  template<class T = void> struct logical_not;
#endif
  //@}


  /**
   * Bitwise operations
   * @{
   */
#if __cplusplus > 201103L
  template<class T = void> using bit_and = std::bit_and<T>;
  template<class T = void> using bit_or = std::bit_or<T>;
  template<class T = void> using bit_xor = std::bit_xor<T>;
#else
  template<class T = void> struct bit_and;
  template<class T = void> struct bit_or;
  template<class T = void> struct bit_xor;
#endif

  template<class T = void> struct bit_and_equal;
  template<class T = void> struct bit_or_equal;
  template<class T = void> struct bit_xor_equal;

  template<class T = void> struct left_shift;
  template<class T = void> struct right_shift;

  template<class T = void> struct left_shift_equal;
  template<class T = void> struct right_shift_equal;

  template<class T = void> struct bit_not;
  //@}


  /**
   * Accessor operations
   * @{
   */
  template<class T = void> struct dereference;
  template<class T = void> struct address;
  template<class T = void> struct arrow;
  template<class T = void, class Index = void> struct index;
  /// \brief *(T + Index)
  template<class T = void, typename Index = void> struct index2;
  //@}


  /**
   * Affectation
   * @{
   */
  template<class T = void> struct assign;
  //@}


  /**
   * @{
   */
  template<class T = void, class U = T> struct comma;
  template<class T = void, class Member = void> struct pointer_to_member;
  //@}

#define FALCON_MAKE_BINARY_OP(name, op, Tres, T1, T2)\
  template<class T>\
  struct name\
  {\
    constexpr name() noexcept {}\
\
    Tres operator()(T1 x, T2 y) const\
    { return x op y; }\
\
    typedef T first_argument_type;\
    typedef T second_argument_type;\
    typedef Tres result_type;\
  };\
\
  template<>\
  struct name<void>\
  {\
    constexpr name() noexcept {}\
\
    template<class T, class U>\
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      operator()(T&& x, U&& y) const\
    , std::forward<T>(x) op std::forward<U>(y))\
\
    typedef aux_::is_transparent_t is_transparent;\
  };

#if __cplusplus == 201103L
  FALCON_MAKE_BINARY_OP(plus,       +, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(minus,      -, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(multiplies, *, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(modulus,    %, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(divides,    /, T, T const &, T const &)

  FALCON_MAKE_BINARY_OP(equal_to,      ==, bool, T const &, T const &)
  FALCON_MAKE_BINARY_OP(not_equal_to,  !=, bool, T const &, T const &)
  FALCON_MAKE_BINARY_OP(greater,       > , bool, T const &, T const &)
  FALCON_MAKE_BINARY_OP(less,          < , bool, T const &, T const &)
  FALCON_MAKE_BINARY_OP(greater_equal, >=, bool, T const &, T const &)
  FALCON_MAKE_BINARY_OP(less_equal,    <=, bool, T const &, T const &)

  FALCON_MAKE_BINARY_OP(logical_and, &&, bool, T const &, T const &)
  FALCON_MAKE_BINARY_OP(logical_or,  ||, bool, T const &, T const &)

  FALCON_MAKE_BINARY_OP(bit_and, &, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(bit_or,  |, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(bit_xor, ^, T, T const &, T const &)
#endif

  FALCON_MAKE_BINARY_OP(plus_equal,       +=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(minus_equal,      -=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(multiplies_equal, *=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(modulus_equal,    %=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(divides_equal,    /=, T&, T&, T const &)

  FALCON_MAKE_BINARY_OP(bit_and_equal,    &=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(bit_or_equal,     |=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(bit_xor_equal,    ^=, T&, T&, T const &)

  FALCON_MAKE_BINARY_OP(left_shift,       <<, T, T const &, T const &)
  FALCON_MAKE_BINARY_OP(right_shift,      >>, T, T const &, T const &)

  FALCON_MAKE_BINARY_OP(left_shift_equal, <<=, T&, T&, T const &)
  FALCON_MAKE_BINARY_OP(right_shift_equal,>>=, T&, T&, T const &)

  FALCON_MAKE_BINARY_OP(assign,           =, T&, T&, T const &)

#undef FALCON_MAKE_BINARY_OP

#define FALCON_MAKE_UNARY_OP(name, op, Tres, T1)\
  template<class T>\
  struct name\
  {\
    constexpr name() noexcept {}\
\
    Tres operator()(T1 x) const\
    { return op x; }\
\
    typedef T argument_type;\
    typedef Tres result_type;\
  };\
\
  template<>\
  struct name<void>\
  {\
    constexpr name() noexcept {}\
\
    template<class T>\
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      operator()(T&& x) const\
    , op std::forward<T>(x))\
\
    typedef aux_::is_transparent_t is_transparent;\
  };

#if __cplusplus == 201103L
  FALCON_MAKE_UNARY_OP(negate, +, T, T const &)

  FALCON_MAKE_UNARY_OP(logical_not, !, bool, T const &)
#endif

  FALCON_MAKE_UNARY_OP(increment, ++, T&, T&)
  FALCON_MAKE_UNARY_OP(decrement, --, T&, T&)

  FALCON_MAKE_UNARY_OP(unary_plus, +, T, T const &)

  FALCON_MAKE_UNARY_OP(
    dereference, *, typename internal_reference<T>::type, T&)
  FALCON_MAKE_UNARY_OP(address, &, T*, T&)

  FALCON_MAKE_UNARY_OP(bit_not, ~, T, T const &)

#undef FALCON_MAKE_UNARY_OP

  template<class T>
  struct dereference<T*>
  {
    constexpr dereference() noexcept {}

    constexpr T& operator()(T* x) const noexcept
    { return *x; }

    typedef T argument_type;
    typedef T& result_type;
  };

  template<class T>
  struct dereference<T[]> : dereference<T*>
  {};

  template<typename T, std::size_t N>
  struct dereference<T[N]> : dereference<T*>
  { typedef T argument_type[N]; };

#define FALCON_MAKE_UNARY_OP2(name, post_op, Tres, T1)\
  template<class T>\
  struct name\
  {\
    constexpr name() noexcept {}\
\
    Tres operator()(T1 x) const\
    { return x post_op; }\
\
    typedef T argument_type;\
    typedef Tres result_type;\
  };\
\
  template<>\
  struct name<void>\
  {\
    constexpr name() noexcept {}\
\
    template<class T>\
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      operator()(T&& x) const\
    , std::forward<T>(x) post_op)\
\
    typedef aux_::is_transparent_t is_transparent;\
  };

  FALCON_MAKE_UNARY_OP2(post_increment, ++, T&, T&)
  FALCON_MAKE_UNARY_OP2(post_decrement, --, T&, T&)

  FALCON_MAKE_UNARY_OP2(increment2, += 1, T&, T&)
  FALCON_MAKE_UNARY_OP2(decrement2, -= 1, T&, T&)

#undef FALCON_MAKE_UNARY_OP2


#define FALCON_MAKE_UNARY_OP3(name, post_op, Tres, T1)\
  template<class T>\
  struct name\
  {\
    constexpr name() noexcept {}\
\
    Tres operator()(T1 x) const\
    { return (x = static_cast<T>(x post_op)), x; }\
\
    typedef T argument_type;\
    typedef Tres result_type;\
  };\
\
  template<>\
  struct name<void>\
  {\
    constexpr name() noexcept {}\
\
    template<class T>\
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      operator()(T&& x) const\
    , ((x = static_cast<typename std::remove_reference<T>::type>(\
      std::forward<T>(x) post_op)), x))\
\
    typedef aux_::is_transparent_t is_transparent;\
  };

  FALCON_MAKE_UNARY_OP3(increment3, + 1, T&, T&)
  FALCON_MAKE_UNARY_OP3(decrement3, - 1, T&, T&)

#undef FALCON_MAKE_UNARY_OP3

template<class T>
struct equivalent
{
  constexpr equivalent() noexcept {}

  constexpr bool operator()(const T& a, const T& b) const
  { return !(a < b) && !(b < a); }

  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};

template<>
struct equivalent<void>
{
  constexpr equivalent() noexcept {}

  template<class T, class U>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(const T& a, const U& b) const
  , !(a < b) && !(b < a))

  typedef aux_::is_transparent_t is_transparent;
};


template<class T>
struct equivalent2
{
  constexpr equivalent2() noexcept {}

  constexpr bool operator()(const T& a, const T& b) const
  { return !(a < b) && !(a > b); }

  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};

template<>
struct equivalent2<void>
{
  constexpr equivalent2() noexcept {}

  template<class T, class U>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(const T& a, const U& b) const
  , !(a < b) && !(a > b))

  typedef aux_::is_transparent_t is_transparent;
};


template<class T>
struct arrow
{
  typedef T argument_type;
  typedef typename std::remove_const<T>::type::type& result_type;

  constexpr arrow() noexcept {}

  constexpr result_type operator()(T& a) const
  { return a.operator->(); }
};

template<>
struct arrow<void>
{
  constexpr arrow() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T&& a) const
  , std::forward<T>(a).operator->())

  typedef aux_::is_transparent_t is_transparent;
};


template<typename T, typename Index>
struct index
{
  typedef T first_argument_type;
  typedef typename default_or_type<std::size_t, Index, void>
    ::type second_argument_type;
  typedef typename std::remove_const<T>::type::value_type& result_type;

  constexpr index() noexcept {}

  constexpr result_type operator()(T& a, second_argument_type i) const
  { return a[i]; }
};

template<class T, class Index>
struct index<T*, Index>
{
  typedef T* first_argument_type;
  typedef typename default_or_type<std::size_t, Index, void>
    ::type second_argument_type;
  typedef T& result_type;

  constexpr index() noexcept {}

  constexpr result_type operator()(T& a, second_argument_type i) const
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
  constexpr index() noexcept {}

  template<typename T, typename Index>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T&& a, Index && i) const
  , std::forward<T>(a)[std::forward<Index>(i)])

  typedef aux_::is_transparent_t is_transparent;
};


template<typename T, typename Index>
struct index2
{
  typedef T first_argument_type;
  typedef typename default_or_type<std::size_t, Index, void>
    ::type second_argument_type;
  typedef typename std::remove_const<T>::type::type& result_type;

  constexpr index2() noexcept {}

  constexpr result_type operator()(T& a, second_argument_type i) const
  { return *(a + i); }
};

template<typename T, typename Index>
struct index2<T*, Index>
: index<T*, Index>
{};

template<typename T, typename Index>
struct index2<T[], Index>
: index<T*, Index>
{};

template<typename T, std::size_t N, typename Index>
struct index2<T[N], Index>
: index<T*, Index>
{ typedef T first_argument_type[N]; };

template<>
struct index2<void, void>
{
  constexpr index2() noexcept {}

  template<typename T, typename Index>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T&& a, Index&& i) const
  , *(std::forward<T>(a) + std::forward<Index>(i)))

  typedef aux_::is_transparent_t is_transparent;
};


template<class T, class U>
struct comma
{
  typedef T first_argument_type;
  typedef U second_argument_type;
  typedef T& result_type;

  constexpr comma() noexcept {}

  constexpr result_type operator()(T& a, U& b) const
  { return (a , b); }
};

template<>
struct comma<void, void>
{
  constexpr comma() noexcept {}

  template<class T, class U>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T&& a, U&& b) const
  , (std::forward<T>(a), std::forward<U>(b)))

  typedef aux_::is_transparent_t is_transparent;
};


template<typename T, typename Member>
struct pointer_to_member
{
  typedef T first_argument_type;
  typedef Member second_argument_type;
  typedef decltype(std::declval<T>().*std::declval<Member>()) result_type;

  constexpr pointer_to_member() noexcept {}

  constexpr result_type operator()(T& a, Member m) const
  { return a.*m; };
};

template<>
struct pointer_to_member<void, void>
{
  constexpr pointer_to_member() noexcept {}

  template<typename T, typename Member>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T&& a, Member m) const
  , std::forward<T>(a).*m)

  typedef aux_::is_transparent_t is_transparent;
};

}

#endif
