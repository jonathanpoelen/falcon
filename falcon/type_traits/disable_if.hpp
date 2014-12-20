#ifndef FALCON_TYPE_TRAITS_DISABLE_IF_HPP
#define FALCON_TYPE_TRAITS_DISABLE_IF_HPP

#include <falcon/type_traits/enable_if.hpp>

namespace falcon {

template<bool C, class T = void>
struct disable_if
: enable_if<!C, T>
{};

template<class C, class T = void>
struct disable_if_c
: enable_if<!C::value, T>
{};

template <bool C, class T>
using disable_if_t = typename disable_if<C, T>::type;

template <class C, class T>
using disable_if_c_t = typename disable_if_c<C, T>::type;

}

#endif
