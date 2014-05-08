#ifndef FALCON_IOSTREAMS_FORMAT_HPP
#define FALCON_IOSTREAMS_FORMAT_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/parameter/parameter_index.hpp>
#include <falcon/string/cstring.hpp>
#include <falcon/iostreams/ignore.hpp>

#include <iosfwd>

namespace falcon {
namespace iostreams {

template <
  typename CharT
, typename Traits = std::char_traits<CharT>
, typename Allocator = std::allocator<CharT>>
class basic_format
{
  typedef const CharT * const_pointer;
  typedef std::basic_string<CharT, Traits, Allocator> string_type;

public:
  struct item_type {
    const_pointer pptr;
    const_pointer epptr;
    std::size_t arg;
  };

  using iterator = typename std::vector<item_type>::const_iterator;
  using const_iterator = iterator;
  using reverse_iterator = typename std::vector<item_type>::const_reverse_iterator;
  using const_reverse_iterator = reverse_iterator;

public:
  basic_format() = default;

  basic_format(const string_type & sfmt)
  : fmt(sfmt)
  {
    elems.reserve(4);
    compute_format();
  }

  basic_format(string_type && sfmt)
  : fmt(std::move(sfmt))
  {
    elems.reserve(4);
    compute_format();
  }

  template<typename... Args>
  std::basic_ostream<CharT, Traits> &
  operator()(std::basic_ostream<CharT, Traits> & os, const Args&... args) const {
    apply(build_parameter_index_t<sizeof...(Args)>(), os, args...);
    return os;
  }

  template<typename... Args>
  std::basic_istream<CharT, Traits> &
  operator()(std::basic_istream<CharT, Traits> & is, Args&... args) const {
    apply(build_parameter_index_t<sizeof...(Args)>(), is, args...);
    return is;
  }

  const string_type & format() const
  { return fmt; }

  void format(const string_type & sfmt)
  {
    fmt = sfmt;
    elems.clear();
    compute_format();
  }

  void format(string_type && sfmt)
  {
    fmt = std::move(sfmt);
    elems.clear();
    compute_format();
  }

  const_iterator begin() const
  { return elems.begin(); }

  const_iterator end() const
  { return elems.end(); }

  const_iterator cbegin() const
  { return elems.begin(); }

  const_iterator cend() const
  { return elems.end(); }

  const_reverse_iterator rbegin() const
  { return elems.rbegin(); }

  const_reverse_iterator rend() const
  { return elems.rend(); }

  const_reverse_iterator crbegin() const
  { return elems.rbegin(); }

  const_reverse_iterator crend() const
  { return elems.rend(); }

private:
  template<std::size_t... Indexes, typename... Args>
  void apply(parameter_index<Indexes...>,
             std::basic_ostream<CharT, Traits> & os, const Args&... args) const {
    for (const item_type & e: elems) {
      os << basic_const_cstring<CharT>(e.pptr, e.epptr);
      if (e.arg) {
        FALCON_UNPACK((Indexes+1 == e.arg ? void(os << args) : void()));
      }
    }
  }

  template<std::size_t... Indexes, typename... Args>
  void apply(parameter_index<Indexes...>,
             std::basic_istream<CharT, Traits> & is, Args&... args) const {
    for (const item_type & e: elems) {
      if (e.pptr != e.epptr) {
        if (!istream::ignore(is, e.pptr, e.epptr)) {
          break;
        }
      }
      if (e.arg) {
        FALCON_UNPACK((Indexes+1 == e.arg ? void(is >> args) : void()));
      }
    }
  }

  void compute_format()
  {
    elems.reserve(4);
    const_pointer pos = fmt.data();
    const_pointer last = pos + fmt.size();
    constexpr typename Traits::char_type zero('0');
    typename string_type::size_type n;
    bool test;
    for (const_pointer first = pos; first != last;) {
      if (Traits::eq(*first, '%')) {
        if (++first == last) {
          break;
        }

        if ((test = Traits::eq(*first, '%')) || !(n = *first - zero)) {
          if (++first == last) {
            break;
          }
          const const_pointer tmp = first-(test ? 1 : 2);
          if (pos != tmp) {
            elems.push_back({pos, tmp, 0});
          }
          pos = first;
          continue;
        }

        elems.push_back({pos, first-1, 0});

        if (++first != last && std::isdigit(*first)) {
          n *= 10;
          n += *first - zero;
          if (++first != last && std::isdigit(*first)) {
            n *= 10;
            n += *first - zero;
            if (++first != last && std::isdigit(*first)) {
              n *= 10;
            }
          }
        }

        pos = first;

        elems.back().arg = n;
        continue;
      }
      ++first;
    }
    if (pos != last) {
      elems.push_back({pos, last, 0});
    }
  }

private:
  std::vector<item_type> elems;
  string_type fmt;
};

template <
typename CharT
, typename Traits = std::char_traits<CharT>
, typename Allocator = std::allocator<CharT>>
basic_format<CharT, Traits, Allocator>
formatter(const std::basic_string<CharT, Traits, Allocator> & s) {
  return {s};
}


namespace _aux {

template <typename FormatTraits, typename Stream, typename Size
, std::size_t... Indexes, typename... Args>
void putgetf(::falcon::parameter_index<Indexes...>, Stream & ss,
             const typename Stream::char_type * fmt,
             Size fmtlen, Args&&... args)
{
  static_assert(sizeof...(args) < 1000, "too many arguments (the limit is 999)");
  using Traits = typename Stream::traits_type;
  using CharT = typename Stream::char_type;
  using const_pointer = const CharT *;
  const_pointer pos = fmt;
  const_pointer last = fmt + fmtlen;
  typename Traits::char_type zero('0');
  bool test;
  Size n;
  for (const_pointer first = fmt; first != last;) {
    if (Traits::eq(*first, '%')) {
      if (++first == last) {
        break;
      }

      if ((test = Traits::eq(*first, '%')) || !(n = *first - zero)) {
        if (++first == last) {
          break ;
        }
        const const_pointer tmp = first-(test ? 1 : 2);
        if (pos != tmp) {
          FormatTraits::send(ss, pos, tmp);
        }
        pos = first;
        continue;
      }

      if (pos+1 != first) {
        FormatTraits::send(ss, pos, first-1);
      }

      if (++first != last && std::isdigit(*first)) {
        n *= 10;
        if (sizeof...(args) > 9) {
          n += *first - zero;
          if (++first != last && std::isdigit(*first)) {
            n *= 10;
            if (sizeof...(args) > 99) {
              n += *first - zero;
              if (++first != last && std::isdigit(*first)) {
                n *= 10;
              }
            }
          }
        }
      }

      if (n > sizeof...(args)) {
        throw std::runtime_error("too many arguments");
      }

      pos = first;
      --n;
      FALCON_UNPACK((Indexes == n ? void(FormatTraits::arg(ss, args)) : void()));
      continue;
    }
    ++first;
  }

  if (pos != last) {
    FormatTraits::send(ss, pos, last);
  }
}

struct putf_traits {
  template <typename CharT, typename Traits>
  static void send(std::basic_ostream<CharT, Traits> & os,
                   const CharT * first, const CharT * last) {
    os << basic_const_cstring<CharT, Traits>(first, last);
  }

  template <typename CharT, typename Traits, typename T>
  static void arg(std::basic_ostream<CharT, Traits> & os, const T & x) {
    os << x;
  }
};

struct getf_traits {
  template <typename CharT, typename Traits>
  static void send(std::basic_istream<CharT, Traits> & is,
                   const CharT * first, const CharT * last) {
    falcon::istream::ignore(is, first, last);
  }

  template <typename CharT, typename Traits, typename T>
  static void arg(std::basic_istream<CharT, Traits> & is, T & x) {
    is >> x;
  }
};

}

template <typename CharT, typename Traits, typename... Args>
std::basic_ostream<CharT, Traits> &
putf(std::basic_ostream<CharT, Traits> & os, const char * fmt, const Args&... args)
{
  _aux::putgetf<_aux::putf_traits>(build_parameter_index_t<sizeof...(args)>(), os, fmt,
                           std::char_traits<char>::length(fmt), args...);
  return os;
}

template <typename CharT, typename Traits, typename... Args>
std::basic_istream<CharT, Traits> &
getf(std::basic_istream<CharT, Traits> & is, const char * fmt, Args&... args)
{
  _aux::putgetf<_aux::getf_traits>(build_parameter_index_t<sizeof...(args)>(), is, fmt,
                           std::char_traits<char>::length(fmt), args...);
  return is;
}

template <typename CharT, typename Traits, typename Allocator, typename... Args>
std::basic_ostream<CharT, Traits> &
putf(std::basic_ostream<CharT, Traits> & os,
     std::basic_string<CharT, Traits, Allocator> fmt,
     const Args&... args)
{
  _aux::putgetf<_aux::putf_traits>(build_parameter_index_t<sizeof...(args)>(), os, fmt,
                           fmt.size(), args...);
  return os;
}

template <typename CharT, typename Traits, typename Allocator, typename... Args>
std::basic_istream<CharT, Traits> &
getf(std::basic_istream<CharT, Traits> & is,
     std::basic_string<CharT, Traits, Allocator> fmt,
     Args&... args)
{
  _aux::putgetf<_aux::getf_traits>(build_parameter_index_t<sizeof...(args)>(), is, fmt,
                           fmt.size(), args...);
  return is;
}

}
}

#endif
