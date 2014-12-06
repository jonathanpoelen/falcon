#ifndef FALCON_FN_RANGE_HPP
#define FALCON_FN_RANGE_HPP

#include <falcon/fn/make_global_function_object.hpp>
#include <iterator>

namespace falcon {
namespace fn {
  namespace adl_
  {
    template<class T, std::size_t N>
    constexpr T* begin(T (&a)[N]) noexcept
    { return a; }

    template<class T, std::size_t N>
    constexpr T* end(T (&a)[N]) noexcept
    { return a + N; }

    template<class T, std::size_t N>
    constexpr std::reverse_iterator<T*>
    rbegin(T (&a)[N]) noexcept
    { return std::reverse_iterator<T*>(a + N); }

    template<class T, std::size_t N>
    constexpr std::reverse_iterator<T*>
    rend(T (&a)[N]) noexcept
    { return std::reverse_iterator<T*>(a); }

    template<class Cont>
    constexpr auto has_rbegin_member_function(int)
    -> decltype(bool((void(std::declval<Cont>().rbegin()), true)))
    { return true; }

    template<class Cont>
    constexpr bool has_rbegin_member_function(unsigned)
    { return false; }

    template<class Cont>
    constexpr auto rbegin(Cont & cont)
    -> typename std::enable_if<
      !has_rbegin_member_function<Cont>(1)
    , std::reverse_iterator<decltype(cont.end())>
    >::type
    { return std::reverse_iterator<decltype(cont.end())>(cont.end()); }

    template<class Cont>
    constexpr auto rend(Cont & cont)
    -> typename std::enable_if<
      !has_rbegin_member_function<Cont>(1)
    , std::reverse_iterator<decltype(cont.begin())>
    >::type
    { return std::reverse_iterator<decltype(cont.begin())>(cont.begin()); }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, begin)
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, end)
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, rbegin)
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, rend)

  /// \brief call if possible, non member function begin(T), otherwise std::begin(T)
  using begin_fn = adl_::begin_fn;
  /// \brief call if possible, non member function end(T), otherwise std::end(T)
  using end_fn = adl_::end_fn;
  /// \brief call if possible, non member function rbegin(T), otherwise std::rbegin(T)
  using rbegin_fn = adl_::rbegin_fn;
  /// \brief call if possible, non member function rend(T), otherwise std::rend(T)
  using rend_fn = adl_::rend_fn;

  namespace adl_
  {
    struct cbegin_fn
    {
      constexpr cbegin_fn() noexcept {}

      template<class T>
      constexpr auto operator()(T const & x) const
      -> decltype(begin(x))
      { return begin(x); }
    };

    struct cend_fn
    {
      constexpr cend_fn() noexcept {}

      template<class T>
      constexpr auto operator()(T const & x) const
      -> decltype(begin(x))
      { return begin(x); }
    };

    struct crbegin_fn
    {
      constexpr crbegin_fn() noexcept {}

      template<class T>
      constexpr auto operator()(T const & x) const
      -> decltype(rbegin(x))
      { return rbegin(x); }
    };

    struct crend_fn
    {
      constexpr crend_fn() noexcept {}

      template<class T>
      constexpr auto operator()(T const & x) const
      -> decltype(rbegin(x))
      { return rbegin(x); }
    };
  }

  /// \brief call if possible, non member function cbegin(T), otherwise std::cbegin(T)
  using cbegin_fn = adl_::cbegin_fn;
  /// \brief call if possible, non member function cend(T), otherwise std::cend(T)
  using cend_fn = adl_::cend_fn;
  /// \brief call if possible, non member function crbegin(T), otherwise std::crbegin(T)
  using crbegin_fn = adl_::crbegin_fn;
  /// \brief call if possible, non member function crend(T), otherwise std::crend(T)
  using crend_fn = adl_::crend_fn;

  namespace {
    constexpr auto const & cbegin = static_const<cbegin_fn>::value;
    constexpr auto const & cend = static_const<cend_fn>::value;
    constexpr auto const & crbegin = static_const<crbegin_fn>::value;
    constexpr auto const & crend = static_const<crend_fn>::value;
  }
}
}

#endif
