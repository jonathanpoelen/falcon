#ifndef FALCON_FUNCTIONAL_PARAMETER_INDEX_ADAPTER_HPP
#define FALCON_FUNCTIONAL_PARAMETER_INDEX_ADAPTER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/call_partial_recursive_param_loop.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

///\brief Tag for used @p call_partial_param_loop() with @c parameter_index_adapter
template<std::size_t NumArg>
struct call_partial_param_loop_tag {};

///\brief Tag for used @p call_partial_recursive_param_loop() with @c parameter_index_adapter
template<std::size_t NumArg>
struct call_partial_recursive_param_loop_tag {};


/**
 * \brief Functor for used \link call-arguments \p call(), \p call_partial_param_loop() and \p call_partial_recursive_param_loop() \endlink
 *
 * Tag is \p call_partial_param_loop_tag for used \p call_partial_param_loop(), \p call_partial_recursive_param_loop_tag for used \p call_partial_recursive_param_loop(), each tag of \link indexes-tag indexes-tag \endlink or \p parameter_index
 * @{
 */
template <typename Functor, typename Tag = full_parameter_index_tag>
struct parameter_index_adapter
{
  Functor func_;

private:
  typedef typename parameter_index_or_tag_to_tag<Tag>::type tag_type;

public:
  template<typename... Args, typename BuildIndexes
  = typename keep_parameter_index<tag_type, sizeof...(Args)>::type>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
  , call(BuildIndexes(), func_, std::forward<Args>(args)...))

  void swap(parameter_index_adapter& other)
  {
    using std::swap;
    swap(func_, other.func_);
  }

  template<typename Tag2>
  void swap(parameter_index_adapter<Functor, Tag2>& other)
  {
    using std::swap;
    swap(func_, other.func_);
  }
};

template <typename Functor, std::size_t NumArg>
struct parameter_index_adapter<Functor, call_partial_param_loop_tag<NumArg>>
{
  Functor func_;

  template<typename... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
  , call_partial_param_loop<NumArg>(func_, std::forward<Args>(args)...))

  void swap(parameter_index_adapter& other)
  {
    using std::swap;
    swap(func_, other.func_);
  }

  template<typename Tag2>
  void swap(parameter_index_adapter<Functor, Tag2>& other)
  {
    using std::swap;
    swap(func_, other.func_);
  }
};

template <typename Functor, std::size_t NumArg>
struct parameter_index_adapter<Functor, call_partial_recursive_param_loop_tag<NumArg>>
{
  Functor func_;

  template<typename... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
  , call_partial_recursive_param_loop<NumArg, const Functor&>
    (func_, std::forward<Args>(args)...)
  )

  void swap(parameter_index_adapter& other)
  {
    using std::swap;
    swap(func_, other.func_);
  }

  template<typename Tag2>
  void swap(parameter_index_adapter<Functor, Tag2>& other)
  {
    using std::swap;
    swap(func_, other.func_);
  }
};

//@}

template <class Functor, class Tag>
parameter_index_adapter<Functor, Tag>
make_parameter_index_adapter(Functor && f, Tag)
{ return parameter_index_adapter<Functor, Tag>{std::forward<Functor>(f)};  }


template<class F, std::size_t... Ints>
using func_args = parameter_index_adapter<
F
, specified_parameter_index_tag<parameter_index<(Ints-1)...>>
>;

template<std::size_t... Ints, class F>
func_args<F, Ints...> func(F && f)
{ return func_args<F, Ints...>{std::forward<F>(f)}; }


template <typename Functor, typename Tag>
void swap(parameter_index_adapter<Functor, Tag>& x,
        parameter_index_adapter<Functor, Tag>& y)
{ x.swap(y); }

template <typename Functor, typename Tag, typename Tag2>
void swap(parameter_index_adapter<Functor, Tag>& x,
        parameter_index_adapter<Functor, Tag2>& y)
{ x.swap(y); }

}

#endif
