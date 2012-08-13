#ifndef _FALCON_SFINAE_HEADER_CHOOSE_TYPE_HPP
#define _FALCON_SFINAE_HEADER_CHOOSE_TYPE_HPP

#define FALCON_HEADER_CHOOSE_TYPE_TRUE(_Name)\
	template<bool, typename _Falcon_Unused_T = void> struct _Name\
 
#define FALCON_HEADER_CHOOSE_TYPE_FALSE(_Name)\
	template<typename _Falcon_Unused_T> struct _Name<false, _Falcon_Unused_T>

#define FALCON_CREATE_CHOOSE_TYPE(_Name, _TypeTrue, _TypeFalse)\
	FALCON_HEADER_CHOOSE_TYPE_TRUE(_Name){\
		typedef _TypeTrue type;\
	};\
	FALCON_HEADER_CHOOSE_TYPE_FALSE(_Name){\
		typedef _TypeFalse type;\
	}

#define FALCON_CHOOSE_TYPE_NAME(_TypeName) _TypeName##_choose_type

#define FALCON_CLASS_CHOOSE_TYPE(_Name, _TypeTrue, _TypeFalse)\
	FALCON_CREATE_CHOOSE_TYPE(FALCON_CHOOSE_TYPE_NAME(_Name), _TypeTrue, _TypeFalse)

#define FALCON_CALL_CHOOSE_TYPE(_TypeCondition, _TypeName)\
	typename FALCON_CHOOSE_TYPE_NAME(_TypeName)<_TypeCondition>::type

#endif
