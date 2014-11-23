#ifndef FALCON_TYPE_TRAITS_STATIC_CONST_HPP
#define FALCON_TYPE_TRAITS_STATIC_CONST_HPP

namespace falcon {

template<class T>
struct static_const
{
  static constexpr T value{};
  constexpr const T & operator()() const noexcept
  { return value; }
};

template<class T>
constexpr T static_const<T>::value;

#define FALCON_GLOBAL_OBJECT(name, type) \
  namespace { \
    constexpr auto const & name = ::falcon::static_const<type>::value; \
  }

}

#endif
