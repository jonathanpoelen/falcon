#ifndef FALCON_UTILITY_TEMPORARY_PUSH_HPP
#define FALCON_UTILITY_TEMPORARY_PUSH_HPP

#include <falcon/utility/move.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/extend_pack.hpp>

namespace falcon {

struct pusher
{
  template<class Container, class T>
  void operator()(Container& cont,
                  T CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { cont.push(FALCON_FORWARD(T, new_value)); }
};

struct back_pusher
{
  template<class Container, class T>
  void operator()(Container& cont,
                  T CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { cont.push_back(FALCON_FORWARD(T, new_value)); }
};

struct front_pusher
{
  template<class Container, class T>
  void operator()(Container& cont,
                  T CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { cont.push_front(FALCON_FORWARD(T, new_value)); }
};

#if __cplusplus >= 201103L
struct emplace_pusher
{
  template<class Container, class... Ts>
  void operator()(Container& cont, Ts && ... new_value) const
  { cont.emplace(std::forward<Ts>(new_value)...); }
};

struct emplace_back_pusher
{
  template<class Container, class... Ts>
  void operator()(Container& cont, Ts && ... new_value) const
  { cont.emplace_back(std::forward<Ts>(new_value)...); }
};

struct emplace_front_pusher
{
  template<class Container, class... Ts>
  void operator()(Container& cont, Ts && ... new_value) const
  { cont.emplace_front(std::forward<Ts>(new_value)...); }
};
#endif

struct poper
{
  template<class Container>
  void operator()(Container& cont) const CPP_NOEXCEPT
  { cont.pop(); }
};

struct back_poper
{
  template<class Container>
  void operator()(Container& cont) const CPP_NOEXCEPT
  { cont.pop_back(); }
};

struct front_poper
{
  template<class Container>
  void operator()(Container& cont) const CPP_NOEXCEPT
  { cont.pop_front(); }
};


template<class Container, class Pusher = pusher, class Poper = poper>
class temporary_push
{
  Container * x;
  Pusher pusher;
  Poper poper;

public:
  template<class CPP_EXTEND_PACK U>
  temporary_push(Container & cont,
                 U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
  : x(&cont)
  {
    pusher(cont, FALCON_FORWARD(U, new_value) CPP_EXTEND_PACK);
  }

  template<class TPusher, class TPoper, class CPP_EXTEND_PACK U>
  temporary_push(Container & cont,
                 TPusher CPP_RVALUE func_pusher, TPoper CPP_RVALUE func_poper,
                 U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
  : x(&cont)
  , pusher(FALCON_FORWARD(Pusher, func_pusher))
  , poper(FALCON_FORWARD(Poper, func_poper))
  {
    pusher(cont, FALCON_FORWARD(U, new_value) CPP_EXTEND_PACK);
  }

#if __cplusplus >= 201103L
  temporary_push(temporary_push &&) = default;
  temporary_push(temporary_push const &) = delete;
  temporary_push& operator=(temporary_push &&) = default;
  temporary_push& operator=(temporary_push const &) = delete;
#endif

  ~temporary_push() CPP_NOEXCEPT
  {
    poper(*x);
  }
};


#if __cplusplus >= 201103L
template<class Container>
using temporary_back_insert = temporary_push<Container, back_pusher, back_poper>;

template<class Container>
using temporary_front_insert = temporary_push<Container, front_pusher, front_poper>;

template<class Container>
using temporary_emplace = temporary_push<Container, emplace_pusher, poper>;

template<class Container>
using temporary_back_emplace
  = temporary_push<Container, emplace_back_pusher, back_poper>;

template<class Container>
using temporary_front_emplace
  = temporary_push<Container, emplace_front_pusher, front_poper>;


template<class Container, class... Ts>
temporary_emplace<Container>
temporary_emplacement(Container & cont, Ts && ...new_value)
{
  return temporary_emplace<Container>(cont, std::forward<Ts>(new_value)...);
}

template<class Container, class... Ts>
temporary_back_emplace<Container>
temporary_back_emplacement(Container & cont, Ts && ...new_value)
{
  return {cont, std::forward<Ts>(new_value)...};
}

template<class Container, class... Ts>
temporary_front_emplace<Container>
temporary_front_emplacement(Container & cont, Ts && ...new_value)
{
  return {cont, std::forward<Ts>(new_value)...};
}
#else
template<class Container>
struct temporary_back_insert
: temporary_push<Container, back_pusher, back_poper>
{
  template<class U>
  temporary_back_insert(Container & cont, const U & new_value)
  : temporary_push(cont, new_value)
  {}
};

template<class Container>
struct temporary_front_insert
: temporary_push<Container, front_pusher, front_poper>
{
  template<class U>
  temporary_front_insert(Container & cont, const U & new_value)
  : temporary_push(cont, new_value)
  {}
};
#endif

template<class Container, class CPP_EXTEND_PACK U>
temporary_push<Container>
temporary_pusher(Container & cont,
                 U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
{
  return temporary_push<Container>(cont, FALCON_FORWARD(U, new_value)CPP_EXTEND_PACK);
}

template<class Container, class CPP_EXTEND_PACK U>
temporary_push<Container, front_pusher, front_poper>
temporary_front_inserter(Container & cont,
                         U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
{
  return temporary_push<Container, front_pusher, front_poper>
  (cont, FALCON_FORWARD(U, new_value)CPP_EXTEND_PACK);
}

template<class Container, class CPP_EXTEND_PACK U>
temporary_push<Container, back_pusher, back_poper>
temporary_back_inserter(Container & cont,
                        U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
{
  return temporary_push<Container, back_pusher, back_poper>
  (cont, FALCON_FORWARD(U, new_value)CPP_EXTEND_PACK);
}

template<class Container, class Pusher, class Poper, class CPP_EXTEND_PACK U>
temporary_push<Container, Pusher, Poper>
make_temporary_push(Container & cont,
                    Pusher CPP_RVALUE func_pusher, Poper CPP_RVALUE func_poper,
                    U CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK new_value)
{
  return temporary_push<Container, Pusher, Poper>
  (cont, func_pusher, func_poper, FALCON_FORWARD(U, new_value)CPP_EXTEND_PACK);
}

}

#endif
