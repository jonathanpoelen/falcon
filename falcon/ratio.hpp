#ifndef _FALCON_RATIO_HPP
#define _FALCON_RATIO_HPP

#include <ratio>

namespace falcon{
	typedef std::atto  atto;
	typedef std::femto femto;
	typedef std::pico  pico;
	typedef std::nano  nano;
	typedef std::micro micro;
	typedef std::milli milli;
	typedef std::centi centi;
	typedef std::deci  deci;
	typedef std::deca  deca;
	typedef std::hecto hecto;
	typedef std::kilo  kilo;
	typedef std::mega  mega;
	typedef std::giga  giga;
	typedef std::tera  tera;
	typedef std::peta  peta;
	typedef std::exa   exa;

	//integer is to large
	//typedef std::ratio<1, 1000000000000000000000000l> yocto;
	//typedef std::ratio<1,    1000000000000000000000l> zepta;
	//typedef std::ratio<1000000000000000000000,    1> zetta;
	//typedef std::ratio<1000000000000000000000000, 1> yotta;


	typedef std::ratio<1024,                1> kibi;
	typedef std::ratio<1048576,             1> mebi;
	typedef std::ratio<1073741824,          1> gibi;
	typedef std::ratio<1099511627776,       1> tibi;
	typedef std::ratio<1125899906842624,    1> pibi;
	typedef std::ratio<1152921504606846976, 1> exbi;
}

#endif