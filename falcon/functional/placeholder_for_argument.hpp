#ifndef FALCON_FUNCTIONAL_PLACEHOLDER_FOR_ARGUMENT_HPP
#define FALCON_FUNCTIONAL_PLACEHOLDER_FOR_ARGUMENT_HPP

#include <falcon/functional/call.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>
#include <falcon/parameter/result_pack_of.hpp>
#include <falcon/parameter/pack_element.hpp>

#include <utility>

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

  template<typename... Args>
  constexpr placeholder_for_argument(const T& __data, Args&&... args)
  : _M_data(__data)
  , FALCON_PP_NOT_IDE_PARSER(_M_functor{std::forward<Args>(args)...})
  {}

  template<typename... Args,
    std::size_t CutPosition = (sizeof...(Args) < Position ? sizeof...(Args) : Position) + 1,
    typename _Indexes = typename parameter_index_cat<
      build_range_parameter_index_t<1, CutPosition>,
      parameter_index<0>,
      build_range_parameter_index_t<CutPosition, sizeof...(Args)+1>
    >::type
  >
  constexpr auto operator()(Args&&... args) const
  -> decltype(call(_Indexes(), _M_functor, _M_data, std::forward<Args>(args)...))
  {    return call(_Indexes(), _M_functor, _M_data, std::forward<Args>(args)...); }

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
