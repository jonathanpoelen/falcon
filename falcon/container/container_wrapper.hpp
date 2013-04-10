#ifndef _FALCON_CONTAINER_CONTAINER_WRAPPER
#define _FALCON_CONTAINER_CONTAINER_WRAPPER

#include <iterator>
#include <falcon/container/range_access_traits.hpp>

namespace falcon{

template<typename _Container, typename _Access = range_access_traits<_Container> >
struct container_wrapper
{
	typedef _Container container_type;
	typedef _Access access_type;
	typedef typename _Access::iterator iterator;

private:
	typedef std::iterator_traits<iterator> __type_traits;

public:
	typedef typename __type_traits::value_type value_type;
	typedef typename __type_traits::pointer pointer;
	typedef typename __type_traits::reference reference;
	typedef typename __type_traits::difference_type difference_type;


private:
	container_type* _container;
	_Access _access;


public:
	container_wrapper(container_type& container)
	: _container(&container)
	, _access()
	{}

	container_wrapper(container_type& container, const access_type& traits)
	: _container(&container)
	, _access(traits)
	{}

#if __cplusplus > 201100L
	template<typename... _Args>
	container_wrapper(container_type& container, _Args&&... argtraits)
	: _container(&container)
	, _access(std::move(argtraits)...)
	{}
#endif

	iterator begin() const
	{ return _access.begin(base()); }

	iterator end() const
	{ return _access.end(base()); }

	value_type& operator[](difference_type n)
	{ return *(begin() + n); }

	void swap(container_wrapper& other)
	{
		std::swap(_access, other._access);
		std::swap(_container, other._container);
	}

	operator container_type&() const
	{ return base(); }

	container_type& base() const
	{ return *_container; }

	container_type& access()
	{ return _access; }

	const container_type& access() const
	{ return _access; }
};

template<typename _Container, typename _Iterator>
struct build_container_wrapper
{
	typedef container_wrapper<
		_Container,
		range_access_traits<_Container, _Iterator>
	> type;
};

}

#endif