#ifndef _FALCON_HELPER_ITERATOR_FUNCTION_HAS_MEMBER_FUNCTION_HPP
#define _FALCON_HELPER_ITERATOR_FUNCTION_HAS_MEMBER_FUNCTION_HPP

#include <falcon/sfinae/has_member.hpp>

namespace falcon {
namespace helper {

	FALCON_CLASS_HAS_MEMBER_FUNCTION(begin);
	FALCON_CLASS_HAS_MEMBER_FUNCTION(end);

	/**
	 * \brief check if begin() and end() are in _T
	 */
	template <typename _T>
	struct has_iterator_function_member
	{
		static const bool value = FALCON_HAS_MEMBER_FUNCTION_NAME(begin)<_T>::value && FALCON_HAS_MEMBER_FUNCTION_NAME(end)<_T>::value;
	};

	FALCON_CLASS_HAS_MEMBER_FUNCTION(rbegin);
	FALCON_CLASS_HAS_MEMBER_FUNCTION(rend);

	/**
	 * \brief check if rbegin() and rend() are in _T
	 */
	template <typename _T>
	struct has_reverse_iterator_function_member
	{
		static const bool value = FALCON_HAS_MEMBER_FUNCTION_NAME(rbegin)<_T>::value && FALCON_HAS_MEMBER_FUNCTION_NAME(rend)<_T>::value;
	};

}
}

#endif