#ifndef FALCON_UTILITY_TEMPORARY_INSERT_HPP
#define FALCON_UTILITY_TEMPORARY_INSERT_HPP

#include <falcon/utility/move.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/pack.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/arg/arg.hpp>
#include <falcon/type_traits/enable_type.hpp>

#if __cplusplus >= 201103L
# include <initializer_list>
#endif

namespace falcon {

// TODO const_iterator_no_conflict
template<class C, class = typename C::iterator, class = typename C::const_iterator>
struct __inserter_no_conflict
{
  typedef typename C::const_iterator type;
};

template<class C, class I>
class __inserter_no_conflict<C, I, I>;

struct inserter
{
  template<class Container>
  typename Container::iterator
  operator()(Container& cont,
             typename Container::value_type CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { return cont.insert(FALCON_FORWARD(typename Container::value_type, new_value)); }

  template<class Container>
  typename Container::iterator
  operator()(Container& cont, typename Container::iterator pos,
             typename Container::value_type CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { return cont.insert(pos, FALCON_FORWARD(typename Container::value_type, new_value)); }

  template<class Container>
  typename Container::iterator
  operator()(Container& cont, typename __inserter_no_conflict<Container>::type pos,
             typename Container::value_type CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { return cont.insert(pos, FALCON_FORWARD(typename Container::value_type, new_value)); }

#if __cplusplus >= 201103L
  template<class Container, class T>
  void operator()(Container& cont, std::initializer_list<T>);
#endif
};

#if __cplusplus >= 201103L
struct emplacement
{
  template<class Container, class... Ts>
  typename Container::iterator
  operator()(Container& cont, Ts&&... args) const
  { return cont.emplace(std::forward<Ts>(args)...); }
};

struct associative_emplacement
{
  template<class Container, class... Ts>
  std::pair<typename Container::iterator, bool>
  operator()(Container& cont, Ts&&... args) const
  { return cont.emplace(std::forward<Ts>(args)...); }
};

struct hint_emplacement
{
  template<class Container, class... Ts>
  typename Container::iterator
  operator()(Container& cont, typename Container::const_iterator pos, Ts&&... args) const
  { return cont.hint_emplace(pos, std::forward<Ts>(args)...); }
};
#endif

struct associative_inserter
{
  template<class Container>
  std::pair<typename Container::iterator, bool>
  operator()(Container& cont, typename Container::value_type const & value) const
  { return cont.insert(value); }

#if __cplusplus >= 201103L
  template<class Container>
  std::pair<typename Container::iterator, bool>
  operator()(Container& cont, typename Container::value_type && value) const
  { return cont.insert(std::forward<typename Container::value_type>(value)); }
#endif
};

struct eraser
{
  template<class Container>
  void operator()(Container& cont,
                  typename Container::value_type CPP_RVALUE_OR_CONST_REFERENCE new_value) const
  { cont.erase(FALCON_FORWARD(typename Container::value_type, new_value)); }

  template<class Container>
  void operator()(Container& cont, typename Container::iterator pos) const
  { cont.erase(pos); }
};

struct associative_eraser
{
  template<class Container>
  void operator()(Container& cont, std::pair<typename Container::iterator, bool> pos) const
  {
    if (pos.second) {
      cont.erase(pos.first);
    }
  }
};


template<class Container, class Position = typename Container::iterator,
  class Inserter = inserter, class Deleter = eraser>
class temporary_insert
{
  Container * x;
  Inserter inserter;
  Deleter deleter;
  Position position;

public:
  template<class CPP_PACK U>
  temporary_insert(Container & cont,
                   U CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK new_value)
  : x(&cont)
  , position(inserter(cont, FALCON_FORWARD(U, new_value)CPP_PACK))
  {}

  template<class CPP_PACK U>
  temporary_insert(Container & cont, Inserter func_inserter, Deleter func_deleter,
                   U CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK new_value)
  : x(&cont)
  , inserter(func_inserter)
  , deleter(func_deleter)
  , position(inserter(cont, FALCON_FORWARD(U, new_value)CPP_PACK))
  {}

#if __cplusplus >= 201103L
  temporary_insert(temporary_insert &&) = default;
  temporary_insert(temporary_insert const &) = delete;
  temporary_insert& operator=(temporary_insert &&) = default;
  temporary_insert& operator=(temporary_insert const &) = delete;
#endif

  ~temporary_insert() CPP_NOEXCEPT
  {
    deleter(*x, FALCON_MOVE(position));
  }
};


template<class Container, class Inserter, class Deleter, class CPP_PACK U>
temporary_insert<Container, typename Container::iterator, Inserter, Deleter>
make_temporary_insert(Container & cont, Inserter CPP_RVALUE inserter, Deleter CPP_RVALUE deleter,
                      U CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK new_value)
{
  return temporary_insert<Container, typename Container::iterator, Inserter, Deleter>(
    cont
  , FALCON_FORWARD(Inserter, inserter)
  , FALCON_FORWARD(Deleter, deleter)
  , FALCON_FORWARD(U, new_value)CPP_PACK
  );
}

template<class Position, class Container, class Inserter, class Deleter, class CPP_PACK U>
temporary_insert<Container, Position, Inserter, Deleter>
make_temporary_insert(Container & cont, Inserter CPP_RVALUE inserter, Deleter CPP_RVALUE deleter,
                      U CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK new_value)
{
  return temporary_insert<Container, Position, Inserter, Deleter>(
    cont
  , FALCON_FORWARD(Inserter, inserter)
  , FALCON_FORWARD(Deleter, deleter)
  , FALCON_FORWARD(U, new_value)CPP_PACK
  );
}


template<class Container, class Position = typename Container::iterator, class = void>
struct __selector_inserter
{
  typedef temporary_insert<Container, Position> type;
};

template<class Container, class Position>
struct __selector_inserter<Container, Position
, typename enable_type<typename Container::key_type>::type>
{
  typedef temporary_insert<Container, std::pair<Position, bool>
    , associative_inserter, associative_eraser> type;
};

template<class Container>
typename __selector_inserter<Container>::type
temporary_inserter(Container & cont, typename Container::value_type const & new_value)
{
  typedef typename __selector_inserter<Container>::type result_type;
  return result_type(cont, new_value);
}

template<class Container, class T>
typename __selector_inserter<Container>::type
temporary_inserter(Container & cont, T CPP_RVALUE_OR_CONST_REFERENCE new_value)
{
  typedef typename __selector_inserter<Container>::type result_type;
  return result_type(cont, FALCON_FORWARD(T, new_value));
}

#if __cplusplus >= 201103L
template<class Container, class Position = typename Container::iterator, class = void>
struct __selector_emplacement
{
  typedef temporary_insert<Container, Position, emplacement> type;
};

template<class Container, class Position>
struct __selector_emplacement<Container, Position
, typename enable_type<typename Container::key_type>::type>
{
  typedef temporary_insert<Container, std::pair<Position, bool>
    , associative_emplacement, associative_eraser> type;
};

template<class Container, class... Ts>
typename __selector_emplacement<Container>::type
temporary_inserter(Container & cont, Ts&&... new_value)
{
  return {cont, std::forward<Ts>(new_value)...};
}
#endif

template<class Container>
temporary_insert<Container>
temporary_inserter(Container & cont, typename Container::iterator pos,
                   typename Container::value_type const & new_value)
{
  return temporary_insert<Container>(cont, new_value);
}

template<class Container>
temporary_insert<Container>
temporary_inserter(Container & cont, typename __inserter_no_conflict<Container>::type pos,
                   typename Container::value_type const & new_value)
{
  return temporary_insert<Container>(cont, new_value);
}

#if __cplusplus >= 201103L
template<class Container>
temporary_insert<Container>
temporary_inserter(Container & cont, typename Container::const_iterator pos,
                   typename Container::value_type && new_value)
{
  return {cont, pos, std::forward<typename Container::value_type>(new_value)};
}
#endif

}

#endif
