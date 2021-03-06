#ifndef FALCON_ALGORITHM_UNORDERED_HPP
#define FALCON_ALGORITHM_UNORDERED_HPP

#include <falcon/utility/move.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

/**
 * \brief Removes the element at pos. The end member is moved to fill the void.
 *
 * @a cont must provide the following functions with the usual semantics:
 *  - back()
 *  - pop_back()
 */
template<typename Container>
typename range_access_iterator<Container>::type
unordered_erase(Container & cont, typename range_access_iterator<Container>::type pos)
{
  if(pos + 1 != cont.end()) {
    *pos = FALCON_MOVE(cont.back());
  }
  cont.pop_back();
  return pos;
}

/**
 * \brief Removes the elements in the range [first; last). The end members are moved to fill the void.
 *
 * @a cont must provide the following functions with the usual semantics:
 *  - end()
 *  - erase(first, last)
 */
template<typename Container>
typename range_access_iterator<Container>::type
unordered_erase(
  Container & cont
, typename range_access_iterator<Container>::type first
, typename range_access_iterator<Container>::type last)
{
  if(last == cont.end()) {
    return cont.erase(first, last);
  }

  typedef Container container_type;
  typedef typename container_type::difference_type difference_type;
  difference_type dis = last - first;
  difference_type rdis = cont.end() - last;
  if(rdis <= dis) {
    return cont.erase(first, last);
  }

  typedef typename container_type::iterator iterator;
  for(iterator pos = cont.end() - dis; first != last; ++first, ++pos) {
    *first = FALCON_MOVE(*pos);
  }
  return cont.erase(cont.end() - dis, cont.end());
}


template<typename BidirectionIt, typename UnaryPredicate>
BidirectionIt
unordered_remove_if(BidirectionIt first, BidirectionIt last, UnaryPredicate p)
{
  while (first != last) {
    if (p(*first)) {
      while (first != --last) {
        if (!p(*last)) {
          *first = FALCON_MOVE(*last);
          goto next;
        }
      }
      break;
    }
    next:
    ++first;
  }
  return first;
}

template<typename BidirectionIt, typename T>
BidirectionIt
unordered_remove(BidirectionIt first, BidirectionIt last, const T& x)
{
  while (first != last) {
    if (*first == x) {
      while (first != --last) {
        if (*last != x) {
          *first = FALCON_MOVE(*last);
          goto next;
        }
      }
      break;
    }
    next:
    ++first;
  }
  return first;
}

}

#endif
