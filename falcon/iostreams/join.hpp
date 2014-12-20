#ifndef FALCON_IOSTREAM_JOIN_HPP
#define FALCON_IOSTREAM_JOIN_HPP

#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/disable_if.hpp>
#include <falcon/type_traits/is_ios.hpp>

#include <iosfwd>


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

	iterator_type _first;
	iterator_type _last;
  value_type _glue;
};

template<class CharT, class CharOrStringT, class ForwardIterator>
struct join_iterator_wrapper<CharT, CharOrStringT, ForwardIterator, true>
{
	typedef CharOrStringT value_type;
	typedef ForwardIterator iterator_type;

	iterator_type _first;
	iterator_type _last;
  value_type _glue;
	std::streamsize _size;
};

template<class CharT, class Traits, class CharOrStringT, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
operator<<(
  std::basic_ostream<CharT, Traits>& os
, join_iterator_wrapper<CharT, CharOrStringT, ForwardIterator, false> wrapper)
{ return join(
  os
, wrapper._first
, wrapper._last
, wrapper._glue); }

template<class CharT, class Traits, class CharOrStringT, class ForwardIterator>
std::basic_ostream<CharT, Traits>&
operator<<(
  std::basic_ostream<CharT, Traits>& os
, join_iterator_wrapper<CharT, CharOrStringT, ForwardIterator, true> wrapper)
{ return join(
  os
, wrapper._first
, wrapper._last
, wrapper._glue
, wrapper._size); }

template<class CharT, class ForwardIterator>
join_iterator_wrapper<CharT, const CharT*, ForwardIterator>
join(ForwardIterator first, ForwardIterator last, const CharT* glue)
{ return {first, last, glue}; }

template<class CharT, class ForwardIterator>
join_iterator_wrapper<CharT, CharT, ForwardIterator>
join(ForwardIterator first, ForwardIterator last, CharT glue)
{ return {first, last, glue}; }

template<class ForwardIterator>
join_iterator_wrapper<char, char, ForwardIterator>
join(ForwardIterator first, ForwardIterator last)
{ return {first, last, ','}; }

template<class CharT, class ForwardIterator>
join_iterator_wrapper<CharT, const CharT*, ForwardIterator, true>
join(
  ForwardIterator first
, ForwardIterator last
, const CharT* glue
, std::streamsize size)
{ return {first, last, glue, size}; }


template<
  class CharT
, class CharOrStringT
, class Container
, bool SpecifiedSize = false>
struct join_wrapper
{
	typedef CharOrStringT value_type;
	typedef const Container& container_type;

	container_type _container;
	value_type _glue;
};

template<class CharT, class CharOrStringT, class Container>
struct join_wrapper<CharT, CharOrStringT, Container, true>
{
	typedef CharOrStringT value_type;
	typedef const Container& container_type;

	container_type _container;
	value_type _glue;
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
typename disable_if_c<
  is_ostream<Container>
, join_wrapper<CharT, const CharT*, Container>
>::type
join(const Container& container, const CharT* glue)
{ return {container, glue}; }

template<class CharT, class Container>
disable_if_c_t<
  is_ostream<Container>
, join_wrapper<CharT, CharT, Container>
>
join(const Container& container, CharT glue)
{ return {container, glue}; }

template<class CharT = char, class Container>
join_wrapper<CharT, CharT, Container> join(const Container& container)
{ return {container, ','}; }

template<class Container>
join_wrapper<char, char, Container> join(const Container& container)
{ return {container, ','}; }

template<class CharT, class Container>
disable_if_c_t<
  is_ostream<Container>
, join_wrapper<CharT, const CharT*, Container, true>
>
join(const Container& container, const CharT* glue, std::streamsize size)
{ return {container, glue, size}; }

}

namespace iostreams {
  using ::falcon::iostreams::join;
}

}

#endif
