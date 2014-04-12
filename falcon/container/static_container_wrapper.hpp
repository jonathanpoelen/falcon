#ifndef FALCON_CONTAINER_STATIC_CONTAINER_WRAPPER_HPP
#define FALCON_CONTAINER_STATIC_CONTAINER_WRAPPER_HPP

#include <iterator>

namespace falcon{

template<typename _Container, typename _Traits = _Container>
struct static_container_wrapper
{
	typedef _Container container_type;
	typedef typename _Traits::iterator iterator;

private:
	typedef std::iterator_traits<iterator> __type_traits;

public:
	typedef typename __type_traits::value_type value_type;
	typedef typename __type_traits::pointer pointer;
	typedef typename __type_traits::reference reference;

public:
	static iterator begin()
	{ return _Traits::begin(); }

  static iterator end()
	{ return _Traits::end(); }
};

}

#endif
