#ifndef FALCON_FUNCTIONAL_SPECIAL_CALL_HPP
#define FALCON_FUNCTIONAL_SPECIAL_CALL_HPP

#include <falcon/functional/call.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

/**
 * \ingroup call-arguments
 * @{
 */
/**
 * \brief Specification of \p call()
 * @{
 */
template<std::size_t Keep = 1, typename Function, typename... Args,
  typename Indexes = typename keep_parameter_index<
    first_parameter_index_tag<Keep>, sizeof...(Args)
  >::type
>
constexpr auto call_first_param(Function && func, Args&&... args)
-> decltype(call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...))
{    return call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...); }


template<std::size_t Keep = 1, typename Function, typename... Args,
  typename Indexes = typename keep_parameter_index<
    last_parameter_index_tag<Keep>, sizeof...(Args)
  >::type
>
constexpr auto call_last_param(Function && func, Args&&... args)
-> decltype(call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...))
{    return call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...); }


template<std::size_t Start, std::size_t Len, typename Function, typename... Args,
  typename Indexes = typename keep_parameter_index<
    range_parameter_index_tag<Start, Len>, sizeof...(Args)
  >::type
>
constexpr auto call_range_param(Function && func, Args&&... args)
-> decltype(call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...))
{    return call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...); }


template<std::size_t Pos, std::size_t Ignore = 1, typename Function,
  typename... Args,
  typename Indexes = typename keep_parameter_index<
    ignore_parameter_index_tag<Pos, Ignore>, sizeof...(Args)
  >::type
>
constexpr auto call_ignore_param(Function && func, Args&&... args)
-> decltype(call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...))
{    return call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...); }


template<std::size_t Start = 0, std::size_t Len = -1u, typename Function,
  typename... Args,
  typename Indexes = typename keep_parameter_index<
    reverse_parameter_index_tag<Start, Len>, sizeof...(Args)
  >::type
>
constexpr auto call_reverse_param(Function && func, Args&&... args)
-> decltype(call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...))
{    return call(Indexes(), std::forward<Function>(func), std::forward<Args>(args)...); }
//@}
//@}

}

#endif
