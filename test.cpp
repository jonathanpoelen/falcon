#include <iostream>
#include <falcon/c++/initialize.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/utility/maker.hpp>
#include <falcon/type_traits/identity.hpp>

struct POD {
  int x;
  int y;
};

std::ostream& operator<<(std::ostream& os, const POD& pod) {
  return os << pod.x << "-" << pod.y;
}


template <typename Class, typename T, unsigned N>
struct param_position_with_value
{
  typedef Class class_type;
  typedef T type;
  static constexpr unsigned position = N;

  type value;
};

template <typename Class, typename T, unsigned N>
struct param_position
{
  typedef Class class_type;
  typedef T type;
  static constexpr unsigned position = N;

  param_position_with_value<Class, T, N>
  operator=(type val) const ///TODO val -> && ?
  { return param_position_with_value<Class, T, N>{val}; }
};

struct param_check
{
  template <typename Class>
  static void check_class(falcon::identity<Class>...)
  {}

  template<typename Param>
  static void check_unique_index(const Param&)
  {}

  template<typename Param1, typename Param2, typename... Params>
  static void check_unique_index(const Param1& p1, const Param2& p2, const Params&... other)
  {
    static_assert(Param1::position != Param2::position, "same position index");
    check_unique_index(p1, other...);
    check_unique_index(p2, other...);
  }

  template <typename Class, typename... Params>
  static void check(const Params&... args)
  {
    check_class<POD>(falcon::identity<typename Params::class_type>()...);
    check_unique_index(args...);
  }
};


constexpr param_position<POD, int, 0> X;
constexpr param_position<POD, int, 1> Y;

template<typename... Args>
POD pod(Args... args)
{
  param_check::check<POD>(args...);
  typedef falcon::parameter_index<Args::position...> indexes;
  return falcon::call(indexes(), falcon::maker<POD>(), args.value...);
}

void f(){ std::cout << ("plop") << std::endl;}

typedef void(*func_t)();
constexpr const func_t pf= &f;

int main(/*int argc, char **argv*/)
{
  POD a CPP_INITIALIZE(2, 4);
  POD b = {5, 6};
  POD c = pod(X=3,Y=7);
  POD d = pod(Y=3,X=7);
  std::cout
  << a << "\n"
  << b << "\n"
  << c << "\n"
  << d << "\n"
  ;
  pf();
}

