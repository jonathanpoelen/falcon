#ifndef _FALCON_HELPER_ITERATOR_FUNCTION_IS_CALL_POSSIBLE_HPP
#define _FALCON_HELPER_ITERATOR_FUNCTION_IS_CALL_POSSIBLE_HPP

#include <falcon/sfinae/function_is_call_possible.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {
namespace helper {

	FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(begin);
	FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(end);

	/**
	 * \brief check if falcon::begin() and falcon::end() are callable with type _T
	 */
	template <typename _T>
	struct iterator_function_is_call_possible
	{
		static const bool value = FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(begin)<_T>::value && FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(end)<_T>::value;
	};

	FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(rbegin);
	FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(rend);

	/**
	 * \brief check if falcon::rbegin() and falcon::rend() are callable with type _T
	 */
	template <typename _T>
	struct reverse_iterator_function_is_call_possible
	{
		static const bool value = FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(rbegin)<_T>::value && FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(rend)<_T>::value;
	};

}
}


#endif