#ifndef FALCON_ALGORITHM_MERGE_UNIQUE_HPP
#define FALCON_ALGORITHM_MERGE_UNIQUE_HPP

#include <falcon/functional/operators.hpp>
#include <falcon/iterator/iterator_category.hpp>
#include <algorithm>

namespace falcon {
namespace algorithm {

namespace _aux {
template<class ForwardIt, class OutputIt, class BinaryPredicate>
OutputIt unique_merge(ForwardIt first1, ForwardIt last1,
                      ForwardIt first2, ForwardIt last2,
                      OutputIt d_first,
                      BinaryPredicate binary_pred,
                      std::forward_iterator_tag)
{
  if (first1 != last1 && first2 != last2) {
    ForwardIt x = (*first1 < *first2) ? first1++ : first2++;
    *d_first = *x;
    ++d_first;

    while (first1 != last1) {
      if (first2 == last2) {
        while (first1 != last1 && *x == *first1) {
          ++first1;
        }
        d_first = std::unique_copy(first1, last1, d_first);
        break ;
      }
      if (*first2 < *first1) {
        if (!bool(binary_pred(*x, *first2))) {
          x = first2;
          *d_first = *x;
          ++d_first;
        }
        ++first2;
      } else {
        if (!bool(binary_pred(*x, *first1))) {
          x = first1;
          *d_first = *x;
          ++d_first;
        }
        ++first1;
      }
    }

    while (first2 != last2 && *x == *first2) {
      ++first2;
    }
  }
  else if (first1 != last1) {
    return std::unique_copy(first1, last1, d_first);
  }

  return std::unique_copy(first2, last2, d_first);
}

template<class InputIt, class InputIt2, class OutputIt, class BinaryPredicate>
OutputIt unique_merge(InputIt first1, InputIt last1,
                      InputIt2 first2, InputIt2 last2,
                      OutputIt d_first,
                      BinaryPredicate binary_pred,
                      std::input_iterator_tag)
{
  if (first1 != last1 && first2 != last2) {
    typedef typename std::iterator_traits<InputIt>::value_type value_type;
    value_type x = (*first1 < *first2) ? *first1++ : *first2++;
    *d_first = x;
    ++d_first;

    while (first1 != last1) {
      if (first2 == last2) {
        while (first1 != last1 && x == *first1) {
          ++first1;
        }
        d_first = std::unique_copy(first1, last1, d_first);
        break ;
      }
      if (*first2 < *first1) {
        if (!bool(binary_pred(x, *first2))) {
          x = *first2;
          *d_first = x;
          ++d_first;
        }
        ++first2;
      } else {
        if (!bool(binary_pred(x, *first1))) {
          x = *first1;
          *d_first = x;
          ++d_first;
        }
        ++first1;
      }
    }

    while (first2 != last2 && binary_pred(x, *first2)) {
      ++first2;
    }
  }
  else if (first1 != last1) {
    return std::unique_copy(first1, last1, d_first);
  }

  return std::unique_copy(first2, last2, d_first);
}
}


template<class InputIt1, class InputIt2, class OutputIt>
OutputIt unique_merge(InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, InputIt2 last2,
                      OutputIt d_first)
{
  return _aux::unique_merge(first1, last1, first2, last2, d_first, equal_to<>(),
                            iterator::iterator_category<InputIt1>());
}


template<class InputIt1, class InputIt2, class OutputIt, class BinaryPredicate>
OutputIt unique_merge(InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, InputIt2 last2,
                      OutputIt d_first,
                      BinaryPredicate binary_pred)
{
  return _aux::unique_merge(first1, last1, first2, last2, d_first, binary_pred,
                            iterator::iterator_category<InputIt1>());
}

}
}

#endif
