#ifndef FALCON_TUPLE_TUPLE_APPLIER_HPP
#define FALCON_TUPLE_TUPLE_APPLIER_HPP

#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/tuple/tuple_apply.hpp>

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
  tuple_applier(Functor && func)
  : m_func(std::forward<Functor>(func))
  {}

  template<typename T>
  auto operator()(T&& t) const
  -> decltype(
    tuple_apply(keep_parameter_index_t<__tag, std::tuple_size<T>::value>()
  , std::declval<Functor&>(), std::forward<T>(t)))
  { return tuple_apply(keep_parameter_index_t<__tag, std::tuple_size<T>::value>()
  , m_func, std::forward<T>(t)); }

  void swap(tuple_applier& other)
  {
    using std::swap;
    swap(m_func, other.m_func);
  }

  template<typename Tag2>
  void swap(tuple_applier<Functor, Tag2>& other)
  {
    using std::swap;
    swap(m_func, other.m_func);
  }

private:
  Functor m_func;
};

template <typename Functor>
tuple_applier<Functor> make_tuple_applier(Functor&& func)
{ return {std::forward<Functor>(func)}; }

template <typename Functor, typename Tag>
tuple_applier<Functor, Tag> make_tuple_applier(Functor&& func, Tag)
{ return {std::forward<Functor>(func)}; }

template <typename Functor, typename Tag, typename Tag2>
void swap(tuple_applier<Functor, Tag>& a, tuple_applier<Functor, Tag2>& b)
{ a.swap(b); }

}

#endif
