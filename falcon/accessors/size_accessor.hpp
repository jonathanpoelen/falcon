#ifndef FALCON_ACCESSOR_SIZE_ACCESSOR_HPP
#define FALCON_ACCESSOR_SIZE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>
#include <cstddef>

namespace falcon {

template <typename T, typename Result = std::size_t>
struct size_accessor
{
	typedef Result result_type;
	typedef T argument_type;

	CPP_CONSTEXPR result_type operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.size())
  { return x.size(); }
};

}

#endif
