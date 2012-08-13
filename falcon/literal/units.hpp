#ifndef _FALCON_LITERAL_UNITS_HPP
#define _FALCON_LITERAL_UNITS_HPP

#include <falcon/literal/detail/literal_support.hpp>
#include <falcon/ratio.hpp>

namespace falcon {
namespace literal {

namespace units {}
namespace units_symbol {}

#define FALCON_USER_DEFINED_LD_UNITS_LITERAL(suffix, symbol)\
	namespace units {\
		constexpr long double operator "" _##suffix (long double n)\
		{ return n * ::falcon::suffix::num / ::falcon::suffix::den; }\
	}\
	namespace units_symbol {\
		constexpr long double operator "" _##symbol (long double n)\
		{ return ::falcon::literal::units::operator "" _##suffix (n); }\
	}

#define FALCON_USER_DEFINED_ULL_UNITS_LITERAL(suffix, symbol)\
	namespace units {\
		constexpr unsigned long long operator "" _##suffix (unsigned long long n)\
		{ return n * ::falcon::suffix::num / ::falcon::suffix::den; }\
	}\
	namespace units_symbol {\
		constexpr unsigned long long operator "" _##symbol (unsigned long long n)\
		{ return ::falcon::literal::units::operator "" _##suffix (n); }\
	}

#define FALCON_USER_DEFINED_UNITS_LITERAL(suffix, symbol)\
	FALCON_USER_DEFINED_ULL_UNITS_LITERAL(suffix, symbol)\
	FALCON_USER_DEFINED_LD_UNITS_LITERAL(suffix, symbol)

FALCON_USER_DEFINED_LD_UNITS_LITERAL(yocto, y, 1.e-24)
FALCON_USER_DEFINED_LD_UNITS_LITERAL(zepta, z, 1.e-21)
FALCON_USER_DEFINED_UNITS_LITERAL(atto, a)
FALCON_USER_DEFINED_UNITS_LITERAL(femto, f)
FALCON_USER_DEFINED_UNITS_LITERAL(pico, p)
FALCON_USER_DEFINED_UNITS_LITERAL(nano, n)
FALCON_USER_DEFINED_UNITS_LITERAL(micro, u)
FALCON_USER_DEFINED_UNITS_LITERAL(milli, m)
FALCON_USER_DEFINED_UNITS_LITERAL(centi, c)
FALCON_USER_DEFINED_UNITS_LITERAL(deci, d)

FALCON_USER_DEFINED_UNITS_LITERAL(deca, da)
FALCON_USER_DEFINED_UNITS_LITERAL(hecto, h)
FALCON_USER_DEFINED_UNITS_LITERAL(kilo, k)
FALCON_USER_DEFINED_UNITS_LITERAL(mega, M)
FALCON_USER_DEFINED_UNITS_LITERAL(giga, G)
FALCON_USER_DEFINED_UNITS_LITERAL(tera, T)
FALCON_USER_DEFINED_UNITS_LITERAL(peta, P)
FALCON_USER_DEFINED_UNITS_LITERAL(exa, E)
FALCON_USER_DEFINED_LD_UNITS_LITERAL(zetta, Z, 1.e-21)
FALCON_USER_DEFINED_LD_UNITS_LITERAL(yotta, Y, 1.e-24)

FALCON_USER_DEFINED_UNITS_LITERAL(kibi, Ki)
FALCON_USER_DEFINED_UNITS_LITERAL(mebi, Mi)
FALCON_USER_DEFINED_UNITS_LITERAL(gibi, Gi)
FALCON_USER_DEFINED_UNITS_LITERAL(tibi, Ti)
FALCON_USER_DEFINED_UNITS_LITERAL(pibi, Pi)
FALCON_USER_DEFINED_UNITS_LITERAL(exbi, Ei)

#undef FALCON_USER_DEFINED_UNITS_LITERAL
#undef FALCON_USER_DEFINED_LD_UNITS_LITERAL
#undef FALCON_USER_DEFINED_ULL_UNITS_LITERAL

namespace units_symbol {
	constexpr unsigned long long operator "" _MM (unsigned long long n)
	{ return operator "" _G(n); }
	constexpr long double operator "" _MM (long double n)
	{ return operator "" _G(n); }
}

}
}

#endif