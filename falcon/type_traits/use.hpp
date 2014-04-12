#ifndef FALCON_TYPE_TRAITS_USE_HPP
#define FALCON_TYPE_TRAITS_USE_HPP

namespace falcon{

template <typename T>
struct use
{ typedef T type; };

template <typename T, typename Unless>
struct late_use
{ typedef T type; };

}

#endif
