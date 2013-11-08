#ifndef FALCON_STRING_STOX_HPP
#define FALCON_STRING_STOX_HPP

#include <falcon/type_traits/is_same.hpp>

#include <string>
#include <limits>
#include <stdexcept>
#include <cerrno>
#include <cstdarg>
#if __cplusplus < 201103L
# if defined __USE_GNU || defined __USE_BSD || defined __USE_MISC
#   include <alloca.h>
# endif
#endif

namespace falcon {

namespace detail {
template<typename TRet, typename Ret, typename CharT>
Ret __stoa_aux(const TRet& __tmp, Ret& __ret, const char* __name,
               const CharT* __str, std::size_t* __idx, CharT* __endptr)
{
  if (__endptr == __str)
    throw std::invalid_argument(__name);
  else if (errno == ERANGE
    || (falcon::is_same<Ret, int>::value
    && (__tmp < static_cast<TRet>(std::numeric_limits<int>::min())
    || __tmp > static_cast<TRet>(std::numeric_limits<int>::max()))))
    throw std::out_of_range(__name);
  else
    __ret = static_cast<Ret>(__tmp);

  if (__idx)
    *__idx = __endptr - __str;
}

// Helper for all the sto* functions.
template<typename Ret, typename TRet, typename CharT>
Ret stoa(TRet (*__convf) (const CharT*, CharT**),
         const char* __name, const CharT* __str, std::size_t* __idx)
{
  Ret __ret;

  CharT* __endptr;
  errno = 0;
  const TRet __tmp = __convf(__str, &__endptr);
  __stoa_aux(__tmp, __ret, __name, __str, __idx, __endptr);
  return __ret;
}

template<typename Ret, typename TRet, typename CharT>
Ret stoa(TRet (*__convf) (const CharT*, CharT**, int base),
         const char* __name, const CharT* __str, std::size_t* __idx,
         int __base)
{
  Ret __ret;

  CharT* __endptr;
  errno = 0;
  const TRet __tmp = __convf(__str, &__endptr, __base);
  __stoa_aux(__tmp, __ret, __name, __str, __idx, __endptr);
  return __ret;
}

// Helper for the to_string / to_wstring functions.
template<typename String, typename CharT>
String to_xstring(int (*__convf) (CharT*, std::size_t, const CharT*, std::va_list),
                  std::size_t __n, const CharT* __fmt, ...)
{
#if __cplusplus >= 201103L
  String ret;
  ret.resize(__n);
  CharT* __s = &ret[0];
#elif defined __USE_GNU || defined __USE_BSD || defined __USE_MISC
  CharT* __s = static_cast<CharT*>(alloca(sizeof(CharT) * __n));
#else
  CharT* __s = new CharT[__n];
#endif

  std::va_list __args;
  va_start(__args, __fmt);

  const int __len = __convf(__s, __n, __fmt, __args);

  va_end(__args);

#if __cplusplus >= 201103L
  return ret;
#elif defined __USE_GNU || defined __USE_BSD || defined __USE_MISC
  return String(__s, __s + __len);
# else
  String ret(__s, __s + __len);
  delete [] __s;
  return ret;
#endif
}
}

#define FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, std_fname)            \
  template<typename CharT, typename Allocator>                                 \
  inline result_type                                                           \
  fname(const std::basic_string<CharT, std::char_traits<CharT>, Allocator>& s, \
        std::size_t* __idx = 0, int __base = 10)                               \
  { return ::falcon::detail::stoa<result_type>                                 \
  (&std_fname, #fname, s.c_str(), __idx, __base); }

#define FALCON_BASIC_CSTRING_TO(result_type, fname, type)       \
  FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, strto##type)

FALCON_BASIC_CSTRING_TO(int, stoi, l)
FALCON_BASIC_CSTRING_TO(long, stol, l)
FALCON_BASIC_CSTRING_TO(unsigned long, stoul, ul)
#if __cplusplus >= 201103L
FALCON_BASIC_CSTRING_TO(long long, stoll, ll)
FALCON_BASIC_CSTRING_TO(unsigned long long, stoull, ull)
#endif

#undef FALCON_BASIC_CSTRING_TO_IMPL

#define FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, std_fname)            \
  template<typename CharT, typename Allocator>                                 \
  inline result_type                                                           \
  fname(const std::basic_string<CharT, std::char_traits<CharT>, Allocator>& s, \
        std::size_t* __idx = 0)                                                \
  { return ::falcon::detail::stoa<result_type>                                 \
  (&std_fname, #fname, s.c_str(), __idx); }

FALCON_BASIC_CSTRING_TO(float, stof, f)
FALCON_BASIC_CSTRING_TO(double, stod, d)
#if __cplusplus >= 201103L
FALCON_BASIC_CSTRING_TO(double long, stold, ld)
#endif
#undef FALCON_BASIC_CSTRING_TO
#undef FALCON_BASIC_CSTRING_TO_IMPL

}

#endif
