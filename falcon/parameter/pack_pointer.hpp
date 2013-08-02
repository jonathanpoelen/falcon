#ifndef FALCON_PARAMETER_PACK_POINTER_HPP
#define FALCON_PARAMETER_PACK_POINTER_HPP

#include <falcon/parameter/pack_element.hpp>

namespace falcon {

template<typename Pack>
class pack_pointer;

/**
 * @brief Add pointer each type of Pack
 * Pack must is a @ref parameter_pack
 */
template<typename... Element>
struct pack_pointer<parameter_pack<Element...>>
{ typedef parameter_pack<Element*...> type; };


template<typename Pack>
class pack_const_pointer;

/**
 * @brief Add const pointer each type of Pack
 * Pack must is a @ref parameter_pack
 */
template<typename... Element>
struct pack_const_pointer<parameter_pack<Element...>>
{ typedef parameter_pack<const Element*...> type; };

}

#endif
