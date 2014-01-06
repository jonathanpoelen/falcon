#ifndef FALCON_ACCESSOR_PAIR_ACCESOR_HPP
#define FALCON_ACCESSOR_PAIR_ACCESOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {

namespace __detail {

template<class T>
struct inner_first_type
{ typedef T::first_type type; };

template<class T>
struct inner_first_type<volatile T>
{ typedef T::first_type type; };

template<class T>
struct inner_first_type<const T>
{ typedef typename T::first_type const type; };

template<class T>
struct inner_first_type<const volatile T>
{ typedef typename T::first_type const type; };

template<class T>
struct inner_second_type
{ typedef T::second_type type; };

template<class T>
struct inner_second_type<volatile T>
{ typedef T::second_type type; };

template<class T>
struct inner_second_type<const T>
{ typedef typename T::second_type const type; };

template<class T>
struct inner_second_type<const volatile T>
{ typedef typename T::second_type const type; };

}

template <class T>
struct first_accessor
{
  typedef T pair_type;
  typedef pair_type argument_type;
  typedef typename __detail::inner_first_type<T>::type result_type;

  CPP_CONSTEXPR result_type& operator()(pair_type& pair) const CPP_NOEXCEPT
  { return pair.first; }
};

template <class T>
struct second_accessor
{
	typedef T pair_type;
	typedef pair_type argument_type;
  typedef typename __detail::inner_second_type<T>::type result_type;

  CPP_CONSTEXPR result_type& operator()(pair_type& pair) const CPP_NOEXCEPT
  { return pair.second; }
};

}

#endif
