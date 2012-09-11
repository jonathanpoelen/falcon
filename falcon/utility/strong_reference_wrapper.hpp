#ifndef _FALCON_UTILITY_STRONG_REFERENCE_WRAPPER_HPP
#define _FALCON_UTILITY_STRONG_REFERENCE_WRAPPER_HPP

#include <falcon/functional/invoke.hpp>

namespace falcon {

template<typename _Tp>
class strong_reference_wrapper
{
	_Tp& _M_data;

public:
	typedef _Tp type;

	strong_reference_wrapper(_Tp& __indata)
	: _M_data(__indata)
	{ }

	strong_reference_wrapper(_Tp&&) = delete;

	strong_reference_wrapper(const strong_reference_wrapper<_Tp>& __inref):
	_M_data(__inref._M_data)
	{ }

	strong_reference_wrapper& operator=(_Tp& __inref)
	{
		_M_data = __inref;
		return *this;
	}

	operator const _Tp&() const
	{ return this->get(); }

	operator _Tp&()
	{ return this->get(); }

	const _Tp& get() const
	{ return *_M_data; }

	_Tp& get()
	{ return *_M_data; }

	template<typename... _Args>
	typename std::result_of<_Tp&(_Args&&...)>::type
	operator()(_Args&&... __args) const
	{
		return invoke(get(), std::forward<_Args>(__args)...);
	}

	template<typename... _Args>
	typename std::result_of<_Tp&(_Args&&...)>::type
	operator()(_Args&&... __args)
	{
		return invoke(get(), std::forward<_Args>(__args)...);
	}
};


/// Denotes a reference should be taken to a variable.
template<typename _Tp>
inline strong_reference_wrapper<_Tp>
sref(_Tp& __t)
{ return strong_reference_wrapper<_Tp>(__t); }

/// Denotes a const reference should be taken to a variable.
template<typename _Tp>
inline strong_reference_wrapper<const _Tp>
csref(const _Tp& __t)
{ return strong_reference_wrapper<const _Tp>(__t); }

template<typename _Tp>
void sref(const _Tp&&) = delete;

template<typename _Tp>
void csref(const _Tp&&) = delete;

/// Partial specialization.
template<typename _Tp>
inline strong_reference_wrapper<_Tp>
sref(strong_reference_wrapper<_Tp> __t)
{ return sref(__t.get()); }

/// Partial specialization.
template<typename _Tp>
inline strong_reference_wrapper<const _Tp>
csref(strong_reference_wrapper<_Tp> __t)
{ return csref(__t.get()); }

}

#endif