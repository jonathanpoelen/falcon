#ifndef _FALCON_MEMORY_UNINITIALIZED_HPP
#define _FALCON_MEMORY_UNINITIALIZED_HPP

#include <falcon/memory/construct.hpp>
#include <falcon/memory/destroy.hpp>

#include <iterator>

namespace falcon {

template<bool _TrivialValueType>
struct __uninitialized_emplace
{
	template<class ForwardIterator, class... Args>
	static void __uninit_emplace(ForwardIterator first, ForwardIterator last, Args&&... args)
	{
		ForwardIterator cur = first;
		try
		{
			for (; cur != last; ++cur)
				construct(std::addressof(*cur), args...);
		}
		catch(...)
		{
			destroy(first, cur);
			throw;
		}
	}
};

template<>
struct __uninitialized_emplace<true>
{
	template<class ForwardIterator, class T>
	static void __uninit_emplace(ForwardIterator first, ForwardIterator last, T && x)
	{
		for (; first != last; ++first)
			*first = x;
	}
};

/**
 *  @brief Emplace values args into the range [first,last).
 *  @param first  An input iterator.
 *  @param last   An input iterator.
 *  @param args   The source values.
 *  @return Nothing.
 */
template<class ForwardIterator, class... Args>
inline void uninitialized_emplace(ForwardIterator first, ForwardIterator last, Args&&... args)
{
	typedef typename std::iterator_traits<ForwardIterator>::value_type ValueType;

	__uninitialized_emplace<
		std::has_trivial_default_constructor<ValueType>::value
	>::__uninit_emplace(first, last, std::forward<Args>(args)...);
}

}

#endif
