#ifndef FALCON_PARAMETER_PACK_ELEMENT_HPP
#define FALCON_PARAMETER_PACK_ELEMENT_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/parameter/parameter_element.hpp>

namespace falcon {

template <typename Pack, typename Indexes>
class __pack_element;

template <typename Pack, size_t... Indexes>
struct __pack_element<Pack, parameter_index<Indexes...>>
{ typedef parameter_pack<typename parameter_element<Indexes, Pack>::type...> type; };

template <typename Pack, typename Indexes>
struct pack_element
{ typedef typename __pack_element<Pack, Indexes>::type type; };

namespace parameter {
  template <typename Pack, typename Indexes>
  using elements = __pack_element<Pack, Indexes>;
}

}

#endif
