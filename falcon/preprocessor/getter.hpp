#ifndef _FALCON_PREPROCESSOR_GETTER_HPP
#define _FALCON_PREPROCESSOR_GETTER_HPP

#define FALCON_MEMBER_GETTER(type, name, value)\
	type& name() { return (value); }\
	const type& name() const { return (value); }

#define FALCON_MEMBER_GETTER_POINTER(type, name, value)\
	type* name() { return (value); }\
	const type* name() const { return (value); }

#define FALCON_CAST_GETTER(type, value)\
	operator type&() { return (value); }\
	operator const type&() const { return (value); }

#endif