#ifndef FALCON_TYPE_TRAITS_IGNORE_HPP
#define FALCON_TYPE_TRAITS_IGNORE_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/empty_class.hpp>

namespace falcon {

CPP_EMPTY_CLASS(ignore_t);

CPP_GLOBAL_CONSTEXPR ignore_t ignore;

}

#endif
