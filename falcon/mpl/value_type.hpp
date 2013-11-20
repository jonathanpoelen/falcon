#ifndef FALCON_MPL_VALUE_TYPE_HPP
#define FALCON_MPL_VALUE_TYPE_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct value_type
: detail::mpl_apply_def
{ using type = typename aux::value_type<detail::sequence_t<Seq>, T>::type; };

template<typename Seq, typename T>
using value_type_t = typename value_type<Seq, T>::type;

}
}

#endif
