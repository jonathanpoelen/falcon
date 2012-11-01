#ifndef FALCON_BIT_BIT_REFERENCE_HPP
#define FALCON_BIT_BIT_REFERENCE_HPP

#include <type_traits>

namespace falcon {

template<typename _T>
struct basic_bit_reference
{
	typedef _T bit_type;
	typedef typename std::remove_const<bit_type>::type mask_type;

private:
	bit_type * _p;
	mask_type _mask;

public:
	basic_bit_reference(bit_type * x, bit_type y)
	: _p(x), _mask(y)
	{}

	basic_bit_reference()
	: _p(0), _mask(0)
	{}

	operator bool() const
	{ return !!(*_p & _mask); }

	basic_bit_reference& operator=(bool x)
	{
		if (x)
			*_p = static_cast<bit_type>(*_p | _mask);
		else
			*_p = static_cast<bit_type>(*_p & ~_mask);
		return *this;
	}

	basic_bit_reference& operator=(const basic_bit_reference& x)
	{ return *this = bool(x); }

	bool operator==(const basic_bit_reference& x) const
	{ return bool(*this) == bool(x); }

	bool operator<(const basic_bit_reference& x) const
	{ return !bool(*this) && bool(x); }

	void flip()
	{ *_p ^= _mask; }

	mask_type mask() const
	{ return _mask; }

	void mask(mask_type y)
	{ _mask = y; }

	bit_type * p() const
	{ return _p; }

	void p(bit_type * x)
	{ _p = x; }
};

typedef basic_bit_reference<unsigned long> bit_reference;

}

#endif