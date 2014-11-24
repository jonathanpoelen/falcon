#ifndef FALCON_FN_CMP_EACH_ANY_HPP
#define FALCON_FN_CMP_EACH_ANY_HPP

#include <utility>

namespace falcon {
namespace fn {

namespace aux_ {
  template <class Comp, bool val>
  struct cmp_if_impl
  {
    struct is_transparent;

    constexpr cmp_if_impl() {}

    constexpr cmp_if_impl(Comp const & cmp)
    : cmp_(cmp)
    {}

    constexpr cmp_if_impl(Comp && cmp)
    : cmp_(std::move(cmp))
    {}

    template<class T, class U>
    constexpr bool operator()(T const& a, U const& b) const noexcept
    { return cmp_(a, b); }

    template<class T, class U, class... Ts>
    constexpr bool
    operator()(T const& a, U const& b, Ts const&... args) const noexcept
    { return bool(cmp_(a, b)) == val ? val : operator()(b, args...); }

  private:
    Comp cmp_;
  };
}

/// \example cmp_each(lt)(a,b,c) is equivalent to (a < b && b < c)
template<class Cmp>
using cmp_each_fn = aux_::cmp_if_impl<Cmp, false>;

/// \example cmp_any(lt)(a,b,c) is equivalent to (a < b || b < c)
template<class Cmp>
using cmp_any_fn = aux_::cmp_if_impl<Cmp, true>;

template<class Cmp>
cmp_each_fn<Cmp> cmp_each(Cmp cmp)
{ return {std::move(cmp)}; }

template<class Cmp>
cmp_any_fn<Cmp> cmp_any(Cmp cmp)
{ return {std::move(cmp)}; }

}
}

#endif
