#ifndef FALCON_IOSTREAM_JOIN_HPP
#define FALCON_IOSTREAM_JOIN_HPP

#include <iosfwd>
#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/is_ios.hpp>
#include <falcon/type_traits/enable_if.hpp>

namespace falcon {

namespace iostreams {

template<class CharT, class Traits, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
join(
  std::basic_ostream<CharT, Traits>& os
, ForwardIterator first
, ForwardIterator last
, const CharT* glue
, std::streamsize n)
{
	if (first == last)
		return os;
	const std::streamsize w = os.width();
	os << *first;
	if (w)
	{
		while (++first != last)
		{
			os.write(glue, n).width(w);
			os << *first;
		}
	}
	else
	{
		while (++first != last)
			os.write(glue, n) << *first;
	}
	return os;
}

template<class CharT, class Traits, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
join(
  std::basic_ostream<CharT, Traits>& os
, ForwardIterator first
, ForwardIterator last
, const CharT* glue)
{ return join(
  os, first, last, glue
, static_cast<std::streamsize>(Traits::length(glue))); }

template<class CharT, class Traits, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
join(
  std::basic_ostream<CharT, Traits>& os
, ForwardIterator first
, ForwardIterator last
, CharT glue = ',')
{ return join(os, first, last, &glue, 1); }

template<class CharT, class Traits, class Container>
std::basic_ostream<CharT, Traits>&
join(
  std::basic_ostream<CharT, Traits>& os
, const Container& container
, const CharT* glue)
{ return join(
  os, begin(container), end(container), glue
, static_cast<std::streamsize>(Traits::length(glue))); }

template<class CharT, class Traits, class Container>
std::basic_ostream<CharT, Traits>&
join(
  std::basic_ostream<CharT, Traits>& os
, const Container& container
, const CharT* glue
, std::streamsize size)
{ return join(os, begin(container), end(container), glue, size); }

template<class CharT, class Traits, class Container>
std::basic_ostream<CharT, Traits>&
join(
  std::basic_ostream<CharT, Traits>& os
, const Container& container
, CharT glue = ',')
{ return join(os, begin(container), end(container), &glue, 1); }


template<
  class CharT
, class CharOrStringT
, class ForwardIterator
, bool SpecifiedSize = false>
struct join_iterator_wrapper
{
	typedef CharOrStringT value_type;
	typedef ForwardIterator iterator_type;

	join_iterator_wrapper(
    iterator_type first
  , iterator_type last
  , value_type glue)
	: _glue(glue)
	, _first(first)
	, _last(last)
	{}

	value_type _glue;
	iterator_type _first;
	iterator_type _last;
};

template<class CharT, class CharOrStringT, class ForwardIterator>
struct join_iterator_wrapper<CharT, CharOrStringT, ForwardIterator, true>
{
	typedef CharOrStringT value_type;
	typedef ForwardIterator iterator_type;

	join_iterator_wrapper(
    iterator_type first
  , iterator_type last
  , value_type glue
  , std::streamsize size)
	: _glue(glue)
	, _first(first)
	, _last(last)
	, _size(size)
	{}

	value_type _glue;
	iterator_type _first;
	iterator_type _last;
	std::streamsize _size;
};

template<class CharT, class Traits, class CharOrStringT, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
operator<<(
  std::basic_ostream<CharT, Traits>& os
, join_iterator_wrapper<CharT, CharOrStringT, ForwardIterator, false> wrapper)
{ return join(os, wrapper._first, wrapper._last, wrapper._glue); }

template<class CharT, class Traits, class CharOrStringT, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
operator<<(
  std::basic_ostream<CharT, Traits>& os
, join_iterator_wrapper<CharT, CharOrStringT, ForwardIterator, true> wrapper)
{ return join(os, wrapper._first, wrapper._last, wrapper._glue, wrapper._size); }

template<class CharT, class ForwardIterator>
join_iterator_wrapper<CharT, const CharT*, ForwardIterator>
join(ForwardIterator first, ForwardIterator last, const CharT* glue)
{
  return join_iterator_wrapper<CharT, const CharT*, ForwardIterator>
    (first, last, glue);
}

template<class CharT, class ForwardIterator>
join_iterator_wrapper<CharT, CharT, ForwardIterator>
join(ForwardIterator first, ForwardIterator last, CharT glue)
{
  return join_iterator_wrapper<CharT, CharT, ForwardIterator>
    (first, last, glue);
}

template<class ForwardIterator>
join_iterator_wrapper<char, char, ForwardIterator>
join(ForwardIterator first, ForwardIterator last)
{ return join_iterator_wrapper<char, char, ForwardIterator>(first, last, ','); }

template<class CharT, class ForwardIterator>
join_iterator_wrapper<CharT, const CharT*, ForwardIterator, true>
join(
  ForwardIterator first
, ForwardIterator last
, const CharT* glue
, std::streamsize size)
{
	return join_iterator_wrapper<CharT, const CharT*, ForwardIterator, true>
    (first, last, glue, size);
}


template<
  class CharT
, class CharOrStringT
, class Container
, bool SpecifiedSize = false>
struct join_wrapper
{
	typedef CharOrStringT value_type;
	typedef const Container& container_type;

	join_wrapper(container_type container, value_type glue)
		: _glue(glue)
		, _container(container)
	{}

	value_type _glue;
	container_type _container;
};

template<class CharT, class CharOrStringT, class Container>
struct join_wrapper<CharT, CharOrStringT, Container, true>
{
	typedef CharOrStringT value_type;
	typedef const Container& container_type;

	join_wrapper(container_type container, value_type glue, std::streamsize size)
		: _glue(glue)
		, _container(container)
		, _size(size)
	{}

	value_type _glue;
	container_type _container;
	std::streamsize _size;
};

template<class CharT, class Traits, class CharOrStringT, class Container>
std::basic_ostream<CharT, Traits>&
operator<<(
  std::basic_ostream<CharT, Traits>& os
, join_wrapper<CharT, CharOrStringT, Container, false> wrapper)
{ return join(
  os
, begin(wrapper._container)
, end(wrapper._container)
, wrapper._glue); }

template<class CharT, class Traits, class CharOrStringT, class Container>
std::basic_ostream<CharT, Traits>&
operator<<(
  std::basic_ostream<CharT, Traits>& os
, join_wrapper<CharT, CharOrStringT, Container, true> wrapper)
{ return join(
  os
, begin(wrapper._container)
, end(wrapper._container)
, wrapper._glue
, wrapper._size); }

template<class CharT, class Container>
typename enable_if<
  !is_ostream<Container>::value
, join_wrapper<CharT, const CharT*, Container>
>::type
join(const Container& container, const CharT* glue)
{ return join_wrapper<CharT, const CharT*, Container>(container, glue); }

template<class CharT, class Container>
typename enable_if<
  !is_ostream<Container>::value
, join_wrapper<CharT, CharT, Container>
>::type
join(const Container& container, CharT glue)
{ return join_wrapper<CharT, CharT, Container>(container, glue); }

#if __cplusplus >= 201103L
template<class CharT = char, class Container>
#else
template<class CharT, class Container>
#endif
join_wrapper<CharT, CharT, Container> join(const Container& container)
{ return join_wrapper<CharT, CharT, Container>(container, ','); }

template<class Container>
join_wrapper<char, char, Container> join(const Container& container)
{ return join_wrapper<char, char, Container>(container, ','); }

template<class CharT, class Container>
typename enable_if<
  !is_ostream<Container>::value
, join_wrapper<CharT, const CharT*, Container, true>
>::type
join(const Container& container, const CharT* glue, std::streamsize size)
{ return join_wrapper<CharT, const CharT*, Container, true>(container, glue, size); }

}

namespace iostreams {
  using ::falcon::iostreams::join;
}

}

#endif
