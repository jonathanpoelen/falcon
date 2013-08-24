#ifndef _FALCON_ITERATOR_RANGE_ACCESS_HPP
#define _FALCON_ITERATOR_RANGE_ACCESS_HPP

#if __cplusplus >= 201103L
# include <utility>
#else
# include <falcon/type_traits/use_if.hpp>
# include <cstddef>
#endif

#include <iterator>


/// @defgroup sequences Sequences

namespace falcon {

#if __cplusplus >= 201103L
  using std::begin;
  using std::end;
#if __cplusplus > 201103L
  using std::rbegin;
  using std::rend;
#else
  template<class Container>
  inline auto rbegin(Container& cont)
  -> decltype(cont.rbegin())
  { return cont.rbegin(); }

  template<class Container>
  inline auto rbegin(const Container& cont)
  -> decltype(cont.rbegin())
  { return cont.rbegin(); }

  template<class Container>
  inline auto rend(Container& cont)
  -> decltype(cont.rend())
  { return cont.rend(); }

  template<class Container>
  inline auto rend(const Container& cont)
  -> decltype(cont.rend())
  { return cont.rend(); }
#endif

  template<class Container>
  inline auto cbegin(const Container& cont)
  -> decltype(begin(cont))
  { return begin(cont); }

  template<class Container>
  inline auto cend(const Container& cont)
  -> decltype(end(cont))
  { return end(cont); }

  template<class Container>
  inline auto crbegin(const Container& cont)
  -> decltype(rbegin(cont))
  { return rbegin(cont); }

  template<class Container>
  inline auto crend(const Container& cont)
  -> decltype(rend(cont))
  { return rend(cont); }

#else

  template <typename Container>
  struct range_access_iterator
  : use_if<use_iterator<Container>, use_const_iterator<Container> >
  {};

  template <typename T, std::size_t N>
  struct range_access_iterator<T[N]>
  {
      typedef T* type;
  };

  template <typename Container>
  struct range_access_iterator<const Container>
  : use_if<use_const_iterator<Container>, use_iterator<Container> >
  {};

  template <typename Container>
  struct range_access_reverse_iterator
  : use_if<use_reverse_iterator<Container>, use_const_reverse_iterator<Container> >
  {};

  template <typename T, std::size_t N>
  struct range_access_reverse_iterator<T[N]>
  {
      typedef T* type;
  };

  template <typename Container>
  struct range_access_reverse_iterator<const Container>
  : use_if<use_const_reverse_iterator<Container>, use_reverse_iterator<Container> >
  {};

  template<typename Container>
  inline typename range_access_iterator<Container>::type begin(Container& cont)
  { return cont.begin(); }

  template<typename Container>
  inline typename range_access_iterator<Container>::type end(Container& cont)
  { return cont.end(); }

  template<class T, size_t N>
  inline T* begin(T (&arr)[N])
  { return arr; }

  template<class T, size_t N>
  inline T* end(T (&arr)[N])
  { return arr + N; }

  template<typename Container>
  inline typename range_access_reverse_iterator<Container>::type rbegin(Container& cont)
  { return cont.rbegin(); }

  template<typename Container>
  inline typename range_access_reverse_iterator<Container>::type rend(Container& cont)
  { return cont.rend(); }

  template<typename Container>
  inline typename range_access_iterator<const Container>::type cbegin(const Container& cont)
  { return begin(cont); }

  template<typename Container>
  inline typename range_access_iterator<const Container>::type cend(const Container& cont)
  { return end(cont); }

  template<typename Container>
  inline typename range_access_reverse_iterator<const Container>::type crbegin(const Container& cont)
  { return rbegin(cont); }

  template<typename Container>
  inline typename range_access_reverse_iterator<const Container>::type crend(const Container& cont)
  { return rend(cont); }

#endif

#if !(__cplusplus > 201103L)
  template<class T, size_t N>
  inline std::reverse_iterator<T*> rbegin(T (&arr)[N])
  { return std::reverse_iterator<T*>(begin(arr)); }

  template<class T, size_t N>
  inline std::reverse_iterator<T*> rend(T (&arr)[N])
  { return std::reverse_iterator<T*>(end(arr)); }
#endif

  template<class T, size_t N>
  inline const T* cbegin(const T (&arr)[N])
  { return begin(arr); }

  template<class T, size_t N>
  inline const T* cend(const T (&arr)[N])
  { return begin(arr); }

  template<class T, size_t N>
  inline std::reverse_iterator<const T*> crbegin(const T (&arr)[N])
  { return rbegin(arr); }

  template<class T, size_t N>
  inline std::reverse_iterator<const T*> crend(const T (&arr)[N])
  { return rbegin(arr); }


#if __cplusplus >= 201103L
  template <typename Container>
  struct range_access_iterator
  {
    typedef decltype(begin(std::declval<Container&>())) type;
  };

  template <typename Container>
  struct range_access_reverse_iterator
  {
    typedef decltype(rbegin(std::declval<Container&>())) type;
  };
#endif


  template <typename Container>
  struct range_access_subtype
  {
    typedef typename std::iterator_traits<
      typename range_access_iterator<Container>::type
    >::value_type type;
  };

}

#endif
