#ifndef _FALCON_PREPROCESSOR_INCREMENT
#define _FALCON_PREPROCESSOR_INCREMENT

#define __FALCON_MEMBER_INCREMENT(_Op, _ResulType, ...)\
	_ResulType& operator _Op()\
	{\
		__VA_ARGS__;\
		return *this;\
	}\
	_ResulType operator _Op(int)\
	{\
		_ResulType tmp(*this);\
		operator _Op();\
		return tmp;\
	}

#define FALCON_MEMBER_INCREMENT(_ResulType, ...)\
	__FALCON_MEMBER_INCREMENT(++, _ResulType, __VA_ARGS__)

#define FALCON_MEMBER_DECREMENT(_ResulType, ...)\
	__FALCON_MEMBER_INCREMENT(--, _ResulType, __VA_ARGS__)


#define __FALCON_MEMBER_EQUAL_INCREMENT(_Op, _ResulType, _Value, ...)\
	_ResulType& operator _Op(_Value)\
	{\
		__VA_ARGS__;\
		return *this;\
	}\
	_ResulType operator _Op(_Value, int)\
	{\
		_ResulType tmp(*this);\
		__VA_ARGS__;\
		return tmp;\
	}

#define FALCON_MEMBER_EQUAL_INCREMENT(_ResulType, _Value, ...)\
	__FALCON_MEMBER_EQUAL_INCREMENT(+=, _ResulType, _Value, __VA_ARGS__)

#define FALCON_MEMBER_EQUAL_DECREMENT(_ResulType, _Value, ...)\
	__FALCON_MEMBER_EQUAL_INCREMENT(-=, _ResulType, _Value, __VA_ARGS__)

#endif