#ifndef FALCON_ITERATOR_SYNCHRONIZE_ITERATOR_HPP
#define FALCON_ITERATOR_SYNCHRONIZE_ITERATOR_HPP

#include <tuple>
#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/utility/synchronizer.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/parameter/is_parameter_index_tag.hpp>
#include <falcon/type_traits/build_class.hpp>
#include <falcon/type_traits/use_type.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/type_traits/disable_if.hpp>
#include <falcon/parameter/pack_reference.hpp>

namespace falcon {
namespace iterator {

template <typename... _Iterators>
class synchronize_iterator;

namespace detail {
	template<typename... _Categories>
	class __synchronize_category;

	template<typename _Category>
	struct __rank_iterator_category
	{ static const std::size_t value = 0; };

	template<>
	struct __rank_iterator_category<std::output_iterator_tag>
	{ static const std::size_t value = 1; };

	template<>
	struct __rank_iterator_category<std::forward_iterator_tag>
	{ static const std::size_t value = 2; };

	template<>
	struct __rank_iterator_category<std::bidirectional_iterator_tag>
	{ static const std::size_t value = 3; };

	template<>
	struct __rank_iterator_category<std::random_access_iterator_tag>
	{ static const std::size_t value = 4; };

	template<typename _Category, typename _Category2, typename... _Categories>
	struct __synchronize_category<_Category, _Category2, _Categories...>
	: __synchronize_category<
		typename if_<
			(__rank_iterator_category<_Category>::value < __rank_iterator_category<_Category2>::value),
			_Category,
			_Category2
		>::type,
		_Categories...
	>
	{};

	template<typename _Category>
	struct __synchronize_category<_Category>
	{ typedef _Category iterator_category; };

	class __no_difference_type;

	template<typename... _Iterators>
	struct synchronize_base
	{
		static_assert(sizeof...(_Iterators) != 0, "none iterator");

		typedef parameter_pack<_Iterators...> __parameter_pack;

		typedef typename parameter_element<
			sizeof...(_Iterators) - 1,
			__parameter_pack
		>::type __last;

		static const bool __is_tag = is_parameter_index_or_tag<__last>();

		static_assert(__is_tag ? sizeof...(_Iterators) != 1 : true, "none iterator");

		typedef typename parameter_index_or_tag_to_tag<
			typename if_<
				__is_tag,
				__last,
				full_parameter_index_tag
			>::type
		>::type __parameter_index_tag;

		struct __iterators_with_tag
		{
			typedef typename parameter::elements<
				__parameter_pack,
				typename build_parameter_index<sizeof...(_Iterators) - 1>::type
			>::type type;
		};

		typedef typename eval_if<
			__is_tag,
			__iterators_with_tag,
			use<__parameter_pack>
		>::type __iterators;

		typedef typename keep_parameter_index<
			__parameter_index_tag,
			sizeof...(_Iterators) - (__is_tag ? 1 : 0)
		>::type __cmp_parameter_index;

		static const bool __cmp_iterators_is_full = std::is_same<
			typename build_parameter_index<sizeof...(_Iterators)>::type,
			__cmp_parameter_index
		>::value;

		typedef typename parameter::wrap<
			std::iterator_traits,
			__iterators
		>::type __pack_traits;

		template<template<class...>class _W>
		struct __subtype
		: build_class<
			synchronizer,
			typename parameter::modifier<_W, __pack_traits>::type
		>
		{};

		typedef typename iterator_handler_types<
			synchronize_iterator<_Iterators...>,
			typename build_class<synchronizer, __iterators>::type,
			typename build_class<
				__synchronize_category,
				typename parameter::modifier<use_iterator_category, __pack_traits>::type
			>::type::iterator_category,
			typename __subtype<use_value_type>::type,
			__no_difference_type,
			typename __subtype<use_pointer>::type,
			typename __subtype<use_reference>::type
		>::base base;
	};
}

/**
 * synchronize_iterator< _Iterators...[, \link indexes-tag parameter_index_tag]>
 */
template <typename... _Iterators>
class synchronize_iterator
: public detail::synchronize_base<_Iterators...>::base
{
	friend class iterator_core_access;

	typedef detail::synchronize_base<_Iterators...> __detail;
	typedef typename __detail::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename iterator_type::tuple_type iterator_tuple;

public:
	synchronize_iterator()
	: __base()
	{}

	explicit synchronize_iterator(iterator_type&& __x)
	: __base(std::forward<iterator_type>(__x), 1)
	{}

	template<typename... _Args>
	explicit synchronize_iterator(std::tuple<_Args...>&& __x)
	: __base(std::forward<iterator_type>(__x), 1)
	{}

	template<typename... _Args>
	synchronize_iterator(_Args&&... __args)
	: __base(std::piecewise_construct, std::forward<_Args>(__args)...)
	{}

	synchronize_iterator(synchronize_iterator&& __x)
	: __base(std::forward<iterator_tuple>(__x.iterators()))
	{}

	synchronize_iterator(const synchronize_iterator& __x)
	: __base(__x)
	{}

	using __base::operator=;

	iterator_tuple& iterators()
	{ return this->base_reference().tuple(); }

	const iterator_tuple& iterators() const
	{ return this->base_reference().tuple(); }

private:
	const iterator_tuple& __cmp_iterator(std::true_type) const
	{ return iterators(); }

	CPP1X_DELEGATE_FUNCTION(
		__cmp_iterator(std::false_type) const,
		to_tuple_reference(typename __detail::__cmp_parameter_index(), this->iterators())
	)

	typedef std::integral_constant<bool, __detail::__cmp_iterators_is_full> __cmp_type;

	bool equal(const synchronize_iterator& other) const
	{ return __cmp_iterator(__cmp_type()) == other.__cmp_iterator(__cmp_type()); }

	bool less(const synchronize_iterator& other) const
	{ return __cmp_iterator(__cmp_type()) < other.__cmp_iterator(__cmp_type()); }
};


template <typename _IteratorOrTag, typename... _Iterators>
typename enable_if_c<
	is_parameter_index_or_tag<_IteratorOrTag>,
	synchronize_iterator<_Iterators..., _IteratorOrTag>
>::type make_synchronize_iterator(_IteratorOrTag, _Iterators... __x)
{ return {__x...}; }

template <typename _IteratorOrTag, typename... _Iterators>
typename disable_if_c<
	is_parameter_index_or_tag<_IteratorOrTag>,
	synchronize_iterator<_Iterators..., _IteratorOrTag>
>::type make_synchronize_iterator(_IteratorOrTag __x, _Iterators... __y)
{ return {__x, __y...}; }

}
}

#endif
