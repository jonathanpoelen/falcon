#ifndef _FALCON_PARAMETER_SIZE_HPP
#define _FALCON_PARAMETER_SIZE_HPP

#include <cstddef>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {
namespace parameter {

template<typename _Pack>
class pack_size;

template<typename... _Elements>
struct pack_size<parameter_pack<_Elements CPP0X_EXTEND_PACK> >
{
	static const std::size_t value = sizeof...(_Elements);
};

}
}

#endif