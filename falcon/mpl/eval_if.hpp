#ifndef FALCON_MPL_EVAL_IF_HPP
#define FALCON_MPL_EVAL_IF_HPP

#include <falcon/type_traits/eval_if.hpp>

namespace falcon {
namespace mpl {

template<typename C, typename TrueT, typename FalseT>
using eval_if = ::falcon::eval_if_c<C, TrueT, FalseT>;

template<bool c, typename TrueT, typename FalseT>
using eval_if_c = ::falcon::eval_if<c, TrueT, FalseT>;

template<typename C, typename TrueT, typename FalseT>
using eval_not_if = ::falcon::eval_not_if_c<C, TrueT, FalseT>;

template<bool c, typename TrueT, typename FalseT>
using eval_not_if_c = ::falcon::eval_not_if<c, TrueT, FalseT>;

}
}

#endif
