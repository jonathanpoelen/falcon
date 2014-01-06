#ifndef FALCON_ACCESSOR_REFERENCE_ACCESSOR_HPP
#define FALCON_ACCESSOR_REFERENCE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/type_traits/add_const_if_reference.hpp>

namespace falcon {

template <class T>
struct reference_accessor
{
	typedef T value_type;
	typedef T & reference;
	typedef reference argument_type;
	typedef reference result_type;
	typedef typename add_const_if_reference<T>::type const_reference;

	CPP_CONSTEXPR result_type operator()(reference v) const CPP_NOEXCEPT
	{ return v; }

  CPP_CONSTEXPR const_reference operator()(const_reference v) const CPP_NOEXCEPT
	{ return v; }
};

template <class T>
struct reference_accessor<const T>
{
	typedef T value_type;
	typedef const T & reference;
	typedef reference argument_type;
	typedef reference result_type;
	typedef reference const_reference;

	CPP_CONSTEXPR result_type operator()(const_reference v) const CPP_NOEXCEPT
	{ return v; }
};

}

#endif
