#ifndef FALCON_MPL_EVAL_IF_HPP
#define FALCON_MPL_EVAL_IF_HPP

#include <falcon/type_traits/eval_if.hpp>

namespace falcon {
namespace mpl {

template<typename C, typename TrueT, typename FalseT>
struct eval_if
{ using type = ::falcon::eval_if_c_t<typename C::type, TrueT, FalseT>; };

// template<bool c, typename TrueT, typename FalseT>
// struct eval_if_c
// { using type = ::falcon::eval_if<c, TrueT, FalseT>; };

template<typename C, typename TrueT, typename FalseT>
struct eval_not_if
{ using type = ::falcon::eval_not_if_c_t<typename C::type, TrueT, FalseT>; };

// template<bool c, typename TrueT, typename FalseT>
// struct eval_not_if_c
// { using type = ::falcon::eval_not_if<c, TrueT, FalseT>; };

}
}

#endif
