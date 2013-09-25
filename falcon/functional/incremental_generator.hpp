#ifndef FALCON_FUNCTIONAL_INCREMENTAL_GENERATOR_HPP
#define FALCON_FUNCTIONAL_INCREMENTAL_GENERATOR_HPP

#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>

namespace falcon {
/**
 * std::bind(falcon::post_increment<T>, val)
 */
template<typename T>
struct incremental_generator
{
private:
	T value;

public:
	typedef T result_type;

public:
	incremental_generator()
	: value()
	{}

	incremental_generator(T CPP_RVALUE_OR_CONST_REFERENCE begin)
    : value(FALCON_FORWARD(T, begin))
	{}

	T operator() ()
	{
		return value++;
	}
};

/**
 * std::bind(falcon::increment<T>, val)
 */
template<typename T>
struct preincremental_generator
{
private:
	T value;

public:
	typedef T result_type;

public:
	preincremental_generator()
	: value()
	{}

	preincremental_generator(T CPP_RVALUE_OR_CONST_REFERENCE begin)
    : value(FALCON_FORWARD(T, begin))
	{}

	T operator() ()
	{
		return ++value;
	}
};
}

#endif
