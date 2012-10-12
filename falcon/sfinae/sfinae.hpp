#ifndef FALCON_SFINAE_SFINAE_HPP
#define FALCON_SFINAE_SFINAE_HPP

#include <falcon/type_traits/yes_no_type.hpp>

namespace falcon {
namespace sfinae {

template <typename U, U>
struct helper;

}

struct sfinae_type
{
	typedef yes_type one;
	typedef no_type two;
};

}

#endif
