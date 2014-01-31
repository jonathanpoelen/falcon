#ifndef FALCON_ACCESSOR_EMPTY_ACCESSOR_HPP
#define FALCON_ACCESSOR_EMPTY_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>
#include <cstddef>

namespace falcon {

template <typename T>
struct empty_accessor
{
	typedef bool result_type;
	typedef T argument_type;

	CPP_CONSTEXPR result_type operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.empty())
  { return x.empty(); }
};

}

#endif
