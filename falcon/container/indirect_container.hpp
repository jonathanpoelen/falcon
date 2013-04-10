#ifndef FALCON_CONTAINER_INDIRECT_CONTAINER_HPP
#define FALCON_CONTAINER_INDIRECT_CONTAINER_HPP

#include <functional>
#include <boost/ref.hpp>
#include <falcon/c++/extend_parameter.hpp>
#include <falcon/container/container_wrapper.hpp>
#include <falcon/iterator/get_accessor_iterator.hpp>

namespace falcon {

template<typename _Container,
	typename _Value = typename range_access_subtype<_Container>::type>
struct indirect_container_iterator_type
{
	template<typename _Iterator
#if __cplusplus > 201100L
	, typename _Proxy = use_default,
		typename _Tp = use_default, typename _Category = use_default,
		typename _Reference = use_default, typename _Distance = use_default,
		typename _Pointer = use_default
#endif
	>
	struct builder
	{
		typedef falcon::iterator::indirect_iterator<_Iterator
#if __cplusplus > 201100L
			, _Proxy, _Tp, _Category, _Reference, _Distance, _Pointer
#endif
		> type;
	};
};

template<typename _Container, typename _Value>
struct indirect_container_iterator_type<_Container, boost::reference_wrapper<_Value> >
{
	template<typename _Iterator>
	struct builder
	: falcon::iterator::build_get_accessor_iterator<_Iterator>
	{};
};

#if __cplusplus > 201100L
template<typename _Container, typename _Value>
struct indirect_container_iterator_type<_Container, std::reference_wrapper<_Value>>
{
	template<typename _Iterator>
	struct builder
	: falcon::iterator::build_get_accessor_iterator<_Iterator>
	{};
};
#endif

template<typename _Container,
	template<CPP_USE_OPTIONAL_EXTEND_PARAMETER(class)> class _IteratorBuild
	= indirect_container_iterator_type<_Container>::template builder
	CPP_OTHER_OPTIONAL_EXTEND_PARAMETER(typename, _ArgsIterator)
>
struct build_indirect_container
{
	typedef container_wrapper<
		_Container,
		range_access_traits<
			_Container,
			typename _IteratorBuild<
				typename range_access_iterator<_Container>::type
				CPP_USE_OTHER_OPTIONAL_EXTEND_PARAMETER(_ArgsIterator)
			>::type
		>
	> type;
};

template<typename _Container>
typename build_indirect_container<_Container>::type
indirect_container(_Container& cont)
{
	typedef typename build_indirect_container<_Container>::type __result_type;
	return __result_type(cont);
}

template<typename _Container, typename _Build>
typename build_indirect_container<_Container, _Build::template rebind>::type
indirect_container(_Container& cont, _Build)
{
	typedef typename build_indirect_container<_Container, _Build::template rebind>::type __result_type;
	return __result_type(cont);
}

#if __cplusplus > 201100L
template<typename _Container,
	template<class...> class _IteratorBuild = indirect_container_iterator_type<_Container>::template builder,
	typename... _ArgsIterator>
using indirect_container_wrapper = typename build_indirect_container<
	_Container, _IteratorBuild, _ArgsIterator...>::type;
#endif

}

#endif