#ifndef FALCON_SFINAE_DETAIL_IS_CALLABLE_HPP
#define FALCON_SFINAE_DETAIL_IS_CALLABLE_HPP

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <falcon/type_traits/enable_if.hpp>
# include <boost/type_traits/is_convertible.hpp>
#endif

namespace falcon {
  namespace detail {
    template<typename T, typename U>
#if __cplusplus >= 201103L
    typename std::enable_if<std::is_convertible<U,T>::value, T>::type
    returnval(U&&);
#else
    typename falcon::enable_if<boost::is_convertible<U,T>::value, T>::type
    returnval(const U&);

    class sfinae_unspecified;
#endif
  }
}

#endif
