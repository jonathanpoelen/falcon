#ifndef FALCON_ALGORITHM_TRANSFORM_ACCUMULATE_HPP
#define FALCON_ALGORITHM_TRANSFORM_ACCUMULATE_HPP

namespace falcon {

/**
 * \brief init = op(init, unary_op(*first))
 * \see std::transform and std::accumulate
 */
template<
  class InputIt, class UnaryOperation
, class T, class BinaryOperation>
T transform_accumulate(
  InputIt first, InputIt last, UnaryOperation unary_op
, T init, BinaryOperation op)
{
  for (; first != last; ++first) {
    init = op(init, unary_op(*first));
  }
  return init;
}


/**
* \brief init = op(init, unary_op(*first))
* \see std::transform and std::accumulate
*/
template<
  class InputIt1, class InputIt2, class BinaryOperation
, class T, class BinaryOperationReduce>
T transform_accumulate(
  InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op
, T init, BinaryOperationReduce op)
{
  for (; first1 != last1; ++first1, ++first2) {
    init = op(init, binary_op(*first1, *first2));
  }
  return init;
}

}

#endif
