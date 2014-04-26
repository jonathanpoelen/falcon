#ifndef FALCON_ALGORITHM_MERGE_UNIQUE_HPP
#define FALCON_ALGORITHM_MERGE_UNIQUE_HPP

#include <falcon/iterator/nexter_iterator.hpp>
#include <algorithm>

namespace falcon {
namespace algorithm {

namespace _aux {
  template<class It>
  struct NextUniq {
    It last;
#if __cplusplus < 201103L
    NextUniq(){}
    NextUniq(It i):last(i) {}
#endif

    void operator()(It & it) const
    {
      It itn = it;
      ++it;
      while (it != last && *it == *itn) {
        itn = it;
        ++it;
      }
    }
  };
}


template<class InputIt1, class InputIt2, class OutputIt>
OutputIt unique_merge(InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, InputIt2 last2,
                      OutputIt d_first)
{
  using falcon::iterator::nexter_iterator;
  typedef nexter_iterator<InputIt1, _aux::NextUniq<InputIt1> > NInputIt1;
  typedef nexter_iterator<InputIt2, _aux::NextUniq<InputIt2> > NInputIt2;
  return std::set_union(
#if __cplusplus >= 201103L
    NInputIt1(first1, {last1}), NInputIt1(last1)
  , NInputIt2(first2, {last2}), NInputIt2(last2)
#else
    NInputIt1(first1, _aux::NextUniq<InputIt1>(last1)), NInputIt1(last1)
  , NInputIt2(first2, _aux::NextUniq<InputIt2>(last2)), NInputIt2(last2)
#endif
  , d_first
  );
}


template<class InputIt1, class InputIt2, class OutputIt, class BinaryPredicate>
OutputIt unique_merge(InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, InputIt2 last2,
                      OutputIt d_first,
                      BinaryPredicate binary_pred)
{
  using falcon::iterator::nexter_iterator;
  typedef nexter_iterator<InputIt1, _aux::NextUniq<InputIt1> > NInputIt1;
  typedef nexter_iterator<InputIt2, _aux::NextUniq<InputIt2> > NInputIt2;
  return std::set_union(
#if __cplusplus >= 201103L
    NInputIt1(first1, {last1}), NInputIt1(last1)
  , NInputIt2(first2, {last2}), NInputIt2(last2)
#else
    NInputIt1(first1, _aux::NextUniq<InputIt1>(last1)), NInputIt1(last1)
  , NInputIt2(first2, _aux::NextUniq<InputIt2>(last2)), NInputIt2(last2)
#endif
  , d_first, binary_pred
  );
}

}
}

#endif
