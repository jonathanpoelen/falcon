#ifndef FALCON_TYPE_TRAITS_BUILD_CLASS_HPP
#define FALCON_TYPE_TRAITS_BUILD_CLASS_HPP

#include <falcon/parameter/parameter_pack.hpp>

namespace falcon
{

template <template<typename...> class _W, typename _T>
class build_class;

template <template<typename...> class _W, typename... _Elements>
struct build_class<_W, parameter_pack<_Elements...>>
{ typedef _W<_Elements...> type; };

}

#endif