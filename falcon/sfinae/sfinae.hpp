#ifndef FALCON_SFINAE_SFINAE_HPP
#define FALCON_SFINAE_SFINAE_HPP

#include <falcon/type_traits/yes_no_type.hpp>

namespace falcon {
namespace sfinae {

template <typename U, U>
struct helper;

/*struct sfinae
{
	typedef yes_type yes;
	typedef no_type no;

	template <typename U, U>
	struct helper;
};*/

}
}

#endif
