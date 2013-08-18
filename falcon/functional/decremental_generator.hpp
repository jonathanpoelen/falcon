#ifndef _FALCON_FUNCTIONAL_DECREMENTAL_GENERATOR_HPP
#define _FALCON_FUNCTIONAL_DECREMENTAL_GENERATOR_HPP

#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>

namespace falcon {
/**
 * std::bind(falcon::post_decrement<T>, val)
 */
template<typename T>
struct decremental_generator
{
private:
	T value;

public:
	typedef T result_type;

public:
	decremental_generator()
	: value()
	{}

	decremental_generator(T CPP_RVALUE_OR_CONST_REFERENCE begin)
    : value(FALCON_FORWARD(T, begin))
	{}

	T operator() ()
	{
		return value--;
	}
};

/**
 * std::bind(falcon::decrement<T>, val)
 */
template<typename T>
struct predecremental_generator
{
private:
	T value;

public:
	typedef T result_type;

public:
	predecremental_generator()
	: value()
	{}

	predecremental_generator(T CPP_RVALUE_OR_CONST_REFERENCE begin)
    : value(FALCON_FORWARD(T, begin))
	{}

	T operator() ()
	{
		return --value;
	}
};
}

#endif
