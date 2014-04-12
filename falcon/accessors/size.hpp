#ifndef FALCON_ACCESSOR_SIZE_HPP
#define FALCON_ACCESSOR_SIZE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/helper/use_size_type.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#include <cstddef>

namespace falcon {
namespace accessors {

template <typename T CPP_IF_CPP1X(= void), typename Result = use_default>
struct size
{
	typedef typename default_or_type<use_sizeype<T>, Result>::type result_type;
	typedef T argument_type;

	CPP_CONSTEXPR result_type operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.size())
  { return x.size(); }
};

#if __cplusplus >= 201103L
template <>
struct size<void>
{
  template<class T>
  CPP_CONSTEXPR auto operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.size())
  -> decltype(x.size())
  { return x.size(); }
};

CPP_GLOBAL_CONSTEXPR size<> size_f;
#endif

}
}

#endif
