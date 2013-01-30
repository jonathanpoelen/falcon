#ifndef _FALCON_DETAIL_STRING_CONVERTION_HPP
#define _FALCON_DETAIL_STRING_CONVERTION_HPP

#include <limits>
#include <stdexcept>
#include <cerrno>
#include <alloca.h>
#include <cstdarg>
#include <falcon/type_traits/is_same.hpp>

namespace falcon {
namespace detail {

template<typename _TRet, typename _Ret, typename _CharT>
_Ret __stoa_aux(const _TRet& __tmp, _Ret& __ret, const char* __name,
								const _CharT* __str, std::size_t* __idx, _CharT* __endptr)
{
	if (__endptr == __str)
		throw std::invalid_argument(__name);
	else if (errno == ERANGE
		|| (falcon::is_same<_Ret, int>::value
		&& (__tmp < static_cast<_TRet>(std::numeric_limits<int>::min())
		|| __tmp > static_cast<_TRet>(std::numeric_limits<int>::max()))))
		throw std::out_of_range(__name);
	else
		__ret = static_cast<_Ret>(__tmp);

	if (__idx)
		*__idx = __endptr - __str;
}

// Helper for all the sto* functions.
template<typename _Ret, typename _TRet, typename _CharT>
_Ret stoa(_TRet (*__convf) (const _CharT*, _CharT**),
					const char* __name, const _CharT* __str, std::size_t* __idx)
{
	_Ret __ret;

	_CharT* __endptr;
	errno = 0;
	const _TRet __tmp = __convf(__str, &__endptr);
	__stoa_aux(__tmp, __ret, __name, __str, __idx, __endptr);
	return __ret;
}

template<typename _Ret, typename _TRet, typename _CharT>
_Ret stoa(_TRet (*__convf) (const _CharT*, _CharT**, int base),
					const char* __name, const _CharT* __str, std::size_t* __idx,
					int __base)
{
	_Ret __ret;

	_CharT* __endptr;
	errno = 0;
	const _TRet __tmp = __convf(__str, &__endptr, __base);
	__stoa_aux(__tmp, __ret, __name, __str, __idx, __endptr);
	return __ret;
}

// Helper for the to_string / to_wstring functions.
template<typename _String, typename _CharT>
_String to_xstring(int (*__convf) (_CharT*, std::size_t, const _CharT*,
																	 __builtin_va_list),
									 std::size_t __n, const _CharT* __fmt, ...)
{
	// XXX Eventually the result will be constructed in place in
	// the C++0x string, likely with the help of internal hooks.
	_CharT* __s = static_cast<_CharT*>(alloca(sizeof(_CharT) * __n));

	std::va_list __args;
	va_start(__args, __fmt);

	const int __len = __convf(__s, __n, __fmt, __args);

	va_end(__args);

	return _String(__s, __s + __len);
}

}
}

#endif