#ifndef FALCON_FUNCTIONAL_INVOKER_HPP
#define FALCON_FUNCTIONAL_INVOKER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/invoke.hpp>
#include <falcon/tuple/parameter_index.hpp>

#include <tuple>
#include <utility>
#include <type_traits>

namespace falcon {

template <class Func, class... Args>
class invoker : std::tuple<Func, Args...>
{
  using tuple_t_ = std::tuple<Func, Args...>;

public:
  invoker() = default;

  template<class TFunc>
  constexpr invoker(TFunc && func)
  : tuple_t_(std::forward<TFunc>(func))
  {}

  template<class TFunc, class... TArgs>
  constexpr invoker(TFunc && func, TArgs&&... args)
  : tuple_t_(std::forward<TFunc>(func), std::forward<TArgs>(args)...)
  {}

private:
  const tuple_t_ & tuple_() const
  { return static_cast<tuple_t_ const &>(*this); }

  tuple_t_ & tuple_()
  { return static_cast<tuple_t_ &>(*this); }

  template<std::size_t... Indexes, class... TArgs>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    invoke_(parameter_index<Indexes...>, TArgs&&... args) const
  , invoke(
      std::get<Indexes>(tuple_()) FALCON_IF_NOT_IN_IDE_PARSER(...)
    , std::forward<TArgs>(args)...)
  )

public:
  template<class... TArgs>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(TArgs&&... args) const
  , invoke_(
      build_parameter_index_t<(1+sizeof...(Args))>()
    , std::forward<TArgs>(args)...
  ))

  void swap(invoker & other)
  noexcept(noexcept(swap(this->tuple_(), other.tuple_())))
  {
    using std::swap;
    swap(this->tuple_(), other.tuple_());
  }
};

template<class Func, class... Args>
void swap(invoker<Func, Args...> & a, invoker<Func, Args...> & b)
noexcept(noexcept(a.swap(b)))
{ a.swap(b); }

template <class Func, class... Args>
constexpr invoker<
  typename std::decay<Func>::type
, typename std::decay<Args>::type...
> make_invoker(Func && func, Args&&... args)
{ return {std::forward<Func>(func), std::forward<Args>(args)...}; }

}

#endif
