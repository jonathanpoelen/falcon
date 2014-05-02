#ifndef FALCON_ITERATOR_RANGE_ACCESS_HPP
#define FALCON_ITERATOR_RANGE_ACCESS_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>

#if __cplusplus >= 201103L
# include <utility>
#else
# include <falcon/type_traits/use_if.hpp>
# include <cstddef>
#endif

#include <iterator>


/// @defgroup sequences Sequences

namespace falcon {

#if __cplusplus > 201103L

using std::begin;
using std::end;
using std::rbegin;
using std::rend;
using std::cbegin;
using std::cend;
using std::crbegin;
using std::crend;

#elif __cplusplus == 201103L

  using std::begin;
  using std::end;

  template<class Container>
  auto rbegin(Container& cont)
  noexcept(noexcept(cont.rbegin()))
  -> decltype(cont.rbegin())
  { return cont.rbegin(); }

  template<class Container>
  auto rbegin(const Container& cont)
  noexcept(noexcept(cont.rbegin()))
  -> decltype(cont.rbegin())
  { return cont.rbegin(); }

  template<class Container>
  auto rend(Container& cont)
  noexcept(noexcept(cont.rend()))
  -> decltype(cont.rend())
  { return cont.rend(); }

  template<class Container>
  auto rend(const Container& cont)
  noexcept(noexcept(cont.rend()))
  -> decltype(cont.rend())
  { return cont.rend(); }

  template<class Container>
  auto cbegin(const Container& cont)
  noexcept(noexcept(cont.cbegin()))
  -> decltype(begin(cont))
  { return begin(cont); }

  template<class Container>
  auto cend(const Container& cont)
  noexcept(noexcept(cont.cend()))
  -> decltype(end(cont))
  { return end(cont); }

  template<class Container>
  auto crbegin(const Container& cont)
  noexcept(noexcept(cont.crbegin()))
  -> decltype(rbegin(cont))
  { return rbegin(cont); }

  template<class Container>
  auto crend(const Container& cont)
  noexcept(noexcept(cont.crend()))
  -> decltype(rend(cont))
  { return rend(cont); }

#else

  template<class Container>
  struct range_access_iterator
  : use_if<use_iterator<Container>, use_const_iterator<Container> >
  {};

  template<class T std::size_t N>
  struct range_access_iterator<T[N]>
  {
      typedef T* type;
  };

  template<class Container>
  struct range_access_iterator<const Container>
  : use_if<use_const_iterator<Container>, use_iterator<Container> >
  {};

  template<class Container>
  struct range_access_reverse_iterator
  : use_if<use_reverse_iterator<Container>, use_const_reverse_iterator<Container> >
  {};

  template<class T std::size_t N>
  struct range_access_reverse_iterator<T[N]>
  {
      typedef T* type;
  };

  template<class Container>
  struct range_access_reverse_iterator<const Container>
  : use_if<use_const_reverse_iterator<Container>, use_reverse_iterator<Container> >
  {};

  template<class Container>
  inline typename range_access_iterator<Container>::type begin(Container& cont)
  { return cont.begin(); }

  template<class Container>
  inline typename range_access_iterator<Container>::type end(Container& cont)
  { return cont.end(); }

  template<class Container>
  inline typename range_access_reverse_iterator<Container>::type rbegin(Container& cont)
  { return cont.rbegin(); }

  template<class Container>
  inline typename range_access_reverse_iterator<Container>::type rend(Container& cont)
  { return cont.rend(); }

  template<class Container>
  inline typename range_access_iterator<const Container>::type cbegin(const Container& cont)
  { return begin(cont); }

  template<class Container>
  inline typename range_access_iterator<const Container>::type cend(const Container& cont)
  { return end(cont); }

  template<class Container>
  inline typename range_access_reverse_iterator<const Container>::type crbegin(const Container& cont)
  { return rbegin(cont); }

  template<class Container>
  inline typename range_access_reverse_iterator<const Container>::type crend(const Container& cont)
  { return rend(cont); }

#endif

#if __cplusplus <= 201103L
  template<class T, std::size_t N>
  std::reverse_iterator<T*>
  rbegin(T (&arr)[N]) CPP_NOEXCEPT
  { return std::reverse_iterator<T*>(arr+N); }

  template<class T, std::size_t N>
  std::reverse_iterator<const T*>
  rbegin(const T (&arr)[N]) CPP_NOEXCEPT
  { return std::reverse_iterator<const T*>(arr+N); }

  template<class T, std::size_t N>
  std::reverse_iterator<T*>
  rend(T (&arr)[N]) CPP_NOEXCEPT
  { return std::reverse_iterator<T*>(arr); }

  template<class T, std::size_t N>
  std::reverse_iterator<const T*>
  rend(const T (&arr)[N]) CPP_NOEXCEPT
  { return std::reverse_iterator<const T*>(arr); }

  template<class T, std::size_t N>
  CPP_CONSTEXPR T const *
  cbegin(const T (&arr)[N]) CPP_NOEXCEPT
  { return arr; }

  template<class T, std::size_t N>
  CPP_CONSTEXPR const T *
  cend(const T (&arr)[N]) CPP_NOEXCEPT
  { return arr + N; }

  template<class T, std::size_t N>
  std::reverse_iterator<const T*>
  crbegin(const T (&arr)[N]) CPP_NOEXCEPT
  { return rbegin(arr); }

  template<class T, std::size_t N>
  std::reverse_iterator<const T*>
  crend(const T (&arr)[N]) CPP_NOEXCEPT
  { return rbegin(arr); }
#endif

#if __cplusplus >= 201103L
  template<class Container>
  struct range_access_iterator
  {
    typedef decltype(begin(std::declval<Container&>())) type;
  };

  template<class Container>
  struct range_access_reverse_iterator
  {
    typedef decltype(rbegin(std::declval<Container&>())) type;
  };
#endif


  template<class Container>
  struct range_access_subtype
  {
    typedef typename std::iterator_traits<
      typename range_access_iterator<Container>::type
    >::value_type type;
  };

}

#endif
