#ifndef _FALCON_SFINAE_CHOOSE_HAS_MEMBER_HPP
#define _FALCON_SFINAE_CHOOSE_HAS_MEMBER_HPP

#include <falcon/sfinae/has_member.hpp>
#include <falcon/sfinae/choose_type.hpp>

#define FALCON_CALL_CHOOSE_HAS_MEMBER(_T, _FuncName)\
	FALCON_CALL_CHOOSE_TYPE(FALCON_HAS_MEMBER_NAME(_FuncName)<_T>::value, _FuncName)

#define FALCON_CLASS_CHOOSE_HAS_MEMBER(_FuncName, _TypeTrue, _TypeFalse)\
	FALCON_CLASS_HAS_MEMBER(_FuncName);\
	FALCON_CLASS_CHOOSE_TYPE(_FuncName, _TypeTrue, _TypeFalse)

#define FALCON_MEMBERDEF_CLASS_CHOOSE_HAS_MEMBER(_T, _FuncName, _TypeTrue, _TypeFalse)\
	FALCON_CLASS_CHOOSE_HAS_MEMBER(_T, _FuncName, _TypeTrue, _TypeFalse);\
	typedef FALCON_CALL_CHOOSE_HAS_MEMBER(_T, _FuncName) _FuncName

#endif
