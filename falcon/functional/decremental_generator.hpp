#ifndef _FALCON_FUNCTIONAL_DECREMENTAL_GENERATOR_HPP
#define _FALCON_FUNCTIONAL_DECREMENTAL_GENERATOR_HPP

namespace falcon {
/**
* std::bind(falcon::post_decrement<_T>, val)
*/
template<typename _T>
struct decremental_generator
{
private:
	_T _value;

public:
	typedef _T result_type;

public:
	decremental_generator()
	: _value()
	{}

	decremental_generator(const _T& begin)
	: _value(begin)
	{}

	_T operator() ()
	{
		return _value--;
	}
};

/**
* std::bind(falcon::decrement<_T>, val)
*/
template<typename _T>
struct predecremental_generator
{
private:
	_T _value;

public:
	typedef _T result_type;

public:
	predecremental_generator()
	: _value()
	{}

	predecremental_generator(const _T& begin)
	: _value(begin)
	{}

	_T operator() ()
	{
		return --_value;
	}
};
}

#endif
