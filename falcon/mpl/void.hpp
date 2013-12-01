#ifndef FALCON_MPL_VOID_HPP
#define FALCON_MPL_VOID_HPP

#include <falcon/mpl/integral_c.hpp>

namespace falcon { namespace mpl {

struct void_ { typedef void_ type; };

template<typename T>
struct is_void_
: false_
{};

template<>
struct is_void_<void_>
: true_
{};

template<typename T>
struct is_not_void_
: true_
{};

template<>
struct is_not_void_<void_>
: false_
{};

template<typename T>
using is_void = is_void_<T>;

template<typename T>
using is_not_void = is_not_void_<T>;

}
}

#endif // BOOST_MPL_VOID_HPP_INCLUDED
