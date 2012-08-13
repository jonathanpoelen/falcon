#ifndef _FALCON_PARAMETER_RESULT_PACK_OF_HPP
#define _FALCON_PARAMETER_RESULT_PACK_OF_HPP

#include <type_traits>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {
namespace parameter {

template<typename _Signature, typename _Packs>
class result_pack_of;

template<typename _Functor, typename... _Parameters>
struct result_pack_of<_Functor, parameter_pack<_Parameters...>>
{
	typedef typename std::result_of<_Functor(_Parameters...)>::type type;
};

}
}

#endif