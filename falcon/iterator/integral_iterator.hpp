#ifndef FALCON_ITERATOR_INTEGRAL_ITERATOR_HPP
#define FALCON_ITERATOR_INTEGRAL_ITERATOR_HPP

#include <falcon/iterator/integer_iterator.hpp>

namespace falcon {
namespace iterator {

typedef integer_iterator<int,          integer_iterator_less_comparison_tag> int_iterator;
typedef integer_iterator<unsigned int, integer_iterator_less_comparison_tag> uint_iterator;
typedef integer_iterator<long,         integer_iterator_less_comparison_tag> long_iterator;
typedef integer_iterator<unsigned long,integer_iterator_less_comparison_tag> ulong_iterator;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
typedef integer_iterator<long long, integer_iterator_less_comparison_tag> long_long_iterator;
typedef integer_iterator<unsigned long long, integer_iterator_less_comparison_tag> ulong_long_iterator;
#endif

typedef reverse_integer_iterator<int,          integer_iterator_less_comparison_tag> reverse_int_iterator;
typedef reverse_integer_iterator<unsigned int, integer_iterator_less_comparison_tag> reverse_uint_iterator;
typedef reverse_integer_iterator<long,         integer_iterator_less_comparison_tag> reverse_long_iterator;
typedef reverse_integer_iterator<unsigned long,integer_iterator_less_comparison_tag> reverse_ulong_iterator;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
typedef reverse_integer_iterator<long long, integer_iterator_less_comparison_tag> reverse_long_long_iterator;
typedef reverse_integer_iterator<unsigned long long, integer_iterator_less_comparison_tag> reverse_ulong_long_iterator;
#endif

}
}

#endif