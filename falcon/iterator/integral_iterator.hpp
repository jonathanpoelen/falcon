#ifndef FALCON_ITERATOR_INTEGRAL_ITERATOR_HPP
#define FALCON_ITERATOR_INTEGRAL_ITERATOR_HPP

#include <falcon/iterator/fake_iterator.hpp>

namespace falcon {
namespace iterator {

typedef fake_iterator<int,          fake_iterator_less_comparison_tag> int_iterator;
typedef fake_iterator<unsigned int, fake_iterator_less_comparison_tag> uint_iterator;
typedef fake_iterator<long,         fake_iterator_less_comparison_tag> long_iterator;
typedef fake_iterator<unsigned long,fake_iterator_less_comparison_tag> ulong_iterator;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
typedef fake_iterator<long long, fake_iterator_less_comparison_tag> long_long_iterator;
typedef fake_iterator<unsigned long long, fake_iterator_less_comparison_tag> ulong_long_iterator;
#endif

typedef reverse_fake_iterator<int,          fake_iterator_less_comparison_tag> reverse_int_iterator;
typedef reverse_fake_iterator<unsigned int, fake_iterator_less_comparison_tag> reverse_uint_iterator;
typedef reverse_fake_iterator<long,         fake_iterator_less_comparison_tag> reverse_long_iterator;
typedef reverse_fake_iterator<unsigned long,fake_iterator_less_comparison_tag> reverse_ulong_iterator;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
typedef reverse_fake_iterator<long long, fake_iterator_less_comparison_tag> reverse_long_long_iterator;
typedef reverse_fake_iterator<unsigned long long, fake_iterator_less_comparison_tag> reverse_ulong_long_iterator;
#endif

}
}

#endif