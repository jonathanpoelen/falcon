#ifndef FALCON_STRING_STOX_HPP
#define FALCON_STRING_STOX_HPP

#include <falcon/type_traits/is_same.hpp>

#include <string>
#include <limits>
#include <stdexcept>
#include <cerrno>

namespace falcon {

namespace aux_ {

template<typename TRet, typename Ret, typename CharT>
void stoa_aux(const TRet tmp, Ret& ret, const char* name,
              const CharT* str, std::size_t* idx, CharT* endptr)
{
  if (endptr == str)
    throw std::invalid_argument(name);
  else if (errno == ERANGE
    || (falcon::is_same<Ret, int>::value
      && (tmp < static_cast<TRet>(std::numeric_limits<int>::min())
      || tmp > static_cast<TRet>(std::numeric_limits<int>::max()))))
    throw std::out_of_range(name);
  else
    ret = static_cast<Ret>(tmp);

  if (idx)
    *idx = std::size_t(endptr - str);
}

// Helper for all the sto* functions.
template<typename Ret, typename Conv, typename CharT>
Ret stoa(Conv conv, const char* name, const CharT* str, std::size_t* idx)
{
  Ret ret;
  CharT* endptr;
  errno = 0;
  stoa_aux(conv(str, &endptr), ret, name, str, idx, endptr);
  return ret;
}

template<typename Ret, typename Conv, typename CharT>
Ret stoa(Conv conv, const char* name, const CharT* str, std::size_t* idx, int base)
{
  Ret ret;
  CharT* endptr;
  errno = 0;
  stoa_aux(conv(str, &endptr, base), ret, name, str, idx, endptr);
  return ret;
}

}

#define FALCON_BASIC_CSTRING_TO_WRAPPER(result_type, std_fname, std_wfname)   \
  namespace aux_ {                                                            \
    struct std_fname##_wrapper {                                              \
      result_type                                                             \
      operator()(const char * str, char ** endptr = 0, int base = 10) const { \
        return static_cast<result_type>(::std::std_fname(str, endptr, base)); \
      }                                                                       \
                                                                              \
      result_type                                                             \
      operator()(const wchar_t * str, wchar_t ** endptr = 0,                  \
                 int base = 10) const {                                       \
        return static_cast<result_type>(                                      \
          ::std::std_wfname(str, endptr, base));                              \
      }                                                                       \
    };                                                                        \
  }

#define FALCON_BASIC_CSTRING_TO_IMPL(result_type, char_type, fname, std_fname) \
  template<typename Trait, typename Allocator>                                 \
  inline result_type                                                           \
  fname(const std::basic_string<char_type, Trait, Allocator>& s,               \
        std::size_t* idx = 0, int base = 10)                                   \
  { return ::falcon::aux_::stoa<result_type>                                   \
    (::falcon::aux_::std_fname##_wrapper(), #fname, s.c_str(), idx, base); }

#define FALCON_BASIC_CSTRING_TO(result_type, fname, type)                   \
  FALCON_BASIC_CSTRING_TO_WRAPPER(result_type, strto##type, wcsto##type)    \
  FALCON_BASIC_CSTRING_TO_IMPL(result_type, char, fname, strto##type)       \
  FALCON_BASIC_CSTRING_TO_IMPL(result_type, const char, fname, strto##type) \
  FALCON_BASIC_CSTRING_TO_IMPL(result_type, wchar_t, fname, strto##type)    \
  FALCON_BASIC_CSTRING_TO_IMPL(result_type, const wchar_t, fname, strto##type)

FALCON_BASIC_CSTRING_TO(long, stol, l)
FALCON_BASIC_CSTRING_TO(unsigned long, stoul, ul)
#if __cplusplus >= 201103L
FALCON_BASIC_CSTRING_TO(long long, stoll, ll)
FALCON_BASIC_CSTRING_TO(unsigned long long, stoull, ull)
#endif

# undef FALCON_BASIC_CSTRING_TO_WRAPPER
#define FALCON_BASIC_CSTRING_TO_WRAPPER(result_type, std_fname, std_wfname)
FALCON_BASIC_CSTRING_TO(int, stoi, l)

# undef FALCON_BASIC_CSTRING_TO_WRAPPER
#define FALCON_BASIC_CSTRING_TO_WRAPPER(result_type, std_fname, std_wfname) \
  namespace aux_ {                                                          \
    struct std_fname##_wrapper {                                            \
      result_type                                                           \
      operator()(const char * str, char ** endptr = 0) const {              \
        return ::std::std_fname(str, endptr);                               \
      }                                                                     \
                                                                            \
      result_type                                                           \
      operator()(const wchar_t * str, wchar_t ** endptr = 0) const {        \
        return ::std::std_wfname(str, endptr);                              \
      }                                                                     \
    };                                                                      \
  }

# undef FALCON_BASIC_CSTRING_TO_IMPL
#define FALCON_BASIC_CSTRING_TO_IMPL(result_type, char_type, fname, std_fname) \
  template<typename Trait, typename Allocator>                                 \
  inline result_type                                                           \
  fname(const std::basic_string<char_type, Trait, Allocator>& s,               \
        std::size_t* idx = 0)                                                  \
  { return ::falcon::aux_::stoa<result_type>                                   \
    (::falcon::aux_::std_fname##_wrapper(), #fname, s.c_str(), idx); }

FALCON_BASIC_CSTRING_TO(float, stof, f)
FALCON_BASIC_CSTRING_TO(double, stod, d)
#if __cplusplus >= 201103L
FALCON_BASIC_CSTRING_TO(double long, stold, ld)
#endif
#undef FALCON_BASIC_CSTRING_TO
#undef FALCON_BASIC_CSTRING_TO_IMPL
#undef FALCON_BASIC_CSTRING_TO_WRAPPER

}

#endif
