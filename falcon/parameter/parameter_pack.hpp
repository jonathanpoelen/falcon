#ifndef FALCON_PARAMETER_PACK_HPP
#define FALCON_PARAMETER_PACK_HPP

namespace falcon {

template<typename... Args>
struct parameter_pack
{ typedef parameter_pack type; };

namespace parameter {
  template<typename... Args>
  using pack = parameter_pack<Args...>;
}

}

#endif
