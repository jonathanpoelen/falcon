#ifndef FALCON_MPL_ITERATOR_TAGS_HPP
#define FALCON_MPL_ITERATOR_TAGS_HPP

#include <falcon/mpl/integral_c.hpp>

namespace falcon {
namespace mpl {

struct forward_iterator_tag       : int_<0> { using type = forward_iterator_tag; };
struct bidirectional_iterator_tag : int_<1> { using type = bidirectional_iterator_tag; };
struct random_access_iterator_tag : int_<2> { using type = random_access_iterator_tag; };

}
}

#endif
