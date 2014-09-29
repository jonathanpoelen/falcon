#ifndef FALCON_FUNCTIONAL_LOGICAL_HPP
#define FALCON_FUNCTIONAL_LOGICAL_HPP

#include <utility>
#include <tuple>

namespace falcon {

//@{
/**
 * any_equal_to(5,5,1,2) different to (5 == 5 || 5 == 1 || 5 == 2) because all values are instanciat.
 * With not
 * @code
 * int ref = 5, a = 5, b = 1, c = 2;
 * any_equal_to(ref, a, b, c);
 * @endcode
 * because values pass to reference
 */
class all_equal_to_t;
class all_not_equal_to_t;
class all_less_t;
class all_greater_t;
class all_less_equal_t;
class all_greater_equal_t;

class any_equal_to_t;
class any_not_equal_to_t;
class any_less_t;
class any_greater_t;
class any_less_equal_t;
class any_greater_equal_t;

template<class T> class all_equal_to_wrapper;
template<class T> class all_not_equal_to_wrapper;
template<class T> class all_less_wrapper;
template<class T> class all_greater_wrapper;
template<class T> class all_less_equal_wrapper;
template<class T> class all_greater_equal_wrapper;

template<class T> class any_equal_to_wrapper;
template<class T> class any_not_equal_to_wrapper;
template<class T> class any_less_wrapper;
template<class T> class any_greater_wrapper;
template<class T> class any_less_equal_wrapper;
template<class T> class any_greater_equal_wrapper;

class all_equal_if_t;
class any_equal_if_t;
class none_equal_if_t;

template <class T, class Compare> class all_equal_if_wrapper;
template <class T, class Compare> class any_equal_if_wrapper;
template <class T, class Compare> class all_equal_if_wrapper;
//@}


#define FALCON_MAKE_LOGICAL_FUNC(name, op, and_or)                         \
  constexpr struct name##_t {                                              \
    template<class T, class U>                                             \
    constexpr bool operator()(const T& a, const U& b) const                \
    noexcept(noexcept(a op b))                                             \
    { return a op b; }                                                     \
                                                                           \
    template<class T, class U, class... Args>                              \
    constexpr bool operator()(const T& a, const U& b, const Args&... args) \
    const noexcept(noexcept(a op b))                                       \
    { return (a op b) and_or operator()(a, args...); }                     \
  } name {};                                                               \
                                                                           \
  template<class T>                                                        \
  struct name##_wrapper                                                    \
  {                                                                        \
    name##_wrapper() = default;                                            \
    name##_wrapper(name##_wrapper const &) = default;                      \
    name##_wrapper(name##_wrapper &&) = default;                           \
    constexpr name##_wrapper(T&& x)                                        \
    : x(std::forward<T>(x))                                                \
    {}                                                                     \
    template<class... Args>                                                \
    constexpr bool operator()(const Args&... args) const                   \
    { return name(x, args...); }                                           \
  private:                                                                 \
    T x;                                                                   \
  };

FALCON_MAKE_LOGICAL_FUNC(all_equal_to, ==, &&)
FALCON_MAKE_LOGICAL_FUNC(all_not_equal_to, !=, &&)
FALCON_MAKE_LOGICAL_FUNC(all_less, <, &&)
FALCON_MAKE_LOGICAL_FUNC(all_greater, >, &&)
FALCON_MAKE_LOGICAL_FUNC(all_less_equal, <=, &&)
FALCON_MAKE_LOGICAL_FUNC(all_greater_equal, >=, &&)

FALCON_MAKE_LOGICAL_FUNC(any_equal_to, ==, ||)
FALCON_MAKE_LOGICAL_FUNC(any_not_equal_to, !=, ||)
FALCON_MAKE_LOGICAL_FUNC(any_less, <, ||)
FALCON_MAKE_LOGICAL_FUNC(any_greater, >, ||)
FALCON_MAKE_LOGICAL_FUNC(any_less_equal, <=, ||)
FALCON_MAKE_LOGICAL_FUNC(any_greater_equal, >=, ||)

#undef FALCON_MAKE_LOGICAL_FUNC


#define FALCON_MAKE_LOGICAL_FUNC(name, and_or, v)                        \
  constexpr struct name##_t {                                            \
    template<class Compare, class T, class U>                            \
    constexpr bool operator()(Compare cmp, const T& a, const U& b)       \
    const noexcept(noexcept(cmp(a, b)))                                  \
    { return cmp(a, b) == v; }                                           \
                                                                         \
    template<class Compare, class T, class U, class... Args>             \
    constexpr bool                                                       \
    operator()(Compare cmp, const T& a, const U& b, const Args&... args) \
    const noexcept(noexcept(cmp(a, b)))                                  \
    { return cmp(a, b) and_or operator()(cmp, a, args...); }             \
  } name {};                                                             \
                                                                         \
  template<class T, class Compare>                                       \
  struct name##_wrapper                                                  \
  {                                                                      \
    name##_wrapper() = default;                                          \
    name##_wrapper(name##_wrapper const &) = default;                    \
    name##_wrapper(name##_wrapper &&) = default;                         \
    constexpr name##_wrapper(T&& x)                                      \
    : t(std::forward<T>(x), Compare())                                   \
    {}                                                                   \
    constexpr name##_wrapper(T&& x, Compare cmp)                         \
    : t(std::forward<T>(x), cmp)                                         \
    {}                                                                   \
    constexpr name##_wrapper(Compare cmp)                                \
    : t(T(), cmp)                                                        \
    {}                                                                   \
    template<class... Args>                                              \
    constexpr bool operator()(const Args&... args) const                 \
    { return name(std::get<1>(t), std::get<0>(t), args...); }            \
  private:                                                               \
    std::tuple<T, Compare> t;                                            \
  };

FALCON_MAKE_LOGICAL_FUNC(all_equal_if, &&, true)
FALCON_MAKE_LOGICAL_FUNC(any_equal_if, ||, true)
FALCON_MAKE_LOGICAL_FUNC(none_equal_if, &&, false)

#undef FALCON_MAKE_LOGICAL_FUNC

}

#endif
