#ifndef FALCON_ALGORITHM_UNORDERED_HPP
#define FALCON_ALGORITHM_UNORDERED_HPP

#include <falcon/utility/move.hpp>

namespace falcon {

template<typename Container>
typename Container::iterator
unordered_erase(Container & cont,
#if __cplusplus >= 201103L
                typename Container::const_iterator pos
#else
                typename Container::iterator pos
#endif
)
{
  if(pos + 1 != cont.end()) {
#if __cplusplus >= 201103L
    *const_cast<typename Container::pointer>(pos.base())
    = std::move(cont.back());
#else
    *pos = cont.back();
#endif
  }
  cont.pop_back();
#if __cplusplus >= 201103L
  return cont.begin() + (cont.end() - pos);
#else
  return pos;
#endif
}

template<typename Container>
typename Container::iterator
unordered_erase(Container & cont,
#if __cplusplus >= 201103L
                typename Container::const_iterator first,
                typename Container::const_iterator last
#else
                typename Container::iterator first,
                typename Container::iterator last,
#endif
)
{
  if(last = cont.end()) {
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
#if __cplusplus >= 201103L
    *const_cast<typename Container::pointer>(first.base())
    = std::move(*pos);
#else
    *first = *pos;
#endif
  }
  return cont.erase(cont.end() - dis, cont.end());
}


template<typename BidirectionIt, typename UnaryPredicate>
BidirectionIt unordered_remove_if(BidirectionIt first, BidirectionIt last,
                                  UnaryPredicate p)
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
BidirectionIt unordered_remove(BidirectionIt first, BidirectionIt last, const T& x)
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
