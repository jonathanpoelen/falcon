#ifndef FALCON_ACCESSOR_EMPTY_HPP
#define FALCON_ACCESSOR_EMPTY_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace accessors {

template <class T = void>
struct empty
{
	typedef bool result_type;
	typedef T argument_type;

  CPP_CONSTEXPR empty() {}

  CPP_CONSTEXPR result_type operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.empty())
  { return x.empty(); }
};

template<>
struct empty<void>
{
  CPP_CONSTEXPR empty() {}

  template<class T>
  constexpr bool operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.empty())
  { return x.empty(); }
};

CPP_GLOBAL_CONSTEXPR empty<> empty_f;

}
}

#endif
