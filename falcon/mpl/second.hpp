#ifndef FALCON_MPL_SECOND_HPP
#define FALCON_MPL_SECOND_HPP

namespace falcon {
namespace mpl {

template<typename Pair>
struct second
{ using type = typename Pair::second; };

template<typename Seq>
using second_t = typename second<Seq>::type;

}
}

#endif
