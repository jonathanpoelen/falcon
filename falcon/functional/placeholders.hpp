#ifndef FALCON_FUNCTIONAL_PLACEHOLDERS_HPP
#define FALCON_FUNCTIONAL_PLACEHOLDERS_HPP

#include <functional>

namespace falcon {
template<int N>
struct placeholder {};

namespace placeholders {
  constexpr placeholder<1> _1;
  constexpr placeholder<2> _2;
  constexpr placeholder<3> _3;
  constexpr placeholder<4> _4;
  constexpr placeholder<5> _5;
  constexpr placeholder<6> _6;
  constexpr placeholder<7> _7;
  constexpr placeholder<8> _8;
  constexpr placeholder<9> _9;
  constexpr placeholder<10> _10;
  constexpr placeholder<11> _11;
  constexpr placeholder<12> _12;
  constexpr placeholder<13> _13;
  constexpr placeholder<14> _14;
  constexpr placeholder<15> _15;
  constexpr placeholder<16> _16;
  constexpr placeholder<17> _17;
  constexpr placeholder<18> _18;
  constexpr placeholder<19> _19;
  constexpr placeholder<20> _20;
  constexpr placeholder<21> _21;
  constexpr placeholder<22> _22;
  constexpr placeholder<23> _23;
  constexpr placeholder<24> _24;
  constexpr placeholder<25> _25;
  constexpr placeholder<26> _26;
  constexpr placeholder<27> _27;
  constexpr placeholder<28> _28;
  constexpr placeholder<29> _29;
}
}

namespace std {
template<int N>
struct is_placeholder<::falcon::placeholder<N>>
: public integral_constant<int, N>
{};
}

#endif
