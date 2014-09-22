#ifndef FALCON_UTILITY_STRONG_REFERENCE_WRAPPER_HPP
#define FALCON_UTILITY_STRONG_REFERENCE_WRAPPER_HPP

#include <falcon/functional/invoke.hpp>

namespace falcon {

template<typename T>
class strong_reference_wrapper
{
	T& data_;

public:
	typedef T type;

	strong_reference_wrapper(T& indata)
	: data_(indata)
	{ }

	strong_reference_wrapper(T&&) = delete;
	strong_reference_wrapper(const strong_reference_wrapper<T>&) = default;

	strong_reference_wrapper& operator=(T& inref)
	{
		data_ = inref;
		return *this;
	}

	operator const T&() const
	{ return this->get(); }

	operator T&()
	{ return this->get(); }

	const T& get() const
	{ return *data_; }

	T& get()
	{ return *data_; }

	template<typename... Args>
	typename std::result_of<T&(Args&&...)>::type
	operator()(Args&&... args) const
	{
		return invoke(get(), std::forward<Args>(args)...);
	}

	template<typename... Args>
	typename std::result_of<T&(Args&&...)>::type
	operator()(Args&&... args)
	{
		return invoke(get(), std::forward<Args>(args)...);
	}
};


/// Denotes a reference should be taken to a variable.
template<typename T>
inline strong_reference_wrapper<T>
sref(T& t)
{ return strong_reference_wrapper<T>(t); }

/// Denotes a const reference should be taken to a variable.
template<typename T>
inline strong_reference_wrapper<const T>
csref(const T& t)
{ return strong_reference_wrapper<const T>(t); }

template<typename T>
void sref(const T&&) = delete;

template<typename T>
void csref(const T&&) = delete;

/// Partial specialization.
template<typename T>
inline strong_reference_wrapper<T>
sref(strong_reference_wrapper<T> t)
{ return sref(t.get()); }

/// Partial specialization.
template<typename T>
inline strong_reference_wrapper<const T>
csref(strong_reference_wrapper<T> t)
{ return csref(t.get()); }

}

#endif
