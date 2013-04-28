#ifndef _FALCON_COUNTDOWN_HPP
#define _FALCON_COUNTDOWN_HPP

#include <limits>
#include <boost/config/select_compiler_config.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _T>
struct basic_countdown
{
	typedef _T value_type;

private:
	value_type _value;

public:
	CPP_CONSTEXPR basic_countdown()
	: _value(std::numeric_limits<_T>::max())
	{}

	CPP_CONSTEXPR basic_countdown(const _T& start)
	: _value(start)
	{}

#if __cplusplus >= 201103L
	operator const _T&() const
	{ return _value; }
#endif

	void reset(const _T& start)
	{ _value = start; }

	CPP_CONSTEXPR _T max_count() const
	{ return std::numeric_limits<_T>::max(); }

	CPP_CONSTEXPR _T min_count() const
	{ return std::numeric_limits<_T>::min(); }

	const _T& count() const
	{ return _value; }

	bool next()
	{ return _value-- != min_count(); }
};

typedef basic_countdown<int> icountdown;
typedef basic_countdown<unsigned int> ucountdown;
typedef basic_countdown<long> lcountdown;
typedef basic_countdown<unsigned long> ulcountdown;
#ifdef BOOST_HAS_LONG_LONG
typedef basic_countdown<long long> llcountdown;
typedef basic_countdown<unsigned long long> ullcountdown;
#endif

}

#endif