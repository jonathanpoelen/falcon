#ifndef FALCON_PARAMETER_PACK_REFERENCE_HPP
#define FALCON_PARAMETER_PACK_REFERENCE_HPP

#include <falcon/parameter/pack_element.hpp>

namespace falcon {

template<typename _Pack>
class pack_reference;

/**
 * @brief Add reference each type of _Pack
 * _Pack must is a @ref parameter_pack
 */
template<typename... _Elements>
struct pack_reference<parameter_pack<_Elements...>>
{ typedef parameter_pack<_Elements&...> type; };


template<typename _Pack>
class pack_const_reference;

/**
 * @brief Add const reference each type of _Pack
 * _Pack must is a @ref parameter_pack
 */
template<typename... _Elements>
struct pack_const_reference<parameter_pack<_Elements...>>
{ typedef parameter_pack<const _Elements&...> type; };

}

#endif