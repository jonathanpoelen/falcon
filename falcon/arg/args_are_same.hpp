#ifndef _FALCON_ARGS_ARE_SAME_HPP
#define _FALCON_ARGS_ARE_SAME_HPP

namespace falcon {

template <typename... _Args>
struct args_are_same
{
	static const bool value = true;
};

template <typename _T, typename _U, typename... _Args>
struct args_are_same<_T, _U, _Args...>
{
	static const bool value = false;
};

template <typename _T, typename... _Args>
struct args_are_same<_T, _T, _Args...>
{
	static const bool value = args_are_same<_T, _Args...>::value;
};

}

#endif
