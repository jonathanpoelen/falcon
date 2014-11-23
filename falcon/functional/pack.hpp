#ifndef FALCON_FUNCTIONAL_PACK_HPP
#define FALCON_FUNCTIONAL_PACK_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <tuple>

namespace falcon {

template<std::size_t I, std::size_t N>
struct pack {
  constexpr pack() {}

private:
  template<std::size_t... Ints, class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    impl_(parameter_index<Ints...>, Ts && ... args) const
  , std::make_tuple(std::get<(Ints-1)>(std::forward_as_tuple(args...))...))

public:
  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts && ... args) const
  , impl_(build_range_parameter_index_t<I, I+N>(), std::forward<Ts>(args)...))
};

}

#endif
