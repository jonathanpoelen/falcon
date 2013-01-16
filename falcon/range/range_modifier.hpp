#ifndef _FALCON_RANGE_RANGE_MODIFIER_HPP
#define _FALCON_RANGE_RANGE_MODIFIER_HPP

#include <algorithm>
#include <falcon/container/container_wrapper.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {

/**
 * \brief Wrapper for use operators affect a value in a container
 *
 * make_range_modifier(container) += 8;
 * make_range(first, last).modifier() -= 7;
 */
template<typename _Range, typename _Traits = range_access_traits<_Range> >
struct range_modifier
: container_wrapper<_Range, _Traits>
{
	typedef _Range container_type;
	typedef typename container_wrapper<_Range, _Traits>::iterator iterator;
	typedef typename container_wrapper<_Range, _Traits>::value_type value_type;
	typedef typename container_wrapper<_Range, _Traits>::difference_type difference_type;

	range_modifier(container_type& container)
	: container_wrapper<_Range, _Traits>(container)
	{}

	difference_type size() const
	{ this->end() - this->begin(); }

	template<typename _T>
	range_modifier& operator=(const range_modifier& other)
	{
		this->base() = other.base();
		return *this;
	}

	template<typename _T>
	range_modifier& operator=(const _Range& other)
	{
		this->base() = other;
		return *this;
	}

	template<typename _T>
	range_modifier& operator=(const _T& v)
	{
		assign<>(v);
		return *this;
	}

	template<typename _T>
	void assign(const _T& v)
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			*first = v;
	}

	template<typename _InputIterator>
	void assign(_InputIterator first, _InputIterator last)
	{
		for (iterator result = this->begin(); first != last; ++first, ++result)
			*result = *first;
	}

	template<typename _Functor>
	range_modifier& for_each(_Functor func) const
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			func(*first);
		return *this;
	}

	template<typename _Functor>
	range_modifier& for_each(_Functor func)
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			func(*first);
		return *this;
	}

	template<typename _Functor, typename _T>
	range_modifier& for_each(_Functor func, const _T& x)
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			func(*first, x);
		return *this;
	}

	template<typename _Functor, typename _T>
	range_modifier& for_each(_Functor func, const _T& x) const
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			func(*first, x);
		return *this;
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _Functor, typename... _Args>
	range_modifier& for_each(_Functor func, const _Args&... x) const
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			func(*first, x...);
		return *this;
	}

	template<typename _Functor, typename... _Args>
	range_modifier& for_each(_Functor func, const _Args&... x)
	{
		for (iterator first = this->begin(), last = this->end(); first != last; ++first)
			func(*first, x...);
		return *this;
	}
#endif

	/**
	 * @brief  Find the first element in a sequence for which a predicate is true.
	 * @param  predicate   A predicate.
	 * @return   The first iterator @c i in the range such that @p predicate(*i) is true, or @p end() if no such iterator exists.
	 */
	template<typename _Predicate>
	inline iterator find_if(_Predicate predicate) const
	{
		return std::find_if(this->begin(), this->end(), predicate);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
private:
	template<typename _Predicate>
	struct __predicat_not
	{
		_Predicate& predicate;
		__predicat_not(_Predicate & pred)
		: predicate(pred)
		{}

		bool operator()(const value_type& x) const
		{ return !predicate(x); }
	};
public:
#endif

	/**
	 * @brief  Find the first element in a sequence for which a predicate is false.
	 * @param  predicate   A predicate.
	 * @return   The first iterator @c i in the range such that @p predicate(*i) is false, or @p end() if no such iterator exists.
	 */
	template<typename _Predicate>
	inline iterator find_if_not(_Predicate predicate) const
	{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		return std::find_if_not(this->begin(), this->end(), predicate);
#else
		return std::find_if(this->begin(), this->end(),
												__predicat_not<_Predicate>(predicate));
#endif
	}

	/**
	 * @brief Checks that a predicate is true for all the elements of a sequence.
	 * @param  predicate    A predicate.
	 * @return  True if the check is true, false otherwise.
	 */
	template<typename _Predicate>
	inline bool all_of(_Predicate predicate) const
	{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		return std::all_of(this->first(), this->end(), predicate);
#else
		return this->end() == find_if_not(predicate);
#endif
	}

	/**
	 * @brief  Checks that a predicate is false for all the elements of a sequence.
	 * @param  predicate    A predicate.
	 * @return  True if the check is true, false otherwise.
	 */
	template<typename _Predicate>
	inline bool none_of(_Predicate predicate) const
	{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		return std::none_of(this->first(), this->end(), predicate);
#else
		return this->end() == find_if(predicate);
#endif
	}

	/**
	 * @brief  Checks that a predicate is false for at least an element of a sequence.
	 * @param  predicate    A predicate.
	 * @return  True if the check is true, false otherwise.
	 */
	template<typename _Predicate>
	inline bool any_of(_Predicate predicate) const
	{ return !none_of(predicate); }
};

template<typename _Container>
range_modifier<_Container> make_range_modifier(_Container& container)
{
	return range_modifier<_Container>(container);
}

#define _FALCON_CREATE_RANGE_FUNCTION_OPERATOR(op)\
	template<typename _Range, typename _Traits, typename _T>\
	range_modifier<_Range, _Traits> operator op(range_modifier<_Range, _Traits> range, const _T& v)\
	{\
		for (typename range_modifier<_Range, _Traits>::iterator first = range.begin(), last = range.end(); first != last; ++first)\
			*first op v;\
		return range;\
	}

_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(+=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(-=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(*=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(/=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(|=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(&=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(^=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(%=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(>>=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(<<=)

#undef _FALCON_CREATE_RANGE_FUNCTION_OPERATOR

#define _FALCON_CREATE_RANGE_FUNCTION_OPERATOR(op)\
	template<typename _Range, typename _Traits>\
	range_modifier<_Range, _Traits> operator op(range_modifier<_Range, _Traits> range)\
	{\
		for (typename range_modifier<_Range, _Traits>::iterator first = range.begin(), last = range.end(); first != last; ++first)\
			op(*first);\
		return range;\
	}\
	template<typename _Range, typename _Traits>\
	range_modifier<_Range, _Traits> operator op(range_modifier<_Range, _Traits> range, int)\
	{\
		for (typename range_modifier<_Range, _Traits>::iterator first = range.begin(), last = range.end(); first != last; ++first)\
			op(*first);\
		return range;\
	}

_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(++)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(--)

#undef _FALCON_CREATE_RANGE_FUNCTION_OPERATOR

template<typename _Range, typename _Traits, typename _T>
bool operator==(range_modifier<_Range, _Traits> range, const _T v)
{
	typedef typename range_modifier<_Range, _Traits>::iterator iterator;
	for (iterator first = range.begin(), last = range.end(); first != last; ++first)
	{
		if (*first != v)
			return false;
	}
	return true;
}

template<typename _Range, typename _Traits, typename _T>
bool operator<(range_modifier<_Range, _Traits> range, const _T v)
{
	typedef typename range_modifier<_Range, _Traits>::iterator iterator;
	for (iterator first = range.begin(), last = range.end(); first != last; ++first)
	{
		if (*first >= v)
			return false;
	}
	return true;
}

template<typename _Range, typename _Traits, typename _T>
bool operator>(range_modifier<_Range, _Traits> range, const _T v)
{
	typedef typename range_modifier<_Range, _Traits>::iterator iterator;
	for (iterator first = range.begin(), last = range.end(); first != last; ++first)
	{
		if (*first <= v)
			return false;
	}
	return true;
}

template<typename _Range, typename _Traits, typename _T>
bool operator!=(range_modifier<_Range, _Traits> range, const _T v)
{ return !(range == v); }

template<typename _Range, typename _Traits, typename _T>
bool operator<=(range_modifier<_Range, _Traits> range, const _T v)
{ return !(range > v); }

template<typename _Range, typename _Traits, typename _T>
bool operator>=(range_modifier<_Range, _Traits> range, const _T v)
{ return !(range < v); }

}

#endif
