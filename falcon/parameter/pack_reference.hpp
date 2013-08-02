#ifndef FALCON_PARAMETER_PACK_REFERENCE_HPP
#define FALCON_PARAMETER_PACK_REFERENCE_HPP

#include <falcon/parameter/pack_element.hpp>

namespace falcon {

template<typename Pack>
class pack_reference;

/**
 * @brief Add reference each type of Pack
 * Pack must is a @ref parameter_pack
 */
template<typename... Element>
struct pack_reference<parameter_pack<Element...>>
{ typedef parameter_pack<Element&...> type; };


template<typename Pack>
class pack_const_reference;

/**
 * @brief Add const reference each type of Pack
 * Pack must is a @ref parameter_pack
 */
template<typename... Element>
struct pack_const_reference<parameter_pack<Element...>>
{ typedef parameter_pack<const Element&...> type; };

}

#endif
