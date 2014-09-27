#ifndef FALCON_ITERATOR_HPP
#define FALCON_ITERATOR_HPP

#include <falcon/iterator/bit_iterator.hpp>
#include <falcon/iterator/counting_iterator.hpp>
#include <falcon/iterator/delegate_comparison_iterator.hpp>
#include <falcon/iterator/integer_iterator.hpp>
#include <falcon/iterator/get_accessor_iterator.hpp>
#include <falcon/iterator/indirect_iterator.hpp>
#include <falcon/iterator/infinite_iterator.hpp>
#include <falcon/iterator/integral_iterator.hpp>
#include <falcon/iterator/iterator_category.hpp>
#include <falcon/iterator/iterator_iterator.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include <falcon/iterator/opposite_direction_iterator.hpp>
#include <falcon/iterator/output_iterator.hpp>
#include <falcon/iterator/pseudo_iterator.hpp>
#include <falcon/iterator/subrange_access_iterator.hpp>
#if __cplusplus >= 201103L
# include <falcon/iterator/recursive_iterator.hpp>
# include <falcon/iterator/synchronize_iterator.hpp>
#endif
#include <falcon/type_traits/is_iterator.hpp>

#endif
