#ifndef FALCON_MPL_QUOTE_HPP
#define FALCON_MPL_QUOTE_HPP

namespace falcon {
namespace mpl {

template <template<class...>class T>
struct quote
{
  template <typename... Args>
  struct apply
  {
    using type = typename T<Args...>::type;
  };
};

}
}

#endif
