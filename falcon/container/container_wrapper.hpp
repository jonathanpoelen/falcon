#ifndef _FALCON_CONTAINER_CONTAINER_WRAPPER
#define _FALCON_CONTAINER_CONTAINER_WRAPPER

#include <iterator>
#include <falcon/container/range_access_traits.hpp>

namespace falcon{

template<typename _Container, typename _Traits = range_access_traits<_Container> >
struct container_wrapper
{
	typedef _Container container_type;
	typedef typename _Traits::iterator iterator;

private:
	typedef std::iterator_traits<iterator> __type_traits;

public:
	typedef typename __type_traits::value_type value_type;
	typedef typename __type_traits::pointer pointer;
	typedef typename __type_traits::reference reference;
	typedef typename __type_traits::difference_type difference_type;


private:
	container_type* _container;


public:
	container_wrapper(container_type& container)
	: _container(&container)
	{}

	iterator begin() const
	{ return _Traits::begin(base()); }

	iterator end() const
	{ return _Traits::end(base()); }

	value_type& operator[](difference_type n)
	{ return *(begin() + n); }

	void swap(container_wrapper& other)
	{ std::swap(_container, other._container); }

	operator container_type&() const
	{ return base(); }

	container_type& base() const
	{ return *_container; }
};

template<typename _Container, typename _Iterator>
struct build_container_wrapper
{
	typedef container_wrapper<
		_Container,
		range_access_traits<_Container, _Iterator>
	> type;
};

template<typename _Container,
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<class...> class _IteratorType, typename... _ArgsIterator
#else
	template<class> class _IteratorType
#endif
>
struct build_indirect_container_wrapper
{
	typedef container_wrapper<
		_Container,
		range_access_traits<
			_Container,
			typename _IteratorType<
				typename range_access_iterator<_Container>::type
#ifdef __GXX_EXPERIMENTAL_CXX0X__
				, _ArgsIterator...
#endif
			>::type
		>
	> type;
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _Container,
	template<class...>class _IteratorType, typename... _ArgsIterator>
using indirect_container_wrapper = typename build_indirect_container_wrapper<_Container, _IteratorType, _ArgsIterator...>::type;
#endif

}

#endif