#ifndef _FALCON_LITERAL_CHRONO_HPP
#define _FALCON_LITERAL_CHRONO_HPP

#include <falcon/literal/detail/literal_support.hpp>

#include <chrono>

namespace falcon {
namespace literal {
namespace chrono {

#define FALCON_USER_DEFINED_CHRONO_LITERAL(suffix)\
	constexpr std::chrono::suffix operator "" _##suffix(unsigned long long n)\
	{ return std::chrono::suffix(n); }

	FALCON_USER_DEFINED_CHRONO_LITERAL(nanoseconds)
	FALCON_USER_DEFINED_CHRONO_LITERAL(microseconds)
	FALCON_USER_DEFINED_CHRONO_LITERAL(milliseconds)
	FALCON_USER_DEFINED_CHRONO_LITERAL(seconds)
	FALCON_USER_DEFINED_CHRONO_LITERAL(minutes)
	FALCON_USER_DEFINED_CHRONO_LITERAL(hours)

#undef FALCON_USER_DEFINED_CHRONO_LITERAL

}
}
}

#endif