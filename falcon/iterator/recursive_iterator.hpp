#ifndef _FALCON_ITERATOR_RECURSIVE_ITERATOR_HPP
#define _FALCON_ITERATOR_RECURSIVE_ITERATOR_HPP

#include <tuple>
#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/iterator/subrange_access_iterator.hpp>
#include <falcon/container/range_access_traits.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/parameter/pack_element.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/arg/arg.hpp>
#include <falcon/type_traits/dimension.hpp>
#include <falcon/utility/maker.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterators, typename _ComparisonParameterTag = last_parameter_index_tag<1>>
class basic_recursive_iterator;

template<typename _Iterator, typename _AccessTrait = range_access_traits<typename std::iterator_traits<_Iterator>::value_type>>
struct recursive_iterator_access_adapter
{
	typedef _Iterator iterator;
	typedef std::pair<_Iterator, _Iterator> type;
	typedef _AccessTrait access_traits;
};

template<typename _Iterator>
struct iterator_to_recursive_iterator_access_adapter
{ typedef recursive_iterator_access_adapter<_Iterator> type; };

template<typename _Iterator, typename _AccessTrait>
struct iterator_to_recursive_iterator_access_adapter
<recursive_iterator_access_adapter<_Iterator, _AccessTrait>>
{ typedef recursive_iterator_access_adapter<_Iterator, _AccessTrait> type; };

namespace detail {

	template <typename _ComparisonParameterTag, typename... _Iterators>
	struct recursive_iterator_base
	{
		typedef parameter_pack<_Iterators...> __parameter;

		typedef typename parameter::pack_modifier<
			iterator_to_recursive_iterator_access_adapter,
			typename parameter::pack_element<
				__parameter,
				typename build_parameter_index<sizeof...(_Iterators) - 1>::type
			>::type
		>::type __parameter_adapter;

		typedef typename parameter_element<
			sizeof...(_Iterators) - 1,
			__parameter
		>::type __last_iterator;

		typedef typename parameter::pack_add_right<
			typename parameter::pack_use_type<__parameter_adapter>::type,
			std::pair<__last_iterator, __last_iterator>
		>::type __parameter_pair_iterator;

		typedef typename parameter::pack_add_left<
			__parameter_pair_iterator,
			bool
		>::type __parameter_tuple;

		typedef typename parameter_pack_to_tuple<__parameter_tuple>::type __tuple;

		typedef typename std::iterator_traits<__last_iterator> __traits;

		typedef typename iterator_handler_types<
			basic_recursive_iterator<__parameter, _ComparisonParameterTag>,
			__tuple,
			std::forward_iterator_tag,
			typename __traits::value_type,
			typename __traits::difference_type,
			typename __traits::pointer,
			typename __traits::reference
		>::base base;
	};

}


template<typename _Tuple, typename _ParameterAdapter, std::size_t _Idx>
struct __recursive_iterator_move
{
	static void __update(_Tuple& t)
	{
		typedef typename parameter_element<_Idx-1, _ParameterAdapter>::type::access_traits __access;
		if (std::get<0>(t)) {
			std::get<_Idx+1>(t).first = __access::begin(*std::get<_Idx>(t).first);
			std::get<_Idx+1>(t).second = __access::end(*std::get<_Idx>(t).first);
		}
	}

	static void __inc(_Tuple& t)
	{
		if (++std::get<_Idx+1>(t).first == std::get<_Idx+1>(t).second)
		{
			__recursive_iterator_move<_Tuple, _ParameterAdapter, _Idx - 1>::__inc(t);
			__update(t);
		}
	}

	template<typename difference_type>
	static void __inc(_Tuple& t, difference_type n)
	{
		difference_type diff = std::get<_Idx+1>(t).second - std::get<_Idx+1>(t).first;
		if (diff < n)
		{
			__recursive_iterator_move<_Tuple, _ParameterAdapter, _Idx - 1>::__inc(t, n-diff);
			__update(t);
		}
		else
			std::get<_Idx+1>(t).first += n;
	}
};

template<typename _Tuple, typename _ParameterAdapter>
struct __recursive_iterator_move<_Tuple, _ParameterAdapter, 0>
{
	static void __inc(_Tuple& t)
	{ std::get<0>(t) = ++std::get<1>(t).first != std::get<1>(t).second; }

	template<typename difference_type>
	static void __inc(_Tuple& t, difference_type n)
	{ std::get<0>(t) = (std::get<1>(t).first += n) < std::get<1>(t).second; }
};

template<typename _Result, typename _NullElements>
struct __make_imcomplet_tuple_in_recursive_iterator;

template<typename _Result, std::size_t... _Indexes>
struct __make_imcomplet_tuple_in_recursive_iterator<
	_Result,
	parameter_index<_Indexes...>
>
{
	template<typename... _Iterators>
	static _Result __make(_Iterators... elems)
	{
		return _Result(
			false, elems..., typename std::tuple_element<_Indexes, _Result>::type()...
		);
	}
};

template<typename _Result, typename _ParameterAdapter, std::size_t _Idx, std::size_t _N>
struct __make_tuple_in_recursive_iterator
{
	template<typename... _Iterators>
	static _Result __make(_Iterators... elems)
	{
		auto& p = arg<sizeof...(_Iterators)-1>(elems...);
		if (p.first == p.second) {
			return __make_imcomplet_tuple_in_recursive_iterator<
				_Result,
				typename build_range_parameter_index<
					sizeof...(elems)+1,
					std::tuple_size<_Result>::value
				>::type
			>::__make(elems...);
		}
		typedef typename parameter_element<_Idx, _ParameterAdapter>::type::access_traits __access;
		return __make_tuple_in_recursive_iterator<_Result, _ParameterAdapter, _Idx+1, _N>
		::__make(elems..., std::make_pair<>(
			__access::begin(*p.first),
			__access::end(*p.first)
		));
	}
};

template<typename _Result, typename _ParameterAdapter, std::size_t _N>
struct __make_tuple_in_recursive_iterator<_Result, _ParameterAdapter, _N, _N>
{
	template<typename... _Iterators>
	static _Result __make(_Iterators... elems)
	{
		auto& p = arg<sizeof...(_Iterators)-1>(elems...);
		return _Result(p.first != p.second, elems...);
	}
};

template<typename _Left>
struct __make_last_iterator_in_recursive_iterator;

template<typename... _Left>
struct __make_last_iterator_in_recursive_iterator<parameter_pack<_Left...>>
{
	template<typename _Last>
	static std::tuple<bool, _Left..., std::pair<_Last, _Last>>
	__make(bool __is_valid, _Last __x)
	{
		return std::tuple<bool, _Left..., std::pair<_Last, _Last>>(
			__is_valid, _Left()..., std::pair<_Last, _Last>(__x, _Last())
		);
	}
};


template<typename _Pair>
struct __recursive_iterator_last_element_for_compare
{
	const _Pair& _p;

	__recursive_iterator_last_element_for_compare(const _Pair& x)
	: _p(x)
	{}

	bool operator==(const __recursive_iterator_last_element_for_compare& x) const
	{ return _p.first == x._p.first; }
};

template<typename _Indexes, typename _Elements, typename _Iterators>
struct __recursive_iterator_to_tuple_const_reference_type;

template<std::size_t _Index, std::size_t... _Indexes,
	typename... _Elements, typename _Iterators>
struct __recursive_iterator_to_tuple_const_reference_type<
	parameter_index<_Index, _Indexes...>,
	parameter_pack<_Elements...>,
	_Iterators
>
: __recursive_iterator_to_tuple_const_reference_type<
	parameter_index<_Indexes...>,
	parameter_pack<
		_Elements...,
		__recursive_iterator_last_element_for_compare<
			typename parameter_element<_Index, _Iterators>::type
		>
	>,
	_Iterators>
{};

template<typename... _Elements, typename _Iterators>
struct __recursive_iterator_to_tuple_const_reference_type<
	parameter_index<>,
	parameter_pack<_Elements...>,
	_Iterators
>
{ typedef std::tuple<_Elements...> __type; };

template <typename... _Iterators, typename _ComparisonParameterTag>
class basic_recursive_iterator<parameter_pack<_Iterators...>, _ComparisonParameterTag>
: public detail::recursive_iterator_base<_ComparisonParameterTag, _Iterators...>::base
{
	friend class iterator_core_access;

	typedef detail::recursive_iterator_base<_ComparisonParameterTag, _Iterators...> __detail;
	typedef typename __detail::__last_iterator __last_iterator;
	typedef typename __detail::__parameter_adapter __parameter_adapter;
	typedef typename __detail::__parameter_tuple __parameter_tuple;
	typedef typename __detail::__parameter_pair_iterator __parameter_pair_iterator;

	typedef typename __detail::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::reference reference;

	typedef iterator_type tuple_type;

public:
	basic_recursive_iterator()
	: __base(__make_imcomplet_tuple_in_recursive_iterator<
		iterator_type,
		typename build_range_parameter_index<1, sizeof...(_Iterators)+1>::type
	>::__make())
	{}

	explicit basic_recursive_iterator(iterator_type __x)
	: __base(__x)
	{}

	basic_recursive_iterator(const basic_recursive_iterator& __x)
	: __base(__x)
	{}

	explicit basic_recursive_iterator(bool __is_valid, __last_iterator __x)
	: __base(__make_last_iterator_in_recursive_iterator<
		typename parameter::pack_element<
			__parameter_pair_iterator,
			typename build_parameter_index<sizeof...(_Iterators)-1>::type
		>::type
	>::__make(__is_valid, __x))
	{}

private:
	typedef __make_tuple_in_recursive_iterator<
		iterator_type, __parameter_adapter, 0, sizeof...(_Iterators)-1
	> __maker_tuple;
	typedef typename std::tuple_element<0, iterator_type>::type __first_iterator;
	typedef std::pair<__first_iterator, __first_iterator> __first_pair;

public:
	template<typename _Container>
	explicit basic_recursive_iterator(_Container& __cont, int = 1)
	: __base(__maker_tuple::__make(std::make_pair(std::begin(__cont), std::end(__cont))))
	{}

	explicit basic_recursive_iterator(__first_iterator __first, __first_iterator __last)
	: __base(__maker_tuple::__make(__first_pair(__first, __last)))
	{}

	using __base::operator=;

	const tuple_type& tuple_impl() const
	{ return this->base_reference(); }

	tuple_type& tuple_impl()
	{ return this->base_reference(); }

	bool valid() const
	{ return std::get<0>(tuple_impl()); }

private:
	static const std::size_t __last_idx = sizeof...(_Iterators);

	const __last_iterator& get_last_iterator() const
	{ return std::get<__last_idx>(this->base_reference()).first; }

	reference dereference() const
	{ return *get_last_iterator(); }

	void increment()
	{
		__recursive_iterator_move<iterator_type, __parameter_adapter, __last_idx-1>
		::__inc(this->base_reference());
	}

	void advance(difference_type n)
	{
		__recursive_iterator_move<iterator_type, __parameter_adapter, __last_idx-1>
		::__inc(this->base_reference(), n);
	}
public:
	typedef typename parameter_index_increment<
		typename keep_parameter_index<
			typename parameter_index_or_tag_to_tag<_ComparisonParameterTag>::type,
			sizeof...(_Iterators)
		>::type
	>::type __tuple_index;
	typedef typename __recursive_iterator_to_tuple_const_reference_type<
		__tuple_index,
		parameter_pack<>,
		__parameter_tuple
	>::__type __tuple_reference_type;
	__tuple_reference_type __tuple_reference() const
	{
		return tuple_apply(__tuple_index(),
											 maker<__tuple_reference_type>(),
											 tuple_impl());
	}

	bool equal(const basic_recursive_iterator& x) const
	{ return valid() == x.valid() && (x.valid() && __tuple_reference() == x.__tuple_reference()); }

	bool less(const basic_recursive_iterator& x) const;

	basic_recursive_iterator next(difference_type n) const
	{
		basic_recursive_iterator ret(*this);
		ret.advance(n);
		return ret;
	}

public:
	bool operator==	(const __last_iterator& x) const { return get_last_iterator() == x; }
	bool operator<	(const __last_iterator& x) const { return get_last_iterator() < x; }
	bool operator!=	(const __last_iterator& x) const { return !(*this == x); }
	bool operator<=	(const __last_iterator& x) const { return !(x < *this); }
	bool operator>	(const __last_iterator& x) const { return x < *this; }
	bool operator>=	(const __last_iterator& x) const { return !(*this < x); }

	operator bool () const
	{ return valid(); }

	bool operator !() const
	{ return !valid(); }

	bool next()
	{
		this->increment();
		return valid();
	}

	bool next(difference_type n)
	{
		advance(n);
		return valid();
	}
};


template<std::size_t _Dimension, typename _Iterator, typename _ComparisonParameterTag>
struct __recursive_iterator_info
{
	template<std::size_t _N, typename _T, typename... _Elements>
	struct __recursive_iterator_info_impl
	: __recursive_iterator_info_impl<_N-1, typename subrange_access_iterator<_T>::type, _T, _Elements...>
	{};

	template<typename _T, typename... _Elements>
	struct __recursive_iterator_info_impl<0, _T, _Elements...>
	{
		typedef basic_recursive_iterator<
			typename parameter::pack_reverse<parameter_pack<_T, _Elements...>>::type,
			_ComparisonParameterTag
		> type;
	};

	typedef typename __recursive_iterator_info_impl<_Dimension-1, _Iterator>::type type;
};


/**
 * \brief create begin recursive iterator. End iterator is end first iterator. Use safe_recursive_iterator if iterator can be empty.
 * @{
 */
template<std::size_t _Dimension, typename _Container,
	typename _ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<
	_Dimension,
	typename range_access_iterator<_Container>::type,
	_ComparisonParameterTag
>::type
recursive_iterator(_Container& container,
									 _ComparisonParameterTag = _ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		_Dimension,
		typename range_access_iterator<_Container>::type,
		_ComparisonParameterTag
	>::type(container, 1);
}

template<typename _Container,
	typename _ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<
	dimension<_Container>::value,
	typename range_access_iterator<_Container>::type,
	_ComparisonParameterTag
>::type
recursive_iterator(_Container& container,
									 _ComparisonParameterTag = _ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		dimension<_Container>::value,
		typename range_access_iterator<_Container>::type,
		_ComparisonParameterTag
	>::type(container, 1);
}

template<std::size_t _Dimension, typename _Iterator,
	typename _ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<_Dimension, _Iterator, _ComparisonParameterTag>::type
recursive_iterator(_Iterator first, _Iterator get_last,
									 _ComparisonParameterTag = _ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		_Dimension,
		_Iterator,
		_ComparisonParameterTag
	>::type(first, get_last);
}

template<typename _Iterator,
	typename _ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<
	dimension<_Iterator>::value,
	_Iterator,
	_ComparisonParameterTag
>::type
recursive_iterator(_Iterator first, _Iterator get_last,
									 _ComparisonParameterTag = _ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		dimension<_Iterator>::value,
		_Iterator,
		_ComparisonParameterTag
	>::type(first, get_last);
}
//@}

}
}

#endif