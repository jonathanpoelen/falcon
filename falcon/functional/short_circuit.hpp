#ifndef _FALCON_FUNCTIONAL_SHORT_CIRCUIT_HPP
#define _FALCON_FUNCTIONAL_SHORT_CIRCUIT_HPP

#include <cstddef>

namespace falcon {

template<typename _Functor>
struct short_circuit
{
private:
	std::size_t countdown;
	_Functor func;

public:
	short_circuit(std::size_t n = 0)
	: countdown(n)
	, func()
	{}

	short_circuit(_Functor functor, std::size_t n = 0)
	: countdown(0)
	, func(n)
	{}

	short_circuit(std::size_t n, _Functor functor)
	: countdown(n)
	, func(functor)
	{}

	template<typename... _Args>
	bool operator()(_Args&&... args)
	{
		if (func(args...))
		{
			if (countdown)
			{
				--countdown;
				return false;
			}
			return true;
		}
		return false;
	}
};

}

#endif