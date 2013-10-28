#ifndef FALCON_ITERATOR_ITERATOR_PAIR_HPP
#define FALCON_ITERATOR_ITERATOR_PAIR_HPP

#include <falcon/container/range_access.hpp>

namespace falcon {

template<typename Container>
std::pair<
  typename range_access_iterator<Container>::type,
  typename range_access_iterator<Container>::type
>
iterator_pair(Container & cont)
{
#if __cplusplus >= 201103L
  return {begin(cont), end(cont)};
#else
  return std::make_pair(begin(cont), end(cont));
#endif
}

template<typename Container>
std::pair<
  typename range_access_iterator<const Container>::type,
  typename range_access_iterator<const Container>::type
>
const_iterator_pair(const Container & cont)
{
#if __cplusplus >= 201103L
  return {begin(cont), end(cont)};
#else
  return std::make_pair(begin(cont), end(cont));
#endif
}

template<typename Container>
std::pair<
  typename range_access_reverse_iterator<Container>::type,
  typename range_access_reverse_iterator<Container>::type
>
reverse_iterator_pair(Container & cont)
{
#if __cplusplus >= 201103L
  return {rbegin(cont), rend(cont)};
#else
  return std::make_pair(rbegin(cont), rend(cont));
#endif
}

template<typename Container>
std::pair<
  typename range_access_reverse_iterator<const Container>::type,
  typename range_access_reverse_iterator<const Container>::type
>
reverse_iterator_pair(const Container & cont)
{
#if __cplusplus >= 201103L
  return {rbegin(cont), rend(cont)};
#else
  return std::make_pair(rbegin(cont), rend(cont));
#endif
}

}

#endif
