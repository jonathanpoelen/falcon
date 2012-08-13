#ifndef _FALCON_MEMORY_UNINITIALIZED_HPP
#define _FALCON_MEMORY_UNINITIALIZED_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
# include <iterator>
#endif
#include <falcon/c++/reference.hpp>
#include <falcon/memory/construct.hpp>
#include <falcon/memory/destroy.hpp>
#include <falcon/preprocessor/move.hpp>

namespace falcon {

template<bool _TrivialValueType>
struct __uninitialized_emplace
{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _ForwardIterator, typename... _Args>
	static void __uninit_emplace(_ForwardIterator __first, _ForwardIterator __last, _Args&&... __args)
	{
		_ForwardIterator __cur = __first;
		try
		{
			for (; __cur != __last; ++__cur)
				construct(std::addressof(*__cur), std::forward<_Args>(__args)...);
		}
		catch(...)
		{
			destroy<>(__first, __cur);
			throw;
		}
	}
#else
	template<typename _ForwardIterator, typename _Tp>
	static void __uninit_emplace(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __x)
	{
		_ForwardIterator __cur = __first;
		try
		{
			for (; __cur != __last; ++__cur)
				construct(*__cur, __x);
		}
		catch(...)
		{
			destroy<>(__first, __cur);
			throw;
		}
	}
#endif
};

template<>
struct __uninitialized_emplace<true>
{
	template<typename _ForwardIterator, typename _Tp>
	static void __uninit_emplace(_ForwardIterator __first, _ForwardIterator __last, CPP_RVALUE_OR_CONST_REFERENCE(_Tp) __x)
	{
		for (; __first != __last; ++__first)
			*__first = FALCON_MOVE(__x);
	}
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
/**
 *  @brief Emplace values args into the range [first,last).
 *  @param first  An input iterator.
 *  @param last   An input iterator.
 *  @param args   The source values.
 *  @return Nothing.
 */
template<typename _ForwardIterator, typename... _Args>
inline void uninitialized_emplace(_ForwardIterator __first, _ForwardIterator __last, _Args&&... __args)
{
	typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;

	__uninitialized_emplace<
		std::has_trivial_default_constructor<_ValueType>::value
	>::__uninit_emplace(__first, __last, std::forward<_Args>(__args)...);
}
#else
/**
 *  @brief Emplace values args into the range [first,last).
 *  @param first  An input iterator.
 *  @param last   An input iterator.
 *  @param __x   The source value.
 *  @return Nothing.
 */
template<typename _ForwardIterator, typename _Tp>
inline void uninitialized_emplace(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __x)
{
	__uninitialized_emplace<false>::__uninit_emplace(__first, __last, __x);
}
#endif

}

#endif