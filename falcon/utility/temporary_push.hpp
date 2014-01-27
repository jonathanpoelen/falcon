#ifndef FALCON_UTILITY_TEMPORARY_PUSH_HPP
#define FALCON_UTILITY_TEMPORARY_PUSH_HPP

#include <falcon/utility/move.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/extend_pack.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {

struct pusher
{
  template<class Cont, class T>
  void operator()(Cont& x, T CPP_RVALUE_OR_CONST_REFERENCE new_value) const CPP_NOEXCEPT
  { x.push(FALCON_FORWARD(T, new_value)); }
};

struct back_pusher
{
  template<class Cont, class T>
  void operator()(Cont& x, T CPP_RVALUE_OR_CONST_REFERENCE new_value) const CPP_NOEXCEPT
  { x.push_back(FALCON_FORWARD(T, new_value)); }
};

struct front_pusher
{
  template<class Cont, class T>
  void operator()(Cont& x, T CPP_RVALUE_OR_CONST_REFERENCE new_value) const CPP_NOEXCEPT
  { x.push_front(FALCON_FORWARD(T, new_value)); }
};

#if __cplusplus >= 201103L
struct emplace_pusher
{
  template<class Cont, class... Ts>
  void operator()(Cont& x, Ts && ... new_value) const noexcept
  { x.emplace(std::forward<Ts>(new_value)...); }
};

struct emplace_back_pusher
{
  template<class Cont, class... Ts>
  void operator()(Cont& x, Ts && ... new_value) const noexcept
  { x.emplace_back(std::forward<Ts>(new_value)...); }
};

struct emplace_front_pusher
{
  template<class Cont, class... Ts>
  void operator()(Cont& x, Ts && ... new_value) const noexcept
  { x.emplace_front(std::forward<Ts>(new_value)...); }
};
#endif

struct poper
{
  template<class Cont, class T>
  void operator()(Cont& x) const CPP_NOEXCEPT
  { x.pop(); }
};

struct back_poper
{
  template<class Cont, class T>
  void operator()(Cont& x) const CPP_NOEXCEPT
  { x.pop_back(); }
};

struct front_poper
{
  template<class Cont, class T>
  void operator()(Cont& x) const CPP_NOEXCEPT
  { x.pop_front(); }
};


template<class T, class Pusher = pusher, class Poper = poper>
class temporary_push
{
  T& cont;
  Pusher pusher;
  Poper poper;

public:
  template<class CPP_EXTEND_PACK U>
  temporary_push(T& x, U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
  : cont(x)
  {
    pusher(cont, FALCON_FORWARD(U, new_value) CPP_EXTEND_PACK);
  }

  template<class CPP_EXTEND_PACK U>
  temporary_push(T& x, Pusher CPP_RVALUE func_pusher, Poper CPP_RVALUE func_poper,
                 U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
  : cont(x)
  , pusher(FALCON_FORWARD(Pusher, func_pusher))
  , poper(FALCON_FORWARD(Poper, func_poper))
  {
    pusher(cont, FALCON_FORWARD(U, new_value) CPP_EXTEND_PACK);
  }

  ~temporary_push() CPP_NOEXCEPT
  {
    poper(cont);
  }
};

template<class T>
struct temporary_push_back
: temporary_push<T, back_pusher, back_poper>
{
  template<class U>
  temporary_push_back(T& x, U CPP_RVALUE new_value)
  : temporary_push(x, FALCON_FORWARD(U, new_value))
  {}
};

template<class T>
struct temporary_push_front
: temporary_push<T, front_pusher, front_poper>
{
  template<class U>
  temporary_push_front(T& x, U CPP_RVALUE new_value)
  : temporary_push(x, FALCON_FORWARD(U, new_value))
  {}
};

#if __cplusplus >= 201103L
template<class T>
using temporary_emplace = temporary_push<T, emplace_pusher, poper>;

template<class T>
struct temporary_emplace_back
: temporary_push<T, emplace_back_pusher, back_poper>
{
  template<class U>
  temporary_emplace_back(T& x, U CPP_RVALUE new_value)
  : temporary_push(x, FALCON_FORWARD(U, new_value))
  {}
};

template<class T>
struct temporary_emplace_front
: temporary_push<T, emplace_front_pusher, front_poper>
{
  template<class U>
  temporary_emplace_front(T& x, U CPP_RVALUE new_value)
  : temporary_push(x, FALCON_FORWARD(U, new_value))
  {}
};
#endif

template<class T, class Pusher, class Poper, class CPP_EXTEND_PACK U>
temporary_push<T, Pusher, Poper>
make_temporary_push(T& x, Pusher CPP_RVALUE func_pusher, Poper CPP_RVALUE func_poper,
                    U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
{
  return temporary_push<T, Pusher, Poper>(x, func_pusher, func_poper,
                                          FALCON_FORWARD(U, new_value));
}

}

#endif
