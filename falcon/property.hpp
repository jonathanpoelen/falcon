#ifndef FALCON_PROPERTY_PROPERTY_HPP
#define FALCON_PROPERTY_PROPERTY_HPP

#include <utility>
#include <type_traits>
#include <falcon/type_traits/use.hpp>
#include <falcon/accessor/reference_accessor.hpp>
#include <falcon/type_traits/eval_if.hpp>

namespace falcon {
namespace property {

struct properties
{
	static const int
	normal = 0,
	force_copy_assignable = 1 << 10,
	copy_assignable_does_nothing = 1 << 11,
	implicit_cast = 1 << 13,
	by_reference = 1 << 12 | copy_assignable_does_nothing,
	attribute = by_reference | implicit_cast;
};

using properties_t = int;


template<typename _T>
using __get_property = reference_accessor<_T>;


template<typename _T>
struct __set_property_functor
{
	template<typename _U>
	void operator()(_T& oldvalue, const _U& newvalue)
	{ oldvalue = newvalue; }
};

template<typename _T, typename _Assign>
struct __set_property
{
	_Assign assign = _Assign();

	template<typename _Property>
	void operator()(_Property& property, const _T& value)
	{ assign(property.get(), value); }
};

template<typename _T, typename _Assign = use_default>
struct __set_base_property
{
	typedef typename default_or_type<
		use<__set_property_functor<_T>>,
		_Assign
	>::type __functor_type;

	__functor_type assign = __functor_type();

	template<typename _Property>
	void operator()(_Property& property, const _T& value)
	{ assign(property.base(), value); }
};


template<typename _Assign = use_default>
struct set_by_base;


template<typename _T, typename _Get>
struct __get_property_traits
: default_or_type<use<__get_property<_T>>, _Get>
{};

template<typename _T, typename _Get, typename _Set>
struct __set_property_traits
: if_c<
	std::is_void<_Set>,
	void,
	__set_property<
		_T,
		typename default_or_type<
			use<__set_property_functor<_T>>,
			_Set
		>::type
	>
>
{};

template<typename _T, typename _Set>
struct __set_property_traits<_T, void, _Set>
: use<__set_base_property<_T, _Set>>
{};

template<typename _T, typename _Get, typename _Set>
struct __set_property_traits<_T, _Get, set_by_base<_Set>>
: use<__set_base_property<_T, _Set>>
{};

template<typename _T, typename _Set>
struct __set_property_traits<_T, void, set_by_base<_Set>>
: use<__set_base_property<_T, _Set>>
{};


template<properties_t _Properties, typename _T, typename _Get, typename _Set>
struct __property_traits
{
	typedef typename __get_property_traits<_T, _Get>::type __getter_type;
	typedef typename __set_property_traits<_T, __getter_type, _Set>::type __setter_type;

	typedef typename if_c<
		std::is_void<__getter_type>,
		std::nullptr_t,
		__getter_type
	>::type getter_type;
	typedef typename if_c<
		std::is_void<__setter_type>,
		std::nullptr_t,
		__setter_type
	>::type setter_type;

	struct none_assignable{ void operator()(_T&, _T&){}};
	struct default_assignable{ void operator()(_T& a, _T& b){a=b;}};

	static void assign(_T& a, _T& b)
	{
		typedef typename if_<
			(_Properties & properties::copy_assignable_does_nothing)
			&& !(_Properties & properties::force_copy_assignable),
			none_assignable,
			default_assignable
		>::type assignable;
		assignable()(a, b);
	}
};


template <
	properties_t _Properties,
	typename _T,
	typename _Get = use_default,
	typename _Set = use_default
>
class class_property
{
public:
	typedef typename if_<_Properties & properties::by_reference, _T&, _T>::type base_type;

private:
	typedef __property_traits<_Properties, base_type, _Get, _Set> __traits;

public:
	typedef typename __traits::getter_type getter_type;
	typedef typename __traits::setter_type setter_type;

	friend setter_type;

private:
	base_type value;
	getter_type getter;
	setter_type setter;

public:
	class_property(const base_type& x, getter_type g, setter_type s = setter_type())
	: value(x)
	, getter(g)
	, setter(s)
	{}

	class_property(const base_type& x, setter_type s)
	: value(x)
	, getter()
	, setter(s)
	{}

	class_property(const base_type& x)
	: value(x)
	, getter()
	, setter()
	{}

	class_property& operator=(const class_property& other)
	{
		__traits::assign(value, other.value);
		getter = other.getter;
		setter = other.setter;
		return *this;
	}

	const _T& base() const
	{ return value; }

	_T& base()
	{ return value; }

private:
	template<typename _G>
	auto dispatch_get(_G&)
	-> decltype(this->getter(this->base()));

	template<typename _G>
	auto dispatch_get(const _G&) const
	-> decltype(this->getter(this->base()));

	void dispatch_get(std::nullptr_t) const;

public:
	auto get() const -> decltype(this->dispatch_get(this->getter))
	{ return getter(base()); }

	auto get() -> decltype(this->dispatch_get(this->getter))
	{ return getter(base()); }

	template<typename _U>
	void set(_U&& newvalue)
	{ return setter(*this, std::forward<_U>(newvalue)); }

	template<typename _U>
	void operator()(_U&& newvalue)
	{ return set(newvalue); }

	auto operator()() const -> decltype(this->get())
	{ return get(); }

	auto operator()() -> decltype(this->get())
	{ return get(); }

	template<typename _U>
	typename std::enable_if<
		_Properties & properties::implicit_cast,
		typename if_<0, _U, void>::type
	>::type operator=(_U&& newvalue)
	{ set(newvalue); }

	operator typename eval_if<
		_Properties & properties::implicit_cast,
		std::result_of<getter_type&(_T&)>,
		use<void>
	>::type ()
	{ return get(); }

	operator typename eval_if<
		_Properties & properties::implicit_cast,
		std::result_of<const getter_type&(const _T&)>,
		use<void>
	>::type () const
	{ return get(); }
};


template <properties_t _Properties, typename _T, typename _Get = use_default>
using readonly_property = class_property<_Properties, _T, _Get, void>;

template <properties_t _Properties, typename _T, typename _Set = use_default>
using writeonly_property = class_property<_Properties, _T, void, _Set>;


template <typename _T, typename _Get = use_default>
using get_attr = class_property<properties::by_reference, _T, _Get, void>;

template <typename _T, typename _Set = use_default>
using set_attr = class_property<properties::by_reference, _T, void, _Set>;

template <typename _T, typename _Get = use_default, typename _Set = use_default>
using access_attr = class_property<properties::by_reference, _T, _Get, _Set>;


template <typename _T, typename _Get = use_default>
using read_attr = class_property<properties::attribute, _T, _Get, void>;

template <typename _T, typename _Set = use_default>
using write_attr = class_property<properties::attribute, _T, void, _Set>;

template <typename _T, typename _Get = use_default, typename _Set = use_default>
using rw_attr = class_property<properties::attribute, _T, _Get, _Set>;

}}

#endif