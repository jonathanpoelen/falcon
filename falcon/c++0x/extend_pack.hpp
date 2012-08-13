#ifndef _FALCON_CPP0X_EXTEND_PACK_HPP
#define _FALCON_CPP0X_EXTEND_PACK_HPP

#include <falcon/c++0x/warning.hpp>
#include <falcon/c++/extend_pack.hpp>

#define CPP0X_EXTEND_PACK CPP_EXTEND_PACK
#define CPP0X_PACK(...) __VA_ARGS__ CPP0X_EXTEND_PACK

#endif
