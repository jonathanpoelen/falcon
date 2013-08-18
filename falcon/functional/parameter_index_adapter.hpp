#ifndef FALCON_FUNCTIONAL_PARAMETER_INDEX_ADAPTER_HPP
#define FALCON_FUNCTIONAL_PARAMETER_INDEX_ADAPTER_HPP

#include <falcon/functional/call.hpp>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/call_partial_recursive_param_loop.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

///\brief Tag for used @p call_partial_param_loop() with @c parameter_index_adapter
template<std::size_t _NumberArg>
struct call_partial_param_loop_tag {};

///\brief Tag for used @p call_partial_recursive_param_loop() with @c parameter_index_adapter
template<std::size_t _NumberArg>
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
  Functor _M_func;

private:
  typedef typename parameter_index_or_tag_to_tag<Tag>::type __tag;

public:
  template<typename... _Args, typename _BuildIndexes = typename keep_parameter_index<__tag, sizeof...(_Args)>::type>
  constexpr typename __call_result_of<
    const Functor,
    _BuildIndexes,
    _Args...
  >::__type operator()(_Args&&... args) const
  {
    return call<const Functor&>(_BuildIndexes(), _M_func, std::forward<_Args>(args)...);
  }

  void swap(parameter_index_adapter& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }

  template<typename Tag2>
  void swap(parameter_index_adapter<Functor, Tag2>& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }
};

template <typename Functor, std::size_t _NumberArg>
struct parameter_index_adapter<Functor, call_partial_param_loop_tag<_NumberArg>>
{
  Functor _M_func;

  template<typename... _Args>
  constexpr typename __call_partial_param_loop_traits<_NumberArg, const Functor, _Args...>::__result_type operator()(_Args&&... args) const
  {
    return call_partial_param_loop<_NumberArg, const Functor&>(
      _M_func, std::forward<_Args>(args)...);
  }

  void swap(parameter_index_adapter& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }

  template<typename Tag2>
  void swap(parameter_index_adapter<Functor, Tag2>& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }
};

template <typename Functor, std::size_t _NumberArg>
struct parameter_index_adapter<Functor, call_partial_recursive_param_loop_tag<_NumberArg>>
{
  Functor _M_func;

  template<typename... _Args>
  constexpr typename __call_partial_recursive_param_loop_traits<_NumberArg, const Functor, _Args...>::__result_type operator()(_Args&&... args) const
  {
    return call_partial_recursive_param_loop<_NumberArg, const Functor&>(
      _M_func, std::forward<_Args>(args)...);
  }

  void swap(parameter_index_adapter& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }

  template<typename Tag2>
  void swap(parameter_index_adapter<Functor, Tag2>& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }
};

//@}

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
