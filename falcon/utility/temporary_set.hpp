#ifndef FALCON_UTILITY_TEMPORARY_SET_HPP
#define FALCON_UTILITY_TEMPORARY_SET_HPP

#include <falcon/preprocessor/move.hpp>
#include <falcon/c++/reference.hpp>

namespace falcon {

template<typename _T>
class temporary_set
{
	_T& _value;
	_T _old_value;

public:
	temporary_set(_T& old_value, _T CPP_RVALUE_OR_CONST_REFERENCE new_value)
	: _value(old_value)
	, _old_value(FALCON_MOVE(old_value))
	{
		_value = FALCON_FORWARD(_T, new_value);
	}

	~temporary_set()
	{
		_value = FALCON_FORWARD(_T, _old_value);
	}
};

}

#endif