#ifndef FALCON_PARAMETER_PACK_POINTER_HPP
#define FALCON_PARAMETER_PACK_POINTER_HPP

#include <falcon/parameter/pack_element.hpp>

namespace falcon {

template<typename _Pack>
class pack_pointer;

/**
 * @brief Add pointer each type of _Pack
 * _Pack must is a @ref parameter_pack
 */
template<typename... _Elements>
struct pack_pointer<parameter_pack<_Elements...>>
{ typedef parameter_pack<_Elements*...> type; };


template<typename _Pack>
class pack_const_pointer;

/**
 * @brief Add const pointer each type of _Pack
 * _Pack must is a @ref parameter_pack
 */
template<typename... _Elements>
struct pack_const_pointer<parameter_pack<_Elements...>>
{ typedef parameter_pack<const _Elements*...> type; };

}

#endif