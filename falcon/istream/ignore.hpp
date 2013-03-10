#ifndef _FALCON_ISTREAM_IGNORE_HPP
#define _FALCON_ISTREAM_IGNORE_HPP

#include <iosfwd>
#include <utility>
#include <type_traits>

namespace falcon {
namespace istream {

///\brief This function calls @c ignore() for that stream object.
template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is)
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

template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_stream)
{ return is.ignore(); }


template<bool _Lax, typename _CharT, typename _Traits, typename _Compare>
std::basic_istream<_CharT, _Traits>& __ignore_fn(std::basic_istream<_CharT, _Traits>& is, _Compare& comp)
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;
	typedef typename __istream_type::sentry __sentry;
	__sentry __cerb(is, true);
	if (__cerb)
	{
		typedef std::basic_streambuf<_CharT, _Traits> __streambuf_type;
		typedef typename __istream_type::int_type __int_type;
		const __int_type __eof = _Traits::eof();
		__streambuf_type* __sb = is.rdbuf();
		__int_type __c = __sb->sgetc();
		bool __b = comp(__c);

		std::ios_base::iostate __err = std::ios_base::goodbit;

		while (!_Traits::eq_int_type(__c, __eof) && __b)
		{
			__c = __sb->snextc();
			__b = comp(__c);
		}

		if (_Traits::eq_int_type(__c, __eof))
			__err |= std::ios_base::eofbit;
		if (!_Lax && __b)
			__err |= std::ios_base::badbit;

		if (__err)
			is.setstate(__err);
	}
	return is;
}

template<typename _CharT, typename _Traits, typename _Compare>
std::basic_istream<_CharT, _Traits>& __ignore(std::basic_istream<_CharT, _Traits>& is, _Compare& f, std::false_type)
{ return __ignore_fn<false>(is, f); }

template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& __ignore(std::basic_istream<_CharT, _Traits>& is, std::streamsize n, std::true_type)
{ return is.ignore(n); }

/**
 * @brief This function calls @c ignore(n) for that stream object.
 * @param n  Number of characters to discard.
 */
template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is, std::streamsize n)
{ return is.ignore(n); }

/**
 * @brief Discarding characters for which a predicate is false
 * @param comp A comparison functor.
 *
 * If @c comp() and the stream object have @c _Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename _CharT, typename _Traits, typename _Compare>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is, _Compare comp)
{ return __ignore(is, comp, std::is_integral<_Compare>()); }

/**
 * @brief Discarding characters for which a predicate is false
 * @param comp A comparison functor.
 */
template<typename _CharT, typename _Traits, typename _Compare>
std::basic_istream<_CharT, _Traits>& laxignore(std::basic_istream<_CharT, _Traits>& is, _Compare f)
{ return __ignore_fn<true>(is, f); }

struct __ignore_size_stream
{ std::streamsize __size;};

template<typename _Compare, bool _Lax>
struct __ignore_functor_stream
{ _Compare __f; };

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
template<typename _Compare>
inline typename std::conditional<std::is_integral<_Compare>::value, __ignore_size_stream, __ignore_functor_stream<_Compare, false> >::type ignore(_Compare comp)
{ return {std::move(comp)}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param comp A comparison functor.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n) for that object.
 */
template<typename _Compare>
__ignore_functor_stream<_Compare, true> laxignore(_Compare f)
{ return {f}; }

template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_size_stream n)
{ return is.ignore(n.__size); }

template<typename _CharT, typename _Traits, typename _Compare, bool _Lax>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_functor_stream<_Compare, _Lax> func)
{ return __ignore_fn<_Lax>(is, func.f); }


/**
 * @brief This function calls @c ignore(n, delim) for that stream object.
 * @param n  Number of characters to discard.
 * @param delim  A "stop" character.
 */
template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is, std::streamsize n, typename std::basic_istream<_CharT, _Traits>::int_type delim)
{ return is.ignore(n, delim); }

template<typename _IntType>
struct __ignore_size_delimiter_stream
{
	std::streamsize __size;
	_IntType __delim;
};


/**
 * @brief Manipulator for @c ignore().
 * @param n  Number of characters to discard.
 * @param delim  A "stop" character.
 *
 * Sent to a stream object, this manipulator calls @c ignore(n, delim) for that object.
 */
template<typename _IntType>
inline __ignore_size_delimiter_stream<_IntType> ignore(std::streamsize n, _IntType delim)
{ return {n, delim}; }

template<typename _CharT, typename _Traits, typename _IntType>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_size_delimiter_stream<_IntType> n)
{ return is.ignore(n.__size, n.__delim); }


template <typename _InputIterator>
struct __ignore_range
{
	_InputIterator &first, &last;
	bool operator *() const
	{ return first != last; }
	void operator ++() const
	{ ++first; }
};

template<typename _CharT>
const _CharT __ignore_get_char(const _CharT * s)
{ return *s; }

template<typename _InputIterator>
typename std::iterator_traits<_InputIterator>::value_type
__ignore_get_char(const __ignore_range<_InputIterator>& r)
{ return *r.first; }

template<bool _Lax, typename _CharT, typename _Traits, typename _StringOrRange>
std::basic_istream<_CharT, _Traits>& __ignore(std::basic_istream<_CharT, _Traits>& is, _StringOrRange s)
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;
	typedef typename __istream_type::sentry __sentry;
	__sentry __cerb(is, true);
	if (__cerb)
	{
		typedef std::basic_streambuf<_CharT, _Traits> __streambuf_type;
		typedef typename __istream_type::int_type __int_type;
		const __int_type __eof = _Traits::eof();
		__streambuf_type* __sb = is.rdbuf();
		__int_type __c = __sb->sgetc();

		std::ios_base::iostate __err = std::ios_base::goodbit;

		while (*s && !_Traits::eq_int_type(__c, __eof) && _Traits::eq(_Traits::to_char_type(__c), __ignore_get_char<>(s)))
		{
			__c = __sb->snextc();
			++s;
		}

		if (_Traits::eq_int_type(__c, __eof))
			__err |= std::ios_base::eofbit;
		if (!_Lax && *s)
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
 * If the stream object have @c _Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename _CharT, typename _Traits, typename _InputIterator>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is, _InputIterator first, _InputIterator last)
{ return __ignore<false>(is, __ignore_range<_InputIterator>{first, last}); }

/**
 * @brief Discarding characters in a sequence.
 * @param first An input iterator.
 * @param last  An input iterator.
 */
template<typename _CharT, typename _Traits, typename _InputIterator>
std::basic_istream<_CharT, _Traits>& laxignore(std::basic_istream<_CharT, _Traits>& is, _InputIterator first, _InputIterator last)
{ return __ignore<true>(is, __ignore_range<_InputIterator>{first, last}); }

template<typename _InputIterator, typename _InputIterator2, bool _Lax>
struct __ignore_iterator_stream
{
	_InputIterator __first;
	_InputIterator2 __last;
};

/**
 * @brief Manipulator for @c ignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 */
template<typename _InputIterator>
__ignore_iterator_stream<_InputIterator, _InputIterator, false>
ignore(_InputIterator first, _InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 */
template<typename _InputIterator>
__ignore_iterator_stream<_InputIterator, _InputIterator, true>
laxignore(_InputIterator first, _InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c ignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 * The @a first iterator advance
 */
template<typename _InputIterator>
__ignore_iterator_stream<_InputIterator&, _InputIterator, false>
advance_ignore(_InputIterator& first, _InputIterator last)
{ return {first, last}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param first An input iterator.
 * @param last  An input iterator.
 *
 * Sent to a stream object, this manipulator calls @c ignore(stream, @a first, @a last) for that object.
 * The @a first iterator advance
 */
template<typename _InputIterator>
__ignore_iterator_stream<_InputIterator&, _InputIterator, true>
advance_laxignore(_InputIterator first, _InputIterator last)
{ return {first, last}; }

template<typename _CharT, typename _Traits, typename _InputIterator, typename _InputIterator2, bool _Lax>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_iterator_stream<_InputIterator, _InputIterator2, _Lax> range)
{ return __ignore<_Lax>(is, __ignore_range<_InputIterator>{range.__first, range.__last}); }


/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c _Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is, const _CharT * s)
{ return __ignore<false>(is, s); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& laxignore(std::basic_istream<_CharT, _Traits>& is, const _CharT * s)
{ return __ignore<true>(is, s); }

template<typename _CharT, bool _Lax>
struct __ignore_char_stream
{ const _CharT * __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename _CharT>
__ignore_char_stream<_CharT, false> ignore(const _CharT *s)
{ return {s}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename _CharT>
__ignore_char_stream<_CharT, true> laxignore(const _CharT *s)
{ return {s}; }

template<typename _CharT, typename _Traits, bool _Lax>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_char_stream<_CharT, _Lax> s)
{ return __ignore<_Lax>(is, s.__str); }

template<typename _CharT, bool _Lax>
struct __ignore_reference_char_stream
{ const _CharT *& __str; };

/**
 * @brief Manipulator for @c advance_ignore().
 * @param s A string.
 */
template<typename _CharT>
__ignore_reference_char_stream<_CharT, false> advance_ignore(const _CharT *& s)
{ return {s}; }

/**
 * @brief Manipulator for @c advance_laxignore().
 * @param s A string.
 */
template<typename _CharT>
__ignore_reference_char_stream<_CharT, true> advance_laxignore(const _CharT *& s)
{ return {s}; }

template<typename _CharT, typename _Traits, bool _Lax>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_reference_char_stream<_CharT, _Lax> s)
{ return __ignore<_Lax>(is, s.__str); }


/**
 * @brief Discarding a string.
 * @param s A string.
 *
 * If the stream object have @c _Traits::eof() so @c std::badbit is set in the stream.
 */
template<typename _CharT, typename _Traits, typename _StringTraits, typename _Alloc>
std::basic_istream<_CharT, _Traits>& ignore(std::basic_istream<_CharT, _Traits>& is, const std::basic_string<_CharT, _StringTraits, _Alloc>& s)
{ return ignore(is, s.begin(), s.end()); }

/**
 * @brief Discarding a string.
 * @param s A string.
 */
template<typename _CharT, typename _Traits, typename _StringTraits, typename _Alloc>
std::basic_istream<_CharT, _Traits>& laxignore(std::basic_istream<_CharT, _Traits>& is, const std::basic_string<_CharT, _StringTraits, _Alloc>& s)
{ return laxignore(is, s.begin(), s.end()); }

template<typename _CharT, typename _Traits, typename _Alloc, bool _Lax>
struct __ignore_string_stream
{ std::basic_string<_CharT, _Traits, _Alloc> __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
__ignore_string_stream<_CharT, _Traits, _Alloc, false> ignore(const std::basic_string<_CharT, _Traits, _Alloc>&s)
{ return {s}; }

/**
 * @brief Manipulator for @c laxignore().
 * @param s A string.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
__ignore_string_stream<_CharT, _Traits, _Alloc, true> laxignore(const std::basic_string<_CharT, _Traits, _Alloc>&s)
{ return {s}; }

template<typename _CharT, typename _Traits, typename _StringTraits, typename _Alloc, bool _Lax>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_string_stream<_CharT, _StringTraits, _Alloc, _Lax> s)
{ return _Lax ? laxignore(is, s.__str.begin(), s.__str.end()) : ignore(is, s.__str.begin(), s.__str.end()); }

/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& ignore_of(std::basic_istream<_CharT, _Traits>& is, const _CharT * s)
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;
	typedef typename __istream_type::int_type __int_type;
	typedef std::char_traits<_CharT> __char_traits;
	std::size_t len = __char_traits::length(s);
	return ignore(is, [s, len](const __int_type& c) -> bool {
		return __char_traits::find(s, len, __char_traits::to_char_type(c));
	});
}

/**
 * @brief Discarding characters of string.
 * @param s A string.
 */
template<typename _CharT, typename _Traits, typename _StringTraits, typename _Alloc>
std::basic_istream<_CharT, _Traits>& ignore_of(std::basic_istream<_CharT, _Traits>& is, const std::basic_string<_CharT, _StringTraits, _Alloc>& s)
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;
	typedef typename __istream_type::int_type __int_type;
	typedef std::char_traits<_CharT> __char_traits;
	return ignore(is, [&s](const __int_type& c){
		return std::basic_string<_CharT, _StringTraits, _Alloc>::npos != s.find(__char_traits::to_char_type(c));
	});
}


template<typename _CharT>
struct __ignore_of_char_stream
{ const _CharT * __str; };

/**
 * @brief Manipulator for @c ignore_of().
 * @param s A string.
 */
template<typename _CharT>
__ignore_of_char_stream<_CharT> ignore_of(const _CharT *s)
{ return {s}; }

template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_of_char_stream<_CharT> s)
{ return ignore_of(is, s.__str); }


template<typename _CharT, typename _Traits, typename _Alloc>
struct __ignore_of_string_stream
{ std::basic_string<_CharT, _Traits, _Alloc> __str; };

/**
 * @brief Manipulator for @c ignore().
 * @param s A string.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
__ignore_of_string_stream<_CharT, _Traits, _Alloc> ignore_of(const std::basic_string<_CharT, _Traits, _Alloc>&s)
{ return {s}; }

template<typename _CharT, typename _Traits, typename _StringTraits, typename _Alloc>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, __ignore_of_string_stream<_CharT, _StringTraits, _Alloc> s)
{ return ignore_of(is, s.__str); }

}
}

#endif