#ifndef _FALCON_FUNCTIONAL_INCREMENTAL_GENERATOR_HPP
#define _FALCON_FUNCTIONAL_INCREMENTAL_GENERATOR_HPP

namespace falcon {
/**
* std::bind(falcon::post_increment<_T>, val)
*/
template<typename _T>
struct incremental_generator
{
private:
	_T _value;

public:
	typedef _T result_type;

public:
	incremental_generator()
	: _value()
	{}

	incremental_generator(const _T& begin)
	: _value(begin)
	{}

	_T operator() ()
	{
		return _value++;
	}
};

/**
* std::bind(falcon::increment<_T>, val)
*/
template<typename _T>
struct preincremental_generator
{
private:
	_T _value;

public:
	typedef _T result_type;

public:
	preincremental_generator()
	: _value()
	{}

	preincremental_generator(const _T& begin)
	: _value(begin)
	{}

	_T operator() ()
	{
		return ++_value;
	}
};
}

#endif
