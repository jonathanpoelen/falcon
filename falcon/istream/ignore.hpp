#ifndef FALCON_ISTREAM_IGNORE_HPP
#define FALCON_ISTREAM_IGNORE_HPP

#include <ios>
#include <utility>
#include <type_traits>

namespace falcon {
namespace istream {

///\brief This function calls @c ignore() for that stream object.
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is)
{ return is.ignore(); }

namespace _aux {
  struct ignore_stream
  {};
}

/**
 * @brief Manipulator for @c ignore().
 * @param n  Number of characters to discard.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(n) for that object.
 */
_aux::ignore_stream ignore()
{ return {}; }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, _aux::ignore_stream)
{ return is.ignore(); }


namespace _aux {
  template<bool Lax, typename CharT, typename Traits, typename Compare>
  std::basic_istream<CharT, Traits>&
  ignore_fn(std::basic_istream<CharT, Traits>& is, Compare& comp)
  {
    typedef std::basic_istream<CharT, Traits> istream_type;
    typedef typename istream_type::sentry sentry;
    sentry cerb(is, true);
    if (cerb)
    {
      typedef std::basic_streambuf<CharT, Traits> streambuf_type;
      typedef typename istream_type::int_type int_type;
      const int_type eof = Traits::eof();
      streambuf_type* sb = is.rdbuf();
      int_type c = sb->sgetc();
      bool b = comp(c);

      std::ios_base::iostate err = std::ios_base::goodbit;

      while (!Traits::eq_int_type(c, eof) && b)
      {
        c = sb->snextc();
        b = comp(c);
      }

      if (Traits::eq_int_type(c, eof))
        err |= std::ios_base::eofbit;
      if (!Lax && b)
        err |= std::ios_base::badbit;

      if (err)
        is.setstate(err);
    }
    return is;
  }

  template<typename CharT, typename Traits, typename Compare>
  std::basic_istream<CharT, Traits>&
  ignore(
    std::basic_istream<CharT, Traits>& is
  , Compare& f
  , std::false_type)
  { return ignore_fn<false>(is, f); }

  template<typename CharT, typename Traits>
  std::basic_istream<CharT, Traits>&
  ignore(
    std::basic_istream<CharT, Traits>& is
  , std::streamsize n
  , std::true_type)
  { return is.ignore(n); }
}

/**
 * @brief This function calls @c ignore(n) for that stream object.
 * @param n  Number of characters to discard.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is, std::streamsize n)
{ return is.ignore(n); }

/**
 * @brief Discarding characters for which a predicate is false
 * @param comp A comparison functor.
 *
 * If @c comp() and the stream object have @c Traits::eof()
 * so @c std::badbit is set in the stream.
 */
template<typename CharT, typename Traits, typename Compare>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is, Compare comp)
{ return _aux::ignore(is, comp, std::is_integral<Compare>()); }

/**
 * @brief Discarding characters for which a predicate is false
 * @param comp A comparison functor.
 */
template<typename CharT, typename Traits, typename Compare>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is, Compare f)
{ return _aux::ignore_fn<true>(is, f); }

namespace _aux {
  struct ignore_size_stream
  { std::streamsize size;};

  template<typename Compare, bool Lax>
  struct ignore_functor_stream
  { Compare f; };
}

/**
 * @brief Manipulator for @c ignore.
 * @param n Number of characters to discard.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n) for that object.
 */
_aux::ignore_size_stream
ignore(std::streamsize n)
{ return {n}; }

/**
 * @brief Manipulator for @c ignore().
 * @param comp A comparison functor.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(n) for that object.
 */
template<typename Compare>
typename std::conditional<
  std::is_integral<Compare>::value
, _aux::ignore_size_stream
, _aux::ignore_functor_stream<Compare, false>
>::type
ignore(Compare comp)
{ return {std::move(comp)}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param comp A comparison functor.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(n) for that object.
 */
template<typename Compare>
_aux::ignore_functor_stream<Compare, true>
laxignore(Compare f)
{ return {f}; }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_size_stream n)
{ return is.ignore(n.size); }

template<typename CharT, typename Traits, typename Compare, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_functor_stream<Compare, Lax> func)
{ return _aux::ignore_fn<Lax>(is, func.f); }


/**
 * @brief This function calls @c ignore(n, delim) for that stream object.
 * @param n  Number of characters to discard.
 * @param delim  A "stop" character.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore(
  std::basic_istream<CharT, Traits>& is
, std::streamsize n
, typename std::basic_istream<CharT, Traits>::int_type delim)
{ return is.ignore(n, delim); }


namespace _aux {
  template<typename IntType>
  struct ignore_size_delimiter_stream
  {
    std::streamsize size;
    IntType delim;
  };
}

/**
 * @brief Manipulator for @c ignore().
 * @param n  Number of characters to discard.
 * @param delim  A "stop" character.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(n, delim) for that object.
 */
template<typename IntType>
_aux::ignore_size_delimiter_stream<IntType>
ignore(std::streamsize n, IntType delim)
{ return {n, delim}; }

template<typename CharT, typename Traits, typename IntType>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_size_delimiter_stream<IntType> n)
{ return is.ignore(n.size, n.delim); }


namespace _aux {
  template <typename InputIterator>
  struct ignore_range
  {
    InputIterator &first, &last;
    bool operator *() const
    { return first != last; }
    void operator ++() const
    { ++first; }
  };

  template<typename CharT>
  CharT
  ignore_get_char(const CharT * s)
  { return *s; }

  template<typename InputIterator>
  typename std::iterator_traits<InputIterator>::value_type
  ignore_get_char(const ignore_range<InputIterator>& r)
  { return *r.first; }

  template<bool Lax, typename CharT, typename Traits, typename StringOrRange>
  std::basic_istream<CharT, Traits>&
  ignore(std::basic_istream<CharT, Traits>& is, StringOrRange s)
  {
    typedef std::basic_istream<CharT, Traits> istream_type;
    typedef typename istream_type::sentry sentry;
    sentry cerb(is, true);
    if (cerb)
    {
      typedef std::basic_streambuf<CharT, Traits> streambuf_type;
      typedef typename istream_type::int_type int_type;
      const int_type eof = Traits::eof();
      streambuf_type* sb = is.rdbuf();
      int_type c = sb->sgetc();

      std::ios_base::iostate err = std::ios_base::goodbit;

      while (*s && !Traits::eq_int_type(c, eof)
          && Traits::eq(Traits::to_char_type(c), ignore_get_char(s)))
      {
        c = sb->snextc();
        ++s;
      }

      if (Traits::eq_int_type(c, eof))
        err |= std::ios_base::eofbit;
      if (!Lax && *s)
        err |= std::ios_base::badbit;

      if (err)
        is.setstate(err);
    }
    return is;
  }
}

/**
 * @brief Discarding characters in a sequence.
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * If the stream object have @c Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename CharT, typename Traits, typename InputIterator>
std::basic_istream<CharT, Traits>&
ignore(
  std::basic_istream<CharT, Traits>& is
, InputIterator first
, InputIterator last)
{ return _aux::ignore<false>(
  is
, _aux::ignore_range<InputIterator>{first, last}); }

/**
 * @brief Discarding characters in a sequence.
 * @param first An input iterator.
 * @param last  An input iterator.
 */
template<typename CharT, typename Traits, typename InputIterator>
std::basic_istream<CharT, Traits>&
laxignore(
  std::basic_istream<CharT, Traits>& is
, InputIterator first
, InputIterator last)
{ return _aux::ignore<true>(
  is
, _aux::ignore_range<InputIterator>{first, last}); }


namespace _aux {
  template<typename InputIterator, typename InputIterator2, bool Lax>
  struct ignore_iterator_stream
  {
    InputIterator first;
    InputIterator2 last;
  };
}

/**
 * @brief Manipulator for @c ignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(stream, @a first, @a last) for that object.
 */
template<typename InputIterator>
_aux::ignore_iterator_stream<InputIterator, InputIterator, false>
ignore(InputIterator first, InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(stream, @a first, @a last) for that object.
 */
template<typename InputIterator>
_aux::ignore_iterator_stream<InputIterator, InputIterator, true>
laxignore(InputIterator first, InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c ignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(stream, @a first, @a last) for that object.
 * The @a first iterator advance
 */
template<typename InputIterator>
_aux::ignore_iterator_stream<InputIterator&, InputIterator, false>
advance_ignore(InputIterator& first, InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls
 * @c ignore(stream, @a first, @a last) for that object.
 * The @a first iterator advance
 */
template<typename InputIterator>
_aux::ignore_iterator_stream<InputIterator&, InputIterator, true>
advance_laxignore(InputIterator first, InputIterator last)
{ return {first, last}; }

template<
  typename CharT, typename Traits
, typename InputIterator, typename InputIterator2
, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_iterator_stream<InputIterator, InputIterator2, Lax> range)
{ return _aux::ignore<Lax>(
  is
, _aux::ignore_range<InputIterator>{range.first, range.last}); }


/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c Traits::eof() so @c std::badbit
 * is set in the stream.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is, const CharT * s)
{ return _aux::ignore<false>(is, s); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is, const CharT * s)
{ return _aux::ignore<true>(is, s); }

namespace _aux {
  template<typename CharT, bool Lax>
  struct ignore_char_stream
  { const CharT * str; };
}

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT>
_aux::ignore_char_stream<CharT, false>
ignore(const CharT *s)
{ return {s}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename CharT>
_aux::ignore_char_stream<CharT, true>
laxignore(const CharT *s)
{ return {s}; }

template<typename CharT, typename Traits, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_char_stream<CharT, Lax> s)
{ return _aux::ignore<Lax>(is, s.str); }

namespace _aux {
  template<typename CharT, bool Lax>
  struct ignore_reference_char_stream
  { const CharT *& str; };
}

/**
 * @brief Manipulator for @c advance_ignore().
 * @param s A string.
 */
template<typename CharT>
_aux::ignore_reference_char_stream<CharT, false>
advance_ignore(const CharT *& s)
{ return {s}; }

/**
 * @brief Manipulator for @c advance_laxignore().
 * @param s A string.
 */
template<typename CharT>
_aux::ignore_reference_char_stream<CharT, true>
advance_laxignore(const CharT *& s)
{ return {s}; }

template<typename CharT, typename Traits, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_reference_char_stream<CharT, Lax> s)
{ return _aux::ignore<Lax>(is, s.str); }


/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c Traits::eof() so @c std::badbit
 * is set in the stream.
 */
template<
  typename CharT, typename Traits
, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
ignore(
  std::basic_istream<CharT, Traits>& is
, const std::basic_string<CharT, StringTraits, Alloc>& s)
{ return ignore(is, s.begin(), s.end()); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<
  typename CharT, typename Traits
, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
laxignore(
  std::basic_istream<CharT, Traits>& is
, const std::basic_string<CharT, StringTraits, Alloc>& s)
{ return laxignore(is, s.begin(), s.end()); }

namespace _aux {
  template<typename CharT, typename Traits, typename Alloc, bool Lax>
  struct ignore_string_stream
  { std::basic_string<CharT, Traits, Alloc> str; };
}

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT, typename Traits, typename Alloc>
_aux::ignore_string_stream<CharT, Traits, Alloc, false>
ignore(const std::basic_string<CharT, Traits, Alloc>&s)
{ return {s}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename CharT, typename Traits, typename Alloc>
_aux::ignore_string_stream<CharT, Traits, Alloc, true>
laxignore(const std::basic_string<CharT, Traits, Alloc>&s)
{ return {s}; }

template<
  typename CharT, typename Traits
, typename StringTraits, typename Alloc
, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_string_stream<CharT, StringTraits, Alloc, Lax> s)
{
  return Lax
  ? laxignore(is, s.str.begin(), s.str.end())
  : ignore(is, s.str.begin(), s.str.end());
}


/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore_of(std::basic_istream<CharT, Traits>& is, const CharT * s)
{
	typedef std::basic_istream<CharT, Traits> istream_type;
	typedef typename istream_type::int_type int_type;
	typedef std::char_traits<CharT> char_traits;
	std::size_t len = char_traits::length(s);
	return ignore(is, [s, len](const int_type& c) -> bool {
		return char_traits::find(s, len, char_traits::to_char_type(c));
	});
}

/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<
  typename CharT, typename Traits
, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
ignore_of(
  std::basic_istream<CharT, Traits>& is
, const std::basic_string<CharT, StringTraits, Alloc>& s)
{
  typedef std::basic_string<CharT, StringTraits, Alloc> string_type;
  typedef std::basic_istream<CharT, Traits> istream_type;
  typedef typename istream_type::int_type int_type;
  typedef std::char_traits<CharT> char_traits;
  return ignore(is, [&s](const int_type& c){
    return string_type::npos != s.find(char_traits::to_char_type(c));
  });
}


namespace _aux {
  template<typename CharT>
  struct ignore_of_char_stream
  { const CharT * str; };
}

/**
 * @brief Manipulator for @c ignore_of().
 * @param s A string.
 */
template<typename CharT>
_aux::ignore_of_char_stream<CharT>
ignore_of(const CharT *s)
{ return {s}; }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_of_char_stream<CharT> s)
{ return ignore_of(is, s.str); }


namespace _aux {
  template<typename CharT, typename Traits, typename Alloc>
  struct ignore_of_string_stream
  { const std::basic_string<CharT, Traits, Alloc> & str; };
}

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT, typename Traits, typename Alloc>
_aux::ignore_of_string_stream<CharT, Traits, Alloc>
ignore_of(const std::basic_string<CharT, Traits, Alloc>&s)
{ return {s}; }

template<
  typename CharT, typename Traits
, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
operator>>(
  std::basic_istream<CharT, Traits>& is
, _aux::ignore_of_string_stream<CharT, StringTraits, Alloc> s)
{ return ignore_of(is, s.str); }

}
}

#endif
