#ifndef _FALCON_FUNCTIONAL_STD_PLACEHOLDER_HPP
#define _FALCON_FUNCTIONAL_STD_PLACEHOLDER_HPP

#include <functional>

namespace falcon {

template<int N, typename Placeholder = typename std::remove_reference<
  typename std::remove_cv<decltype(std::placeholders::_1)>::type
>::type>
struct std_placeholder
{};

template<int NewN, template<int> class Placeholder, int N>
struct std_placeholder<NewN, Placeholder<N> >
{
	typedef Placeholder<NewN> type;
};

template<typename>
struct to_std_placeholder;

}

#endif
