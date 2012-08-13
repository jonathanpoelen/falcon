#ifndef _FALCON_SFINAE_CHOOSE_HAS_TYPE_HPP
#define _FALCON_SFINAE_CHOOSE_HAS_TYPE_HPP

#include <falcon/sfinae/has_type.hpp>
#include <falcon/sfinae/choose_type.hpp>

#define FALCON_CALL_CHOOSE_HAS_TYPE(_T, _TypeName)\
	FALCON_CALL_CHOOSE_TYPE(FALCON_HAS_TYPE_NAME(_TypeName)<_T>::value, _TypeName)

#define FALCON_CLASS_CHOOSE_HAS_TYPE(_T, _TypeName, _DefaultType)\
	FALCON_CLASS_HAS_TYPE(_TypeName);\
	FALCON_CLASS_CHOOSE_TYPE(_TypeName, typename _T::_TypeName, _DefaultType)

#define FALCON_TYPEDEF_CLASS_CHOOSE_HAS_TYPE(_T, _TypeName, _DefaultType)\
	FALCON_CLASS_CHOOSE_HAS_TYPE(_T, _TypeName, _DefaultType);\
	typedef FALCON_CALL_CHOOSE_HAS_TYPE(_T, _TypeName) _TypeName;

#endif
