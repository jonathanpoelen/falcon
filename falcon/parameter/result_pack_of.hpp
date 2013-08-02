#ifndef FALCON_PARAMETER_RESULT_PACK_OF_HPP
#define FALCON_PARAMETER_RESULT_PACK_OF_HPP

#include <type_traits>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {

template<typename Signature, typename Pack>
class result_pack_of;

template<typename Functor, typename... Parameters>
struct result_pack_of<Functor, parameter_pack<Parameters...>>
{
	typedef typename std::result_of<Functor(Parameters...)>::type type;
};


namespace parameter {
  template<typename Signature, typename Pack>
  using result_of = result_pack_of<Signature, Pack>;
}

}

#endif
