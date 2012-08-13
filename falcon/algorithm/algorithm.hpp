#ifndef FALCON_ALGORITHM_ALGORITHM_HPP
#define FALCON_ALGORITHM_ALGORITHM_HPP

#include <algorithm>
#include <falcon/sfinae/member_is_call_possible.hpp>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/container/container_wrapper.hpp>

#define __FALCON_ALGORITHM_0_PARTIAL_TEMPLATE
#define __FALCON_ALGORITHM_1_PARTIAL_TEMPLATE , typename _T1
#define __FALCON_ALGORITHM_2_PARTIAL_TEMPLATE , typename _T1, typename _T2
#define __FALCON_ALGORITHM_3_PARTIAL_TEMPLATE , typename _T1, typename _T2, typename _T3
#define __FALCON_ALGORITHM_4_PARTIAL_TEMPLATE , typename _T1, typename _T2, typename _T3, typename _T4

#define __FALCON_ALGORITHM_0_TYPE
#define __FALCON_ALGORITHM_1_TYPE , _T1
#define __FALCON_ALGORITHM_2_TYPE , _T1, _T2
#define __FALCON_ALGORITHM_3_TYPE , _T1, _T2, _T3
#define __FALCON_ALGORITHM_4_TYPE , _T1, _T2, _T3, _T4

#define __FALCON_ALGORITHM_PARTIAL_TEMPLATE(_N)  __FALCON_ALGORITHM_##_N##_PARTIAL_TEMPLATE
#define __FALCON_ALGORITHM_TEMPLATE(_N) template<typename Container __FALCON_ALGORITHM_PARTIAL_TEMPLATE(_N)>

#define __FALCON_ALGORITHM_0_ARG
#define __FALCON_ALGORITHM_1_ARG , _T1 v1
#define __FALCON_ALGORITHM_2_ARG , _T1 v1, _T2 v2
#define __FALCON_ALGORITHM_2v_ARG , _T1 v1, _T1 v2
#define __FALCON_ALGORITHM_2v1_ARG , _T1 v1, _T1 v2, _T2 v3
#define __FALCON_ALGORITHM_2v2_ARG , _T1 v1, _T1 v2, _T2 v3, _T3 v4
#define __FALCON_ALGORITHM_3_ARG , _T1 v1, _T2 v2, _T3 v3
#define __FALCON_ALGORITHM_4_ARG , _T1 v1, _T2 v2, _T3 v3, _T4 v4
#define __FALCON_ALGORITHM_T_ARG , const _T1& v1
#define __FALCON_ALGORITHM_T1_ARG , const _T1& v1, _T2& v2
#define __FALCON_ALGORITHM_1T_ARG , _T1 v1, const _T2& v2
#define __FALCON_ALGORITHM_2T_ARG , _T1 v1, _T2 v2, const _T3& v3
#define __FALCON_ALGORITHM_1T1_ARG , _T1 v1, const _T2& v2, _T3 v3
#define __FALCON_ALGORITHM_T2_ARG , const _T1& v1, const _T1& v2
#define __FALCON_ALGORITHM_1T2_ARG , _T1 v1, const _T2& v2, const _T2& v3
#define __FALCON_ALGORITHM_REF_ARG , _T1& v1
#define __FALCON_ALGORITHM_REF1_ARG , _T1& v1, _T2 v2
#define __FALCON_ALGORITHM_REF2_ARG , _T1& v1, _T2 v2, _T3 v3
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define __FALCON_ALGORITHM_RVALUE_ARG , _T1&& v1
#else
# define __FALCON_ALGORITHM_RVALUE_ARG , const _T1& v1
#endif

#define __FALCON_ALGORITHM_0_VAR
#define __FALCON_ALGORITHM_1_VAR , v1
#define __FALCON_ALGORITHM_2_VAR , v1, v2
#define __FALCON_ALGORITHM_3_VAR , v1, v2, v3
#define __FALCON_ALGORITHM_4_VAR , v1, v2, v3, v4

#define __FALCON_ALGORITHM_0_VAR_CONTAINER
#define __FALCON_ALGORITHM_1_VAR_CONTAINER v1
#define __FALCON_ALGORITHM_2_VAR_CONTAINER v1, v2
#define __FALCON_ALGORITHM_3_VAR_CONTAINER v1, v2, v3
#define __FALCON_ALGORITHM_4_VAR_CONTAINER v1, v2, v3, v4

#define __FALCON_ALGORITHM_DELEGATE(_Name, TEMPLATE, ARG, VAR)\
	namespace __delegate {\
		template<bool, typename Container __FALCON_ALGORITHM_##TEMPLATE##_PARTIAL_TEMPLATE>\
		struct _Name##TEMPLATE##ARG##VAR {\
			inline static CPP0X_DELEGATE_FUNCTION(exec(Container& container __FALCON_ALGORITHM_##ARG##_ARG), std::_Name(begin(container), end(container) __FALCON_ALGORITHM_##VAR##_VAR))\
		};\
		\
		__FALCON_ALGORITHM_TEMPLATE(TEMPLATE)\
		struct _Name##TEMPLATE##ARG##VAR <true, Container __FALCON_ALGORITHM_##TEMPLATE##_TYPE> {\
			inline static CPP0X_DELEGATE_FUNCTION(exec(Container& container __FALCON_ALGORITHM_##ARG##_ARG), container._Name(__FALCON_ALGORITHM_##VAR##_VAR_CONTAINER))\
		};\
	}

#define __FALCON_ALGORITHM_DETAIL_CLASS_MEMBER_FUNCTION_IS_CALL_POSSIBLE(_Name)\
	namespace detail {\
		FALCON_CLASS_HAS_MEMBER_FUNCTION(_Name);\
		FALCON_CLASS_MEMBER_FUNCTION_IS_CALL_POSSIBLE(_Name);\
	}

#define __FALCON_ALGORITHM_FUNC(_Name, TEMPLATE, ARG, VAR)\
	__FALCON_ALGORITHM_TEMPLATE(TEMPLATE)\
	CPP0X_DELEGATE_FUNCTION(_Name(Container& container __FALCON_ALGORITHM_##ARG##_ARG), __delegate::_Name##TEMPLATE##ARG##VAR <detail::FALCON_MEMBER_FUNCTION_IS_CALL_POSSIBLE_NAME(_Name)<Container __FALCON_ALGORITHM_##TEMPLATE##_TYPE>::value, Container __FALCON_ALGORITHM_##TEMPLATE##_TYPE>::exec(container __FALCON_ALGORITHM_##VAR##_VAR))\
	\
	template<typename _InitializerT __FALCON_ALGORITHM_PARTIAL_TEMPLATE(TEMPLATE)>\
	CPP0X_DELEGATE_FUNCTION(_Name(std::initializer_list<_InitializerT> initializer __FALCON_ALGORITHM_##ARG##_ARG), std::_Name(initializer.begin(), initializer.end() __FALCON_ALGORITHM_##VAR##_VAR))\
	\
	template<typename _Container, typename _Traits __FALCON_ALGORITHM_PARTIAL_TEMPLATE(TEMPLATE)>\
	CPP0X_DELEGATE_FUNCTION(_Name(container_wrapper<_Container, _Traits> cont __FALCON_ALGORITHM_##ARG##_ARG), std::_Name(cont.begin(), cont.end() __FALCON_ALGORITHM_##VAR##_VAR))

#define __FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(_Name, TEMPLATE, ARG, VAR)\
	__FALCON_ALGORITHM_DELEGATE(_Name, TEMPLATE, ARG, VAR)\
	__FALCON_ALGORITHM_FUNC(_Name, TEMPLATE, ARG, VAR)

#define __FALCON_ALGORITHM(_Name, TEMPLATE, ARG, VAR)\
	__FALCON_ALGORITHM_DETAIL_CLASS_MEMBER_FUNCTION_IS_CALL_POSSIBLE(_Name)\
	__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(_Name, TEMPLATE, ARG, VAR)

#define __FALCON_ALGORITHM2(_Name, TEMPLATE, ARG, VAR)\
	__FALCON_ALGORITHM_TEMPLATE(TEMPLATE)\
	inline CPP0X_DELEGATE_FUNCTION(_Name(Container& container __FALCON_ALGORITHM_##ARG##_ARG), std::_Name(container.begin(), container.end(), v1.begin(), v1.end() __FALCON_ALGORITHM_##VAR##_VAR))

///TODO modifier __FALCON_ALGORITHM2 ou faire un __FALCON_ALGORITHM3 pour transform (http://en.cppreference.com/w/cpp/algorithm/transform)

namespace falcon {

/**
 * \brief Les classes de ce namespace permettent d'utiliser les fonctions présentent dans <algorithm> en ne donnant que le conteneur. De ceux fait, begin() et end() sont automatiquement utilisées. Si le conteneur possède en méthode le nom de l'algorithme, alors cette dernière sera utilisée.
 */
namespace algorithm {

__FALCON_ALGORITHM(all_of, 1, 1, 1)
__FALCON_ALGORITHM(any_of, 1, 1, 1)
__FALCON_ALGORITHM(none_of, 1, 1, 1)

__FALCON_ALGORITHM(for_each, 1, 1, 1)

__FALCON_ALGORITHM(count, 1, T, 1)
__FALCON_ALGORITHM(count_if, 1, 1, 1)

__FALCON_ALGORITHM(mismatch, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(mismatch, 2, 2, 2)

__FALCON_ALGORITHM(equal, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(equal, 2, 2, 2)

__FALCON_ALGORITHM(find, 1, T, 1)
__FALCON_ALGORITHM(find_if, 1, 1, 1)
__FALCON_ALGORITHM(find_if_not, 1, 1, 1)

__FALCON_ALGORITHM(find_end, 1, 2v, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(find_end, 2, 2v1, 3)
__FALCON_ALGORITHM2(find_end, 1, REF, 0)
__FALCON_ALGORITHM2(find_end, 2, REF1, 1)

__FALCON_ALGORITHM(find_first_of, 1, 2v, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(find_first_of, 2, 2v1, 3)

__FALCON_ALGORITHM(adjacent_find, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(adjacent_find, 1, 1, 1)

__FALCON_ALGORITHM(search, 1, 2v, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(search, 2, 2v1, 3)
__FALCON_ALGORITHM2(search, 1, REF, 0)
__FALCON_ALGORITHM2(search, 2, REF1, 1)

__FALCON_ALGORITHM(search_n, 2, 1T, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(search_n, 3, 1T1, 3)

__FALCON_ALGORITHM(copy, 1, T, 1)
__FALCON_ALGORITHM(copy_if, 1, 1, 1)

__FALCON_ALGORITHM(copy_backward, 1, 1, 1)

__FALCON_ALGORITHM(move, 1, 1, 1)

__FALCON_ALGORITHM(move_backward, 1, 1, 1)

__FALCON_ALGORITHM(fill, 1, T, 1)

__FALCON_ALGORITHM(transform, 2, 2, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(transform, 3, 3, 3)

__FALCON_ALGORITHM(generate, 1, 1, 1)

__FALCON_ALGORITHM(remove, 1, T, 1)
__FALCON_ALGORITHM(remove_if, 1, 1, 1)

__FALCON_ALGORITHM(remove_copy, 2, 1T, 2)
__FALCON_ALGORITHM(remove_copy_if, 2, 2, 2)

__FALCON_ALGORITHM(replace, 1, T2, 2)
__FALCON_ALGORITHM(replace_if, 2, 1T, 2)

__FALCON_ALGORITHM(replace_copy, 2, 1T2, 3)
__FALCON_ALGORITHM(replace_copy_if, 3, 2T, 3)

__FALCON_ALGORITHM(swap_ranges, 1, 1, 1)

__FALCON_ALGORITHM(reverse, 0, 0, 0)

__FALCON_ALGORITHM(reverse_copy, 1, 1, 1)

__FALCON_ALGORITHM(rotate, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(rotate, 2, 2, 2)

__FALCON_ALGORITHM(random_shuffle, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(random_shuffle, 1, REF, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(random_shuffle, 1, RVALUE, 1)
__FALCON_ALGORITHM(shuffle, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(shuffle, 1, REF, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(shuffle, 1, RVALUE, 1)

__FALCON_ALGORITHM(unique, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(unique, 1, 1, 1)

__FALCON_ALGORITHM(unique_copy, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(unique_copy, 2, 2, 2)

__FALCON_ALGORITHM(is_partitioned, 1, 1, 1)

__FALCON_ALGORITHM(partition, 1, 1, 1)

__FALCON_ALGORITHM(stable_partition, 1, 1, 1)

__FALCON_ALGORITHM(partition_point, 1, 1, 1)

__FALCON_ALGORITHM(partition_copy, 3, 3, 3)

__FALCON_ALGORITHM(is_sorted, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(is_sorted, 1, 1, 1)

__FALCON_ALGORITHM(is_sorted_until, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(is_sorted_until, 1, 1, 1)

__FALCON_ALGORITHM(sort, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(sort, 1, 1, 1)

__FALCON_ALGORITHM(partial_sort_copy, 1, 2v, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(partial_sort_copy, 2, 2v1, 3)
__FALCON_ALGORITHM2(partial_sort_copy, 1, REF, 0)
__FALCON_ALGORITHM2(partial_sort_copy, 2, REF1, 1)

__FALCON_ALGORITHM(stable_sort, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(stable_sort, 1, 1, 1)

__FALCON_ALGORITHM(nth_element, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(nth_element, 2, 2, 2)

__FALCON_ALGORITHM(lower_bound, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(lower_bound, 1, 1, 1)

__FALCON_ALGORITHM(upper_bound, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(upper_bound, 1, 1, 1)

__FALCON_ALGORITHM(binary_search, 1, T, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(binary_search, 2, T1, 2)

__FALCON_ALGORITHM(equal_range, 1, T, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(equal_range, 2, T1, 2)

__FALCON_ALGORITHM(merge, 2, 2v1, 3)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(merge, 3, 2v2, 4)
__FALCON_ALGORITHM2(merge, 2, REF1, 1)
__FALCON_ALGORITHM2(merge, 3, REF2, 2)

__FALCON_ALGORITHM(inplace_merge, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(inplace_merge, 2, 2, 2)

__FALCON_ALGORITHM(includes, 1, 2v, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(includes, 2, 2v1, 3)
__FALCON_ALGORITHM2(includes, 1, REF, 0)
__FALCON_ALGORITHM2(includes, 2, REF1, 1)

__FALCON_ALGORITHM(set_difference, 2, 2v1, 3)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(set_difference, 3, 2v2, 4)
__FALCON_ALGORITHM2(set_difference, 2, REF1, 1)
__FALCON_ALGORITHM2(set_difference, 3, REF2, 2)

__FALCON_ALGORITHM(set_intersection, 2, 2v1, 3)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(set_intersection, 3, 2v2, 4)
__FALCON_ALGORITHM2(set_intersection, 2, REF1, 1)
__FALCON_ALGORITHM2(set_intersection, 3, REF2, 2)

__FALCON_ALGORITHM(set_symmetric_difference, 2, 2v1, 3)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(set_symmetric_difference, 3, 2v2, 4)
__FALCON_ALGORITHM2(set_symmetric_difference, 2, REF1, 1)
__FALCON_ALGORITHM2(set_symmetric_difference, 3, REF2, 2)

__FALCON_ALGORITHM(set_union, 2, 2v1, 3)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(set_union, 3, 2v2, 4)
__FALCON_ALGORITHM2(set_union, 2, REF1, 1)
__FALCON_ALGORITHM2(set_union, 3, REF2, 2)

__FALCON_ALGORITHM(is_heap, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(is_heap, 1, 1, 1)

__FALCON_ALGORITHM(is_heap_until, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(is_heap_until, 1, 1, 1)

__FALCON_ALGORITHM(make_heap, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(make_heap, 1, 1, 1)

__FALCON_ALGORITHM(push_heap, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(push_heap, 1, 1, 1)

__FALCON_ALGORITHM(pop_heap, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(pop_heap, 1, 1, 1)

__FALCON_ALGORITHM(sort_heap, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(sort_heap, 1, 1, 1)

__FALCON_ALGORITHM(max_element, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(max_element, 1, 1, 1)

__FALCON_ALGORITHM(min_element, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(min_element, 1, 1, 1)

__FALCON_ALGORITHM(minmax_element, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(minmax_element, 1, 1, 1)

__FALCON_ALGORITHM(lexicographical_compare, 1, 2v, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(lexicographical_compare, 2, 2v1, 3)
__FALCON_ALGORITHM2(lexicographical_compare, 1, REF, 0)
__FALCON_ALGORITHM2(lexicographical_compare, 2, REF1, 1)

/*__FALCON_ALGORITHM(is_permutation, 1, 1, 1)
__FALCON_ALGORITHM(is_permutation, 2, 2, 2)*/

__FALCON_ALGORITHM(next_permutation, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(next_permutation, 1, 1, 1)

__FALCON_ALGORITHM(prev_permutation, 0, 0, 0)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(prev_permutation, 1, 1, 1)

__FALCON_ALGORITHM(iota, 1, 1, 1)

__FALCON_ALGORITHM(accumulate, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(accumulate, 2, 2, 2)

__FALCON_ALGORITHM(inner_product, 2, 2, 2)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(inner_product, 4, 4, 4)

__FALCON_ALGORITHM(adjacent_difference, 1, 1, 1)
__FALCON_ALGORITHM_NOT_CLASS_IS_CALL_POSSIBLE(adjacent_difference, 2, 2, 2)

}

using namespace algorithm;

}

#endif
