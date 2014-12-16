#ifndef FALCON_FUNCTIONAL_COMPOSE_HPP
#define FALCON_FUNCTIONAL_COMPOSE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <tuple>
#include <type_traits>

namespace falcon {

/** The @c compose is constructed from tuple functors, @c f, @c gnN.
 * Its @c operator() returns @c f(g1(args...), g2(args...), ...).
 * The function  @c make_compose takes f, t and constructs the @c compose
 * instance for you.  For example, if @c f returns an int, then
 * \code
 * int answer = make_compose(f,g1,g2,g3)(x,y);
 * \endcode
 * is equivalent to
 * \code
 * int answer = f(g1(x,y),g2(x,y),g3(x,y));
 * \endcode
 *
 * @defgroup functors Function Objects
 * @ingroup utilities
 *
 * @{
 */
template <class Fn, class... Fns>
class compose
: std::tuple<Fn, Fns...>
{
  using tuple_t_ = std::tuple<Fn, Fns...>;

  tuple_t_ const & tuple_() const noexcept
  { return static_cast<tuple_t_ const &> (*this); }

  template <class... Rs>
  struct impl_last
  {
    template<class... Args>
    static constexpr CPP1X_DELEGATE_FUNCTION(
      impl(tuple_t_ const & t, Rs && ... args, Args && ... fn_args)
    , std::get<0>(t)(
        std::forward<Rs>(args) FALCON_IF_NOT_IN_IDE_PARSER(...)
      , std::get<sizeof...(Fns)>(t)(std::forward<Args>(fn_args)...)
      )
    )
  };

  template<std::size_t... Indexes, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    impl_(parameter_index<Indexes...>, Args && ... args) const
  , impl_last<decltype(std::get<Indexes+1>(this->tuple_())(args...))...>::impl(
      this->tuple_()
    , std::get<Indexes+1>(this->tuple_())(args...)
      FALCON_IF_NOT_IN_IDE_PARSER(...)
    , std::forward<Args>(args)...
    )
  )

public:
  constexpr compose() = default;
  constexpr compose(const compose&) = default;
  constexpr compose(compose&&) = default;

  template<
    class TFn
  , class = typename std::enable_if<std::is_convertible<TFn, Fn>::value>::type>
  constexpr compose(TFn && func)
  : tuple_t_(std::forward<TFn>(func), Fns()...)
  {}

  template<
    class TFn, class... TFns
  , class = typename std::enable_if<std::is_convertible<TFn, Fn>::value>::type>
  constexpr compose(TFn && func, TFns && ... funcs)
  : tuple_t_(std::forward<TFn>(func), std::forward<TFns>(funcs)...)
  {}

  template<typename... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
    , this->impl_(
        build_parameter_index_t<sizeof...(Fns)-1>()
      , std::forward<Args>(args)...
    )
  )
};


template <class Fn, class... Fns>
constexpr compose<
  typename std::decay<Fn>::type
, typename std::decay<Fns>::type...
>
make_compose(Fn && fn, Fns && ... fns)
{ return { std::forward<Fn>(fn), std::forward<Fns>(fns)... }; }
//@}

}

#endif
