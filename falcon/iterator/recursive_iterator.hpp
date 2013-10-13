#ifndef FALCON_ITERATOR_RECURSIVE_ITERATOR_HPP
#define FALCON_ITERATOR_RECURSIVE_ITERATOR_HPP

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

#include <tuple>

namespace falcon {
namespace iterator {

template <typename Iterators, typename ComparisonParameterTag = last_parameter_index_tag<1>>
class basic_recursive_iterator;

template<typename Iterator, typename AccessTrait = range_access_traits<typename std::iterator_traits<Iterator>::value_type>>
struct recursive_iterator_access_adapter
{
	typedef Iterator iterator;
	typedef std::pair<Iterator, Iterator> type;
	typedef AccessTrait access_traits;
};

template<typename Iterator>
struct iterator_to_recursive_iterator_access_adapter
{ typedef recursive_iterator_access_adapter<Iterator> type; };

template<typename Iterator, typename AccessTrait>
struct iterator_to_recursive_iterator_access_adapter
<recursive_iterator_access_adapter<Iterator, AccessTrait>>
{ typedef recursive_iterator_access_adapter<Iterator, AccessTrait> type; };

namespace detail {

	template <typename ComparisonParameterTag, typename... Iterators>
	struct recursive_iterator_base
	{
		typedef parameter_pack<Iterators...> __parameter;

		typedef typename parameter::modifier<
			iterator_to_recursive_iterator_access_adapter,
			typename parameter::elements<
				__parameter,
				typename build_parameter_index<sizeof...(Iterators) - 1>::type
			>::type
		>::type __parameter_adapter;

		typedef typename parameter_element<
			sizeof...(Iterators) - 1,
			__parameter
		>::type __last_iterator;

		typedef typename parameter::push_back<
			typename parameter::use_type<__parameter_adapter>::type,
			std::pair<__last_iterator, __last_iterator>
		>::type __parameter_pair_iterator;

		typedef typename parameter::push_front<
			__parameter_pair_iterator,
			bool
		>::type __parameter_tuple;

		typedef typename parameter_pack_to_tuple<__parameter_tuple>::type __tuple;

		typedef typename std::iterator_traits<__last_iterator> __traits;

		typedef typename iterator_handler_types<
			basic_recursive_iterator<__parameter, ComparisonParameterTag>,
			__tuple,
			std::forward_iterator_tag,
			typename __traits::value_type,
			typename __traits::difference_type,
			typename __traits::pointer,
			typename __traits::reference
		>::base base;
	};

}


template<typename Tuple, typename ParameterAdapter, std::size_t Idx>
struct __recursive_iterator_move
{
	static void __update(Tuple& t)
	{
		typedef typename parameter_element<Idx-1, ParameterAdapter>::type::access_traits __access;
		if (get<0>(t)) {
			get<Idx+1>(t).first = __access::begin(*get<Idx>(t).first);
			get<Idx+1>(t).second = __access::end(*get<Idx>(t).first);
		}
	}

	static void __inc(Tuple& t)
	{
		if (++get<Idx+1>(t).first == get<Idx+1>(t).second)
		{
			__recursive_iterator_move<Tuple, ParameterAdapter, Idx - 1>::__inc(t);
			__update(t);
		}
	}

	template<typename difference_type>
	static void __inc(Tuple& t, difference_type n)
	{
		difference_type diff = get<Idx+1>(t).second - get<Idx+1>(t).first;
		if (diff < n)
		{
			__recursive_iterator_move<Tuple, ParameterAdapter, Idx - 1>::__inc(t, n-diff);
			__update(t);
		}
		else
			get<Idx+1>(t).first += n;
	}
};

template<typename Tuple, typename ParameterAdapter>
struct __recursive_iterator_move<Tuple, ParameterAdapter, 0>
{
	static void __inc(Tuple& t)
	{ get<0>(t) = ++get<1>(t).first != get<1>(t).second; }

	template<typename difference_type>
	static void __inc(Tuple& t, difference_type n)
	{ get<0>(t) = (get<1>(t).first += n) < get<1>(t).second; }
};

template<typename Result, typename NullElements>
struct __make_imcomplet_tuple_in_recursive_iterator;

template<typename Result, std::size_t... Indexes>
struct __make_imcomplet_tuple_in_recursive_iterator<
	Result,
	parameter_index<Indexes...>
>
{
	template<typename... Iterators>
	static Result __make(Iterators... elems)
	{
		return Result(
			false, elems..., typename std::tuple_element<Indexes, Result>::type()...
		);
	}
};

template<typename Result, typename ParameterAdapter, std::size_t Idx, std::size_t N>
struct __make_tuple_in_recursive_iterator
{
	template<typename... Iterators>
	static Result __make(Iterators... elems)
	{
		auto& p = arg<sizeof...(Iterators)-1>(elems...);
		if (p.first == p.second) {
			return __make_imcomplet_tuple_in_recursive_iterator<
				Result,
				typename build_range_parameter_index<
					sizeof...(elems)+1,
					std::tuple_size<Result>::value
				>::type
			>::__make(elems...);
		}
		typedef typename parameter_element<Idx, ParameterAdapter>::type::access_traits __access;
		return __make_tuple_in_recursive_iterator<Result, ParameterAdapter, Idx+1, N>
		::__make(elems..., std::make_pair(
			__access::begin(*p.first),
			__access::end(*p.first)
		));
	}
};

template<typename Result, typename ParameterAdapter, std::size_t N>
struct __make_tuple_in_recursive_iterator<Result, ParameterAdapter, N, N>
{
	template<typename... Iterators>
	static Result __make(Iterators... elems)
	{
		auto& p = arg<sizeof...(Iterators)-1>(elems...);
		return Result(p.first != p.second, elems...);
	}
};

template<typename Left>
struct __make_last_iterator_in_recursive_iterator;

template<typename... Left>
struct __make_last_iterator_in_recursive_iterator<parameter_pack<Left...>>
{
	template<typename Last>
	static std::tuple<bool, Left..., std::pair<Last, Last>>
	__make(bool __is_valid, Last __x)
	{
		return std::tuple<bool, Left..., std::pair<Last, Last>>(
			__is_valid, Left()..., std::pair<Last, Last>(__x, Last())
		);
	}
};


template<typename Pair>
struct __recursive_iterator_last_element_for_compare
{
	const Pair& _p;

	__recursive_iterator_last_element_for_compare(const Pair& x)
	: _p(x)
	{}

	bool operator==(const __recursive_iterator_last_element_for_compare& x) const
	{ return _p.first == x._p.first; }
};

template<typename Indexes, typename Elements, typename Iterators>
struct __recursive_iterator_to_tuple_const_reference_type;

template<std::size_t Index, std::size_t... Indexes,
	typename... Elements, typename Iterators>
struct __recursive_iterator_to_tuple_const_reference_type<
	parameter_index<Index, Indexes...>,
	parameter_pack<Elements...>,
	Iterators
>
: __recursive_iterator_to_tuple_const_reference_type<
	parameter_index<Indexes...>,
	parameter_pack<
		Elements...,
		__recursive_iterator_last_element_for_compare<
			typename parameter_element<Index, Iterators>::type
		>
	>,
	Iterators>
{};

template<typename... Elements, typename Iterators>
struct __recursive_iterator_to_tuple_const_reference_type<
	parameter_index<>,
	parameter_pack<Elements...>,
	Iterators
>
{ typedef std::tuple<Elements...> __type; };

template <typename... Iterators, typename ComparisonParameterTag>
class basic_recursive_iterator<parameter_pack<Iterators...>, ComparisonParameterTag>
: public detail::recursive_iterator_base<ComparisonParameterTag, Iterators...>::base
{
	friend class iterator_core_access;

	typedef detail::recursive_iterator_base<ComparisonParameterTag, Iterators...> __detail;
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
		typename build_range_parameter_index<1, sizeof...(Iterators)+1>::type
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
		typename parameter::elements<
			__parameter_pair_iterator,
			typename build_parameter_index<sizeof...(Iterators)-1>::type
		>::type
	>::__make(__is_valid, __x))
	{}

private:
	typedef __make_tuple_in_recursive_iterator<
		iterator_type, __parameter_adapter, 0, sizeof...(Iterators)-1
	> __maker_tuple;
	typedef typename std::tuple_element<0, iterator_type>::type __first_iterator;
	typedef std::pair<__first_iterator, __first_iterator> __first_pair;

public:
	template<typename Container>
	explicit basic_recursive_iterator(Container& __cont, int = 1)
	: __base(__maker_tuple::__make(std::make_pair(begin(__cont), end(__cont))))
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
	{ return get<0>(tuple_impl()); }

private:
	static const std::size_t __last_idx = sizeof...(Iterators);

	const __last_iterator& get_last_iterator() const
	{ return get<__last_idx>(this->base_reference()).first; }

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
			typename parameter_index_or_tag_to_tag<ComparisonParameterTag>::type,
			sizeof...(Iterators)
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
	{ return valid() == x.valid() && (x.valid() ?  __tuple_reference() == x.__tuple_reference() : true); }

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


template<std::size_t Dimension, typename Iterator, typename ComparisonParameterTag>
struct __recursive_iterator_info
{
	template<std::size_t N, typename _T, typename... Elements>
	struct __recursive_iterator_info_impl
	: __recursive_iterator_info_impl<N-1, typename subrange_access_iterator<_T>::type, _T, Elements...>
	{};

	template<typename _T, typename... Elements>
	struct __recursive_iterator_info_impl<0, _T, Elements...>
	{
		typedef basic_recursive_iterator<
			typename parameter::reverse<parameter_pack<_T, Elements...>>::type,
			ComparisonParameterTag
		> type;
	};

	typedef typename __recursive_iterator_info_impl<Dimension-1, Iterator>::type type;
};


/**
 * \brief create begin recursive iterator. End iterator is end first iterator. Use safe_recursive_iterator if iterator can be empty.
 * @{
 */
template<std::size_t Dimension, typename Container,
	typename ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<
	Dimension,
	typename range_access_iterator<Container>::type,
	ComparisonParameterTag
>::type
recursive_iterator(Container& container,
									 ComparisonParameterTag = ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		Dimension,
		typename range_access_iterator<Container>::type,
		ComparisonParameterTag
	>::type(container, 1);
}

template<typename Container,
	typename ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<
	dimension<Container>::value,
	typename range_access_iterator<Container>::type,
	ComparisonParameterTag
>::type
recursive_iterator(Container& container,
									 ComparisonParameterTag = ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		dimension<Container>::value,
		typename range_access_iterator<Container>::type,
		ComparisonParameterTag
	>::type(container, 1);
}

template<std::size_t Dimension, typename Iterator,
	typename ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<Dimension, Iterator, ComparisonParameterTag>::type
recursive_iterator(Iterator first, Iterator get_last,
									 ComparisonParameterTag = ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		Dimension,
		Iterator,
		ComparisonParameterTag
	>::type(first, get_last);
}

template<typename Iterator,
	typename ComparisonParameterTag = last_parameter_index_tag<1>>
typename __recursive_iterator_info<
	dimension<Iterator>::value,
	Iterator,
	ComparisonParameterTag
>::type
recursive_iterator(Iterator first, Iterator get_last,
									 ComparisonParameterTag = ComparisonParameterTag())
{
	return typename __recursive_iterator_info<
		dimension<Iterator>::value,
		Iterator,
		ComparisonParameterTag
	>::type(first, get_last);
}
//@}

}
}

#endif
