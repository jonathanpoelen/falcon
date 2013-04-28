#ifndef _FALCON_ALGORITHM_RECURSIVE_FOR_EACH_HPP
#define _FALCON_ALGORITHM_RECURSIVE_FOR_EACH_HPP

#if __cplusplus >= 201103L
# include <initializer_list>
#endif
#include <falcon/c++/constexpr.hpp>
#include <falcon/iterator/subrange_access_iterator.hpp>
#include <falcon/type_traits/dimension.hpp>
#include <falcon/type_traits/ignore.hpp>
#include <falcon/preprocessor/move.hpp>

namespace falcon {
namespace algorithm {

template <typename _Function, typename _T, bool _Break = true>
struct __break_off
{
	_Function function;
	const _T& value;

#if __cplusplus < 201103L
	__break_off(const _Function& function, const _T& value)
	: function(function)
	, value(value)
	{}
#endif
};

template <typename _Function, typename _Functor, bool _Break = true>
struct __break_if
{
	_Function function;
	_Functor functor;

#if __cplusplus < 201103L
	__break_if(const _Function& function, const _T& functor)
	: function(function)
	, functor(functor)
	{}
#endif
};

template <typename _Function, typename _T, bool _Break = true>
struct __return_off
{
	_Function function;
	const _T& value;

#if __cplusplus < 201103L
	__return_off(const _Function& function, const _T& value)
	: function(function)
	, value(value)
	{}
#endif
};

template <typename _Function, typename _Functor, bool _Break = true>
struct __return_if
{
	_Function function;
	_Functor functor;

#if __cplusplus < 201103L
	__return_if(const _Function& function, const _T& functor)
	: function(function)
	, functor(functor)
	{}
#endif
};

#if __cplusplus >= 201103L
template <typename _Function, typename _T>
inline __break_off<_Function, _T> break_off(_Function&& function, const _T& value)
{
	return {function, value};
}

template <typename _Function, typename _T>
inline __break_off<_Function, _T, false> break_off_not(_Function&& function, const _T& value)
{
	return {function, value};
}

template <typename _Function, typename _Functor>
inline __break_if<_Function, _Functor> break_if(_Function&& function, _Functor&& functor)
{
	return {function, functor};
}

template <typename _Function, typename _Functor>
inline __break_if<_Function, _Functor, false> break_if_not(_Function&& function, _Functor&& functor)
{
	return {function, functor};
}
#else
template <typename _Function, typename _T>
inline __break_off<_Function, _T> break_off(_Function function, const _T& value)
{
	return __break_off<_Function, _T>(function, value);
}

template <typename _Function, typename _T>
inline __break_off<_Function, _T, false> break_off_not(_Function function, const _T& value)
{
	return __break_off<_Function, _T, false>(function, value);
}

template <typename _Function, typename _Functor>
inline __break_if<_Function, _Functor> break_if(_Function function, _Functor functor)
{
	return __break_if<_Function, _Functor>(function, functor);
}

template <typename _Function, typename _Functor>
inline __break_if<_Function, _Functor, false> break_if_not(_Function function, _Functor functor)
{
	return __break_if<_Function, _Functor, false>(function, functor);
}
#endif

#if __cplusplus >= 201103L
template <typename _Function, typename _T>
inline __return_off<_Function, _T> return_off(_Function&& function, const _T& value)
{
	return {function, value};
}

template <typename _Function, typename _T>
inline __return_off<_Function, _T, false> return_off_not(_Function&& function, const _T& value)
{
	return {function, value};
}

template <typename _Function, typename _Functor>
inline __return_if<_Function, _Functor> return_if(_Function&& function, _Functor&& functor)
{
	return {function, functor};
}

template <typename _Function, typename _Functor>
inline __return_if<_Function, _Functor, false> return_if_not(_Function&& function, _Functor&& functor)
{
	return {function, functor};
}
#else
template <typename _Function, typename _T>
inline __return_off<_Function, _T> return_off(_Function function, const _T& value)
{
	return __return_off<_Function, _T>(function, value);
}

template <typename _Function, typename _T>
inline __return_off<_Function, _T, false> return_off_not(_Function function, const _T& value)
{
	return __return_off<_Function, _T, false>(function, value);
}

template <typename _Function, typename _Functor>
inline __return_if<_Function, _Functor> return_if(_Function function, _Functor functor)
{
	return __return_if<_Function, _Functor>(function, functor);
}

template <typename _Function, typename _Functor>
inline __return_if<_Function, _Functor, false> return_if_not(_Function function, _Functor functor)
{
	return __return_if<_Function, _Functor, false>(function, functor);
}
#endif

template <typename _Iterator, std::size_t _Dimension>
struct __recursive_for_each
{
	template<typename _Function>
	static void for_each(_Iterator first, _Iterator last, _Function& f)
	{
		for (; first != last; ++first)
			__recursive_for_each<typename subrange_access_iterator<_Iterator>::type, _Dimension-1>::for_each(begin(*first), end(*first), f);
	}

	template<typename _Function, typename _T, bool _Break>
	static bool for_each(_Iterator first, _Iterator last, __return_off<_Function, _T, _Break>& w)
	{
		for (; first != last; ++first) {
			if (!__recursive_for_each<typename subrange_access_iterator<_Iterator>::type, _Dimension-1>::for_each(begin(*first), end(*first), w))
				return false;
		}
		return true;
	}

	template<typename _Function, typename _Functor, bool _Break>
	static bool for_each(_Iterator first, _Iterator last, __return_if<_Function, _Functor, _Break>& w)
	{
		for (; first != last; ++first) {
			if (!__recursive_for_each<typename subrange_access_iterator<_Iterator>::type, _Dimension-1>::for_each(begin(*first), end(*first), w))
				return false;
		}
		return true;
	}
};

template <typename _Iterator>
struct __recursive_for_each<_Iterator, 0>
{
	template<typename _Function>
	static void for_each(_Iterator first, _Iterator last, _Function& f)
	{
		for (; first != last; ++first) {
			f(*first);
		}
	}

	template<typename _Function, typename _T>
	static void for_each(_Iterator first, _Iterator last, __break_off<_Function, _T, true>& w)
	{
		for (; first != last && *first != w.value; ++first) {
			w.function(*first);
		}
	}

	template<typename _Function, typename _T>
	static void for_each(_Iterator first, _Iterator last, __break_off<_Function, _T, false>& w)
	{
		for (; first != last && *first == w.value; ++first) {
			w.function(*first);
		}
	}

	template<typename _Function, typename _Functor>
	static void for_each(_Iterator first, _Iterator last, __break_if<_Function, _Functor, true>& w)
	{
		for (; first != last && w.functor(*first); ++first) {
			w.function(*first);
		}
	}

	template<typename _Function, typename _Functor>
	static void for_each(_Iterator first, _Iterator last, __break_if<_Function, _Functor, false>& w)
	{
		for (; first != last && !w.functor(*first); ++first) {
			w.function(*first);
		}
	}

	template<typename _Function, typename _T>
	static bool for_each(_Iterator first, _Iterator last, __return_off<_Function, _T, true>& w)
	{
		for (; first != last; ++first) {
			if (*first == w.value)
				return false;
			w.function(*first);
		}
		return true;
	}

	template<typename _Function, typename _T>
	static bool for_each(_Iterator first, _Iterator last, __return_off<_Function, _T, false>& w)
	{
		for (; first != last; ++first) {
			if (*first != w.value)
				return false;
			w.function(*first);
		}
		return true;
	}

	template<typename _Function, typename _Functor>
	static bool for_each(_Iterator first, _Iterator last, __return_if<_Function, _Functor, true>& w)
	{
		for (; first != last; ++first) {
			if (!w.functor(*first))
				return false;
			w.function(*first);
		}
		return true;
	}

	template<typename _Function, typename _Functor>
	static bool for_each(_Iterator first, _Iterator last, __return_if<_Function, _Functor, false>& w)
	{
		for (; first != last; ++first) {
			if (w.functor(*first))
				return false;
			w.function(*first);
		}
		return true;
	}
};

template <std::size_t _Dimension = -1ul, typename _Iterator, typename _Function>
_Function recursive_for_each(_Iterator first, _Iterator last, _Function f)
{
	typedef _Iterator& iterator;
	__recursive_for_each<iterator, _Dimension == -1ul ? dimension<decltype(*std::declval<_Iterator>())>::value : _Dimension>::for_each(first, last, f);
	return FALCON_MOVE(f);
}

template <std::size_t _Dimension = -1ul, typename _Container, typename _Function>
_Function recursive_for_each(_Container& container, _Function f)
{
	typedef typename range_access_iterator<_Container>::type iterator;
	__recursive_for_each<iterator, (_Dimension == -1ul ? dimension<_Container>::value : _Dimension) - 1>::for_each(begin(container), end(container), f);
	return FALCON_MOVE(f);
}

#if __cplusplus >= 201103L
template <std::size_t _Dimension = -1ul, typename _T, typename _Function>
_Function recursive_for_each(std::initializer_list<_T> list, _Function f)
{
	__recursive_for_each<typename std::initializer_list<_T>::iterator, (_Dimension == -1ul ? dimension<std::initializer_list<_T> >::value : _Dimension) - 1>::for_each(begin(list), end(list), f);
	return FALCON_MOVE(f);
}
#endif

template<typename _Preface, typename _Function, typename _Postface, std::size_t _Dimension>
class __recursive_intermediate
{
	_Preface _preface;
	_Function _functor;
	_Postface _postface;

public:
	__recursive_intermediate(_Preface preface, _Function functor, _Postface postface)
	: _preface(preface)
	, _functor(functor)
	, _postface(postface)
	{}

	template<typename _Container>
	void operator()(_Container& v)
	{
		_preface();
		recursive_for_each<_Dimension>(v, _functor);
		_postface();
	}
};

template<typename _Function, typename _Postface, std::size_t _Dimension>
class __recursive_intermediate<ignore_t, _Function, _Postface, _Dimension>
{
	_Function _functor;
	_Postface _postface;

public:
	__recursive_intermediate(const ignore_t&, _Function functor, _Postface postface)
	: _functor(functor)
	, _postface(postface)
	{}

	template<typename _Container>
	void operator()(_Container& v)
	{
		recursive_for_each<_Dimension>(v, _functor);
		_postface();
	}
};

template<typename _Preface, typename _Function, std::size_t _Dimension>
class __recursive_intermediate<_Preface, _Function, ignore_t, _Dimension>
{
	_Preface _preface;
	_Function _functor;

public:
	__recursive_intermediate(_Preface preface, _Function functor, const ignore_t&)
	: _preface(preface)
	, _functor(functor)
	{}

	template<typename _Container>
	void operator()(_Container& v)
	{
		_preface();
		recursive_for_each<_Dimension>(v, _functor);
	}
};

template<typename _Function, std::size_t _Dimension>
class __recursive_intermediate<ignore_t, _Function, ignore_t, _Dimension>
{
	_Function _functor;

public:
	__recursive_intermediate(const ignore_t&, _Function functor, const ignore_t&)
	: _functor(functor)
	{}

	template<typename _Container>
	void operator()(_Container& v)
	{
		recursive_for_each<_Dimension>(v, _functor);
	}
};

template<std::size_t _Dimension = -1ul, typename _Preface, typename _Function, typename _Postface = ignore_t>
__recursive_intermediate<_Preface, _Function, _Postface, _Dimension> recursive_intermediate(_Preface preface, _Function functor, _Postface postface = _Postface())
{
	return __recursive_intermediate<_Preface, _Function, _Postface, _Dimension>(FALCON_MOVE(preface), FALCON_MOVE(functor), FALCON_MOVE(postface));
}

}
}

#endif
