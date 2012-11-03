#ifndef _FALCON_SFINAE_HEADER_CHOOSE_TYPE_HPP
#define _FALCON_SFINAE_HEADER_CHOOSE_TYPE_HPP

#include <falcon/type_traits/if.hpp>

#define FALCON_CREATE_CHOOSE_TYPE(_Name, _TypeTrue, _TypeFalse)\
	template<bool b, typename _Falcon_Unused_T = void>\
	struct _Name\
	: falcon::if_<b, _TypeTrue, _TypeFalse>\
	{}

#define FALCON_CHOOSE_TYPE_NAME(_TypeName) _TypeName##_choose_type

#define FALCON_CLASS_CHOOSE_TYPE(_Name, _TypeTrue, _TypeFalse)\
	FALCON_CREATE_CHOOSE_TYPE(FALCON_CHOOSE_TYPE_NAME(_Name), _TypeTrue, _TypeFalse)

#define FALCON_CALL_CHOOSE_TYPE(_TypeCondition, _TypeName)\
	typename FALCON_CHOOSE_TYPE_NAME(_TypeName)<_TypeCondition>::type

#endif
