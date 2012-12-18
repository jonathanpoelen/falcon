#ifndef _FALCON_LITERAL_CHRONO_HPP
#define _FALCON_LITERAL_CHRONO_HPP

#include <falcon/literal/utility.hpp>

#include <chrono>

namespace falcon {
namespace literal {
namespace chrono {

#define FALCON_USER_DEFINED_CHRONO_LITERAL(suffix)\
	template<char... chars>\
	constexpr std::chrono::suffix operator "" _##suffix() noexcept\
	{ return std::chrono::suffix(convert_to<std::chrono::suffix::rep, chars...>()); }

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