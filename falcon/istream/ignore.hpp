#ifndef FALCON_ISTREAM_IGNORE_HPP
#define FALCON_ISTREAM_IGNORE_HPP

#include <falcon/string/cstringfwd.hpp>

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

struct __ignore_stream
{};

/**
 * @brief Manipulator for @c ignore().
 * @param n  Number of characters to discard.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n) for that object.
 */
inline __ignore_stream ignore()
{ return {}; }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, __ignore_stream)
{ return is.ignore(); }


template<bool Lax, typename CharT, typename Traits, typename Compare>
std::basic_istream<CharT, Traits>&
__ignore_fn(std::basic_istream<CharT, Traits>& is, Compare& comp)
{
	typedef std::basic_istream<CharT, Traits> __istream_type;
	typedef typename __istream_type::sentry __sentry;
	__sentry __cerb(is, true);
	if (__cerb)
	{
		typedef std::basic_streambuf<CharT, Traits> __streambuf_type;
		typedef typename __istream_type::int_type __int_type;
		const __int_type __eof = Traits::eof();
		__streambuf_type* __sb = is.rdbuf();
		__int_type __c = __sb->sgetc();
		bool __b = comp(__c);

		std::ios_base::iostate __err = std::ios_base::goodbit;

		while (!Traits::eq_int_type(__c, __eof) && __b)
		{
			__c = __sb->snextc();
			__b = comp(__c);
		}

		if (Traits::eq_int_type(__c, __eof))
			__err |= std::ios_base::eofbit;
		if (!Lax && __b)
			__err |= std::ios_base::badbit;

		if (__err)
			is.setstate(__err);
	}
	return is;
}

template<typename CharT, typename Traits, typename Compare>
std::basic_istream<CharT, Traits>&
__ignore(std::basic_istream<CharT, Traits>& is, Compare& f, std::false_type)
{ return __ignore_fn<false>(is, f); }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
__ignore(std::basic_istream<CharT, Traits>& is, std::streamsize n, std::true_type)
{ return is.ignore(n); }

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
 * If @c comp() and the stream object have @c Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename CharT, typename Traits, typename Compare>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is, Compare comp)
{ return __ignore(is, comp, std::is_integral<Compare>()); }

/**
 * @brief Discarding characters for which a predicate is false
 * @param comp A comparison functor.
 */
template<typename CharT, typename Traits, typename Compare>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is, Compare f)
{ return __ignore_fn<true>(is, f); }

struct __ignore_size_stream
{ std::streamsize __size;};

template<typename Compare, bool Lax>
struct __ignore_functor_stream
{ Compare __f; };

/**
 * @brief Manipulator for @c ignore.
 * @param n Number of characters to discard.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n) for that object.
 */
inline __ignore_size_stream ignore(std::streamsize n)
{ return {n}; }

/**
 * @brief Manipulator for @c ignore().
 * @param comp A comparison functor.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n) for that object.
 */
template<typename Compare>
inline typename std::conditional<std::is_integral<Compare>::value, __ignore_size_stream, __ignore_functor_stream<Compare, false> >::type
ignore(Compare comp)
{ return {std::move(comp)}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param comp A comparison functor.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n) for that object.
 */
template<typename Compare>
__ignore_functor_stream<Compare, true>
laxignore(Compare f)
{ return {f}; }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, __ignore_size_stream n)
{ return is.ignore(n.__size); }

template<typename CharT, typename Traits, typename Compare, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_functor_stream<Compare, Lax> func)
{ return __ignore_fn<Lax>(is, func.f); }


/**
 * @brief This function calls @c ignore(n, delim) for that stream object.
 * @param n  Number of characters to discard.
 * @param delim  A "stop" character.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is, std::streamsize n,
       typename std::basic_istream<CharT, Traits>::int_type delim)
{ return is.ignore(n, delim); }

template<typename IntType>
struct __ignore_size_delimiter_stream
{
	std::streamsize __size;
	IntType __delim;
};


/**
 * @brief Manipulator for @c ignore().
 * @param n  Number of characters to discard.
 * @param delim  A "stop" character.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n, delim) for that object.
 */
template<typename IntType>
inline __ignore_size_delimiter_stream<IntType>
ignore(std::streamsize n, IntType delim)
{ return {n, delim}; }

template<typename CharT, typename Traits, typename IntType>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_size_delimiter_stream<IntType> n)
{ return is.ignore(n.__size, n.__delim); }


template <typename InputIterator>
struct __ignore_range
{
	InputIterator &first, &last;
	bool operator *() const
	{ return first != last; }
	void operator ++() const
	{ ++first; }
};

template<typename CharT>
const CharT __ignore_get_char(const CharT * s)
{ return *s; }

template<typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type
__ignore_get_char(const __ignore_range<InputIterator>& r)
{ return *r.first; }

template<bool Lax, typename CharT, typename Traits, typename StringOrRange>
std::basic_istream<CharT, Traits>&
__ignore(std::basic_istream<CharT, Traits>& is, StringOrRange s)
{
	typedef std::basic_istream<CharT, Traits> __istream_type;
	typedef typename __istream_type::sentry __sentry;
	__sentry __cerb(is, true);
	if (__cerb)
	{
		typedef std::basic_streambuf<CharT, Traits> __streambuf_type;
		typedef typename __istream_type::int_type __int_type;
		const __int_type __eof = Traits::eof();
		__streambuf_type* __sb = is.rdbuf();
		__int_type __c = __sb->sgetc();

		std::ios_base::iostate __err = std::ios_base::goodbit;

		while (*s && !Traits::eq_int_type(__c, __eof) && Traits::eq(Traits::to_char_type(__c), __ignore_get_char(s)))
		{
			__c = __sb->snextc();
			++s;
		}

		if (Traits::eq_int_type(__c, __eof))
			__err |= std::ios_base::eofbit;
		if (!Lax && *s)
			__err |= std::ios_base::badbit;

		if (__err)
			is.setstate(__err);
	}
	return is;
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
ignore(std::basic_istream<CharT, Traits>& is, InputIterator first, InputIterator last)
{ return __ignore<false>(is, __ignore_range<InputIterator>{first, last}); }

/**
 * @brief Discarding characters in a sequence.
 * @param first An input iterator.
 * @param last  An input iterator.
 */
template<typename CharT, typename Traits, typename InputIterator>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is,
          InputIterator first, InputIterator last)
{ return __ignore<true>(is, __ignore_range<InputIterator>{first, last}); }

template<typename InputIterator, typename InputIterator2, bool Lax>
struct __ignore_iterator_stream
{
	InputIterator __first;
	InputIterator2 __last;
};

/**
 * @brief Manipulator for @c ignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 */
template<typename InputIterator>
__ignore_iterator_stream<InputIterator, InputIterator, false>
ignore(InputIterator first, InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 */
template<typename InputIterator>
__ignore_iterator_stream<InputIterator, InputIterator, true>
laxignore(InputIterator first, InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c ignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 * The @a first iterator advance
 */
template<typename InputIterator>
__ignore_iterator_stream<InputIterator&, InputIterator, false>
advance_ignore(InputIterator& first, InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 * The @a first iterator advance
 */
template<typename InputIterator>
__ignore_iterator_stream<InputIterator&, InputIterator, true>
advance_laxignore(InputIterator first, InputIterator last)
{ return {first, last}; }

template<typename CharT, typename Traits, typename InputIterator, typename InputIterator2, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_iterator_stream<InputIterator, InputIterator2, Lax> range)
{ return __ignore<Lax>(is, __ignore_range<InputIterator>{range.__first, range.__last}); }


/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is, const CharT * s)
{ return __ignore<false>(is, s); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is, const CharT * s)
{ return __ignore<true>(is, s); }

template<typename CharT, bool Lax>
struct __ignore_char_stream
{ const CharT * __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT>
__ignore_char_stream<CharT, false>
ignore(const CharT *s)
{ return {s}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename CharT>
__ignore_char_stream<CharT, true>
laxignore(const CharT *s)
{ return {s}; }

template<typename CharT, typename Traits, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, __ignore_char_stream<CharT, Lax> s)
{ return __ignore<Lax>(is, s.__str); }

template<typename CharT, bool Lax>
struct __ignore_reference_char_stream
{ const CharT *& __str; };

/**
 * @brief Manipulator for @c advance_ignore().
 * @param s A string.
 */
template<typename CharT>
__ignore_reference_char_stream<CharT, false>
advance_ignore(const CharT *& s)
{ return {s}; }

/**
 * @brief Manipulator for @c advance_laxignore().
 * @param s A string.
 */
template<typename CharT>
__ignore_reference_char_stream<CharT, true>
advance_laxignore(const CharT *& s)
{ return {s}; }

template<typename CharT, typename Traits, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_reference_char_stream<CharT, Lax> s)
{ return __ignore<Lax>(is, s.__str); }


/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename CharT, typename Traits, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is,
       const std::basic_string<CharT, StringTraits, Alloc>& s)
{ return ignore(is, s.begin(), s.end()); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<typename CharT, typename Traits, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is,
          const std::basic_string<CharT, StringTraits, Alloc>& s)
{ return laxignore(is, s.begin(), s.end()); }

template<typename CharT, typename Traits, typename Alloc, bool Lax>
struct __ignore_string_stream
{ std::basic_string<CharT, Traits, Alloc> __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT, typename Traits, typename Alloc>
__ignore_string_stream<CharT, Traits, Alloc, false>
ignore(const std::basic_string<CharT, Traits, Alloc>&s)
{ return {s}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename CharT, typename Traits, typename Alloc>
__ignore_string_stream<CharT, Traits, Alloc, true>
laxignore(const std::basic_string<CharT, Traits, Alloc>&s)
{ return {s}; }

template<typename CharT, typename Traits, typename StringTraits, typename Alloc, bool Lax>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_string_stream<CharT, StringTraits, Alloc, Lax> s)
{
  return Lax
  ? laxignore(is, s.__str.begin(), s.__str.end())
  : ignore(is, s.__str.begin(), s.__str.end());
}

/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename CharT, typename Traits, typename StringTraits>
std::basic_istream<CharT, Traits>&
ignore(std::basic_istream<CharT, Traits>& is,
       const basic_cstring<CharT, StringTraits>& s)
{ return ignore(is, s.begin(), s.end()); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<typename CharT, typename Traits, typename StringTraits>
std::basic_istream<CharT, Traits>&
laxignore(std::basic_istream<CharT, Traits>& is,
          const basic_cstring<CharT, StringTraits>& s)
{ return laxignore(is, s.begin(), s.end()); }

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT, typename Traits>
auto ignore(const basic_cstring<CharT, Traits>&s)
-> decltype(ignore(s.begin(), s.end()))
{ return ignore(s.begin(), s.end()); }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename CharT, typename Traits>
auto laxignore(const basic_cstring<CharT, Traits>&s)
-> decltype(laxignore(s.begin(), s.end()))
{ return laxignore(s.begin(), s.end()); }


/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
ignore_of(std::basic_istream<CharT, Traits>& is, const CharT * s)
{
	typedef std::basic_istream<CharT, Traits> __istream_type;
	typedef typename __istream_type::int_type __int_type;
	typedef std::char_traits<CharT> __char_traits;
	std::size_t len = __char_traits::length(s);
	return ignore(is, [s, len](const __int_type& c) -> bool {
		return __char_traits::find(s, len, __char_traits::to_char_type(c));
	});
}

/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<typename CharT, typename Traits, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
ignore_of(std::basic_istream<CharT, Traits>& is,
          const std::basic_string<CharT, StringTraits, Alloc>& s)
{
    typedef std::basic_istream<CharT, Traits> __istream_type;
    typedef typename __istream_type::int_type __int_type;
    typedef std::char_traits<CharT> __char_traits;
    return ignore(is, [&s](const __int_type& c){
        return std::basic_string<CharT, StringTraits, Alloc>::npos != s.find(__char_traits::to_char_type(c));
    });
}

/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<typename CharT, typename Traits, typename StringTraits>
std::basic_istream<CharT, Traits>&
ignore_of(std::basic_istream<CharT, Traits>& is,
          const basic_cstring<CharT, StringTraits>& s)
{
	typedef std::basic_istream<CharT, Traits> __istream_type;
	typedef typename __istream_type::int_type __int_type;
	typedef std::char_traits<CharT> __char_traits;
	return ignore(is, [&s](const __int_type& c){
		return std::basic_string<CharT, StringTraits>::npos != s.find(__char_traits::to_char_type(c));
	});
}


template<typename CharT>
struct __ignore_of_char_stream
{ const CharT * __str; };

/**
 * @brief Manipulator for @c ignore_of().
 * @param s A string.
 */
template<typename CharT>
__ignore_of_char_stream<CharT> ignore_of(const CharT *s)
{ return {s}; }

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, __ignore_of_char_stream<CharT> s)
{ return ignore_of(is, s.__str); }


template<typename CharT, typename Traits, typename Alloc>
struct __ignore_of_string_stream
{ std::basic_string<CharT, Traits, Alloc> __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT, typename Traits, typename Alloc>
__ignore_of_string_stream<CharT, Traits, Alloc>
ignore_of(const std::basic_string<CharT, Traits, Alloc>&s)
{ return {s}; }

template<typename CharT, typename Traits, typename StringTraits, typename Alloc>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_of_string_stream<CharT, StringTraits, Alloc> s)
{ return ignore_of(is, s.__str); }

template<typename CharT, typename Traits>
struct __ignore_of_cstring_stream
{ basic_cstring<CharT, Traits> __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename CharT, typename Traits>
__ignore_of_cstring_stream<CharT, Traits>
ignore_of(const basic_cstring<CharT, Traits>&s)
{ return {s}; }

template<typename CharT, typename Traits, typename StringTraits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           __ignore_of_cstring_stream<CharT, StringTraits> s)
{ return ignore_of(is, s.__str); }

}
}

#endif
