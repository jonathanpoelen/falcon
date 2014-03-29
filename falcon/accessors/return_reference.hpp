#ifndef FALCON_ACCESSOR_RETURN_REFERENCE_HPP
#define FALCON_ACCESSOR_RETURN_REFERENCE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/type_traits/add_const_if_reference.hpp>

namespace falcon {
namespace accessors {

template <class T CPP_IF_CPP1X(=void)>
struct return_reference
{
	typedef T value_type;
	typedef T & reference;
	typedef reference argument_type;
	typedef reference result_type;
	typedef typename add_const_if_reference<T>::type const_reference;

	CPP_CONSTEXPR result_type operator()(reference x) const CPP_NOEXCEPT
	{ return x; }

  CPP_CONSTEXPR const_reference operator()(const_reference x) const CPP_NOEXCEPT
	{ return x; }
};

template <class T>
struct return_reference<const T>
{
	typedef T value_type;
	typedef const T & reference;
	typedef reference argument_type;
	typedef reference result_type;
	typedef reference const_reference;

	CPP_CONSTEXPR result_type operator()(const_reference x) const CPP_NOEXCEPT
	{ return x; }
};

#if __cplusplus >= 201103L
template<>
struct return_reference<void>
{
  template<class T>
  CPP_CONSTEXPR T& operator()(T & x) const CPP_NOEXCEPT
  { return x; }
};

CPP_GLOBAL_CONSTEXPR return_reference<> return_reference_f;
#endif

}
}

#endif
