#ifndef FALCON_MPL_DEREF_HPP
#define FALCON_MPL_DEREF_HPP

namespace falcon {
namespace mpl {

template<typename Iterator>
struct deref
{ using type = typename Iterator::type; };

template<typename Iterator>
using deref_t = typename deref<Iterator>::type;

}
}

#endif
