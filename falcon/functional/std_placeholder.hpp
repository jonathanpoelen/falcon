#ifndef _FALCON_FUNCTIONAL_STD_PLACEHOLDER_HPP
#define _FALCON_FUNCTIONAL_STD_PLACEHOLDER_HPP

#include <functional>

namespace falcon {

template<int _N, typename _Placeholder = typename std::remove_reference<typename std::remove_cv<decltype(std::placeholders::_1)>::type>::type>
struct std_placeholder
{};

template<int _NewN, template<int> class _Placeholder, int _N>
struct std_placeholder<_NewN, _Placeholder<_N> >
{
	typedef _Placeholder<_NewN> type;
};

template<typename>
struct to_std_placeholder;

}

#endif
