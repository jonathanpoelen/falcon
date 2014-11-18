#ifndef FALCON_LAMBDA_PROTECT_HPP
#define FALCON_LAMBDA_PROTECT_HPP

#include <falcon/lambda/lambda.hpp>

namespace falcon {
namespace lambda {

namespace _aux {

struct protect_t {};

template<class F>
struct lambda<protect_t, F>
: lambda_operators<lambda<protect_t, F>>
, lambda_with_tuple<F, protect_t>
{
  using lambda::with_tuple_type::lambda_with_tuple;
  using lambda::operators_type::operator=;

  template<class... Args>
  constexpr const F & operator()(Args&&...) const {
    return std::get<0>(this->t);
  }
};

}

template<class F>
constexpr _aux::lambda<_aux::protect_t, F>
protect(F && f)
{ return {std::forward<F>(f), _aux::protect_t()}; }

}
}

#endif
