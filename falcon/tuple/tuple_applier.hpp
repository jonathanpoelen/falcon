#ifndef FALCON_TUPLE_TUPLE_APPLIER_HPP
#define FALCON_TUPLE_TUPLE_APPLIER_HPP

#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>
#include <utility>

namespace falcon {

/**
 * \brief Functor for used \p tuple_apply()
 *
 * Tag is \link indexes-tag indexes-tag \endlink or \p parameter_index
 */
template <typename Functor, typename Tag = full_parameter_index_tag>
class tuple_applier
{
  typedef typename parameter_index_or_tag_to_tag<Tag>::type __tag;

public:
  tuple_applier(Functor func)
  : _M_func(func)
  {}

  template<typename T, typename BuildIndexes = typename keep_parameter_index<__tag, std::tuple_size<T>::value>::type>
  auto operator()(T&& t) const
  -> decltype(tuple_apply(BuildIndexes(), std::declval<const Functor&>(), std::forward<T>(t)))
  { return tuple_apply(BuildIndexes(), _M_func, std::forward<T>(t)); }

  void swap(tuple_applier& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }

  template<typename Tag2>
  void swap(tuple_applier<Functor, Tag2>& other)
  {
    using std::swap;
    swap(_M_func, other._M_func);
  }

private:
  Functor _M_func;
};

template <typename Functor>
tuple_applier<Functor> make_tuple_applier(Functor&& func)
{ return {std::forward<Functor>(func)}; }

template <typename Functor, typename Tag>
void swap(tuple_applier<Functor, Tag>& a,
          tuple_applier<Functor, Tag>& b)
{ a.swap(b); }

template <typename Functor, typename Tag, typename Tag2>
void swap(tuple_applier<Functor, Tag>& a,
          tuple_applier<Functor, Tag2>& b)
{ a.swap(b); }

}

#endif
