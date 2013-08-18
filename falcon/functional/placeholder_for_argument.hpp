#ifndef _FALCON_FUNCTIONAL_PLACEHOLDER_FOR_ARGUMENT_HPP
#define _FALCON_FUNCTIONAL_PLACEHOLDER_FOR_ARGUMENT_HPP

#include <utility>
#include <falcon/functional/call.hpp>
#include <falcon/type_traits/declval.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

namespace falcon {

template <int Position, typename Functor, typename T>
struct placeholder_for_argument
{
  typedef Functor functor_type;
  typedef T first_type;

  static const int position = Position;

private:
  T _M_data;
  Functor _M_functor;

public:
  constexpr placeholder_for_argument() = default;

  constexpr placeholder_for_argument(const T& __data)
  : _M_data(__data)
  , _M_functor()
  {}

  constexpr placeholder_for_argument(const T& __data, Functor func)
  : _M_data(__data)
  , _M_functor(func)
  {}

  template<typename... _Args>
  constexpr placeholder_for_argument(const T& __data, _Args&&... args)
  : _M_data(__data)
  , FALCON_PP_NOT_IDE_PARSER(_M_functor{std::forward<_Args>(args)...})
  {}

  template<typename... _Args,
    std::size_t _CutPosition = (sizeof...(_Args) < Position ? sizeof...(_Args) : Position) + 1,
    typename _Indexes = typename parameter_index_cat<
      typename build_range_parameter_index<1, _CutPosition>::type,
      parameter_index<0>,
      typename build_range_parameter_index<_CutPosition, sizeof...(_Args)+1>::type
    >::type
  >
  constexpr typename parameter::result_of<
    const Functor&,
    typename parameter::elements<
      parameter_pack<const T&, _Args&&...>,
      _Indexes
    >::type
  >::type operator()(_Args&&... args) const
  {
    return call<const Functor&>(_Indexes(), _M_functor, _M_data,
                                std::forward<_Args>(args)...);
  }

  template<typename... _Args,
    std::size_t _CutPosition = (sizeof...(_Args) < Position ? sizeof...(_Args) : Position) + 1,
    typename _Indexes = typename parameter_index_cat<
      typename build_range_parameter_index<1, _CutPosition>::type,
      parameter_index<0>,
      typename build_range_parameter_index<_CutPosition, sizeof...(_Args)+1>::type
    >::type
  >
  typename parameter::result_of<
    Functor&,
    typename parameter::elements<
      parameter_pack<T&, _Args&&...>,
      _Indexes
    >::type
  >::type operator()(_Args&&... args)
  {
    return call<Functor&>(_Indexes(), _M_functor, _M_data,
                          std::forward<_Args>(args)...);
  }

  functor_type& functor()
  { return _M_functor; }
  constexpr const functor_type& functor() const
  { return _M_functor; }

  first_type& data()
  { return _M_data; }
  constexpr const first_type& data() const
  { return _M_data; }

  void swap(placeholder_for_argument& other)
  {
    using std::swap;
    swap(other._M_data, _M_data);
    swap(other._M_functor, _M_functor);
  }
};

template<std::size_t Position, typename Functor, typename T>
placeholder_for_argument<Position, Functor, T> bound_argument(Functor&& func, T&& arg)
{
  return placeholder_for_argument<Position, Functor, T>(
    std::forward<T>(arg), std::forward<Functor>(func)
  );
}

template <int Position, typename Functor, typename T>
void swap(placeholder_for_argument<Position, Functor, T>& x,
        placeholder_for_argument<Position, Functor, T>& y)
{ x.swap(y); }

}

#endif
