#ifndef FALCON_BIT_BIT_REFERENCE_HPP
#define FALCON_BIT_BIT_REFERENCE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

template<class T>
struct bit_reference
{
	typedef T bit_type;

private:
	bit_type * _p;
	bit_type _mask;

public:
  CPP_CONSTEXPR bit_reference(bit_type * x, bit_type m) CPP_NOEXCEPT
	: _p(x), _mask(m)
	{}

  CPP_CONSTEXPR bit_reference() CPP_NOEXCEPT
	: _p(0), _mask(0)
	{}

  operator bool() const CPP_NOEXCEPT
	{ return !!(*_p & _mask); }

  bit_reference& operator=(bool x) CPP_NOEXCEPT
	{
    *_p = static_cast<bit_type>(x ? *_p | _mask : *_p & ~_mask);
		return *this;
	}

  bit_reference& operator=(const bit_reference& x) CPP_NOEXCEPT
	{ return *this = bool(x); }

  CPP_CONSTEXPR bool operator==(const bit_reference& x) const CPP_NOEXCEPT
	{ return bool(*this) == bool(x); }

  CPP_CONSTEXPR bool operator<(const bit_reference& x) const CPP_NOEXCEPT
	{ return !bool(*this) && bool(x); }

  void flip() CPP_NOEXCEPT
	{ *_p ^= _mask; }

  bit_type mask() const CPP_NOEXCEPT
	{ return _mask; }

  void mask(bit_type y) CPP_NOEXCEPT
	{ _mask = y; }

  bit_type * p() const CPP_NOEXCEPT
	{ return _p; }

	void p(bit_type * x) CPP_NOEXCEPT
	{ _p = x; }
};

template<class T>
void swap(bit_reference<T> x, bit_reference<T> y) CPP_NOEXCEPT
{
  bool tmp = x;
  x = y;
  y = tmp;
}

template<class T>
void swap(bit_reference<T> x, bool& y) CPP_NOEXCEPT
{
  bool tmp = x;
  x = y;
  y = tmp;
}

template<class T>
void swap(bool& x, bit_reference<T> y) CPP_NOEXCEPT
{
  bool tmp = x;
  x = y;
  y = tmp;
}

typedef bit_reference<unsigned> u_bit_reference;
typedef bit_reference<unsigned long> ul_bit_reference;
#if __cplusplus >= 201103L
typedef bit_reference<unsigned long long> ull_bit_reference;
#endif

}

#endif
