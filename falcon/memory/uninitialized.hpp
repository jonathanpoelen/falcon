#ifndef FALCON_MEMORY_UNINITIALIZED_HPP
#define FALCON_MEMORY_UNINITIALIZED_HPP

#include <falcon/memory/construct.hpp>
#include <falcon/memory/destroy.hpp>

#include <iterator>

namespace falcon {

namespace aux_ {

	template<bool TrivialValueType>
	struct uninitialized_emplace
	{
		template<class ForwardIterator, class... Args>
		static void uninit_emplace(ForwardIterator first, ForwardIterator last, Args&&... args)
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
	struct uninitialized_emplace<true>
	{
		template<class ForwardIterator, class... Args>
		static void uninit_emplace(ForwardIterator first, ForwardIterator last, Args&&...args)
		{
			for (; first != last; ++first) {
				construct(std::addressof(*first), args...);
			}
		}
	};
}

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

	aux_::uninitialized_emplace<
		std::has_trivial_default_constructor<ValueType>::value
	>::uninit_emplace(first, last, std::forward<Args>(args)...);
}

}

#endif
