#ifndef FALCON_PROPERTY_PROPERTY_HPP
#define FALCON_PROPERTY_PROPERTY_HPP

#include <utility>
#include <type_traits>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/default_or_type.hpp>
#include <falcon/fn/move.hpp>
#include <falcon/fn/unref.hpp>
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


namespace aux_ {
  template<typename T>
  using get_property = fn::forward_fn;


  template<typename T>
  struct set_property_assign
  {
    template<typename U>
    void operator()(T& oldvalue, const U& newvalue)
    { oldvalue = newvalue; }
  };

  template<typename T, typename Assign>
  struct set_property_through_get
  {
    Assign assign = Assign();

    template<typename Property>
    void operator()(Property& property, const T& value)
    { assign(property.get(), value); }
  };

  template<typename T, typename Assign = use_default>
  struct set_property_through_base
  {
    typedef typename default_or_type<
      use<set_property_assign<T>>,
      Assign
    >::type functor_type;

    functor_type assign = functor_type();

    template<typename Property>
    void operator()(Property& property, const T& value)
    { assign(property.base(), value); }
  };


  template<typename T, typename Get>
  struct get_property_traits
  : default_or_type<use<get_property<T>>, Get>
  {};

  template<typename T, typename Get, typename Set>
  struct set_property_through_get_traits
  : if_c<
    std::is_void<Set>,
    void,
    set_property_through_get<
      T,
      typename default_or_type<
        use<set_property_assign<T>>,
        Set
      >::type
    >
  >
  {};

  template<typename T, typename Set>
  struct set_property_through_get_traits<T, void, Set>
  : use<set_property_through_base<T, Set>>
  {};


  template<properties_t Properties, typename T, typename Get, typename Set>
  struct property_traits
  {
    typedef typename get_property_traits<T, Get>::type getter_type_;
    typedef typename set_property_through_get_traits<T, getter_type_, Set>::type setter_type_;

    typedef typename if_c<
      std::is_void<getter_type_>,
      std::nullptr_t,
      getter_type_
    >::type getter_type;
    typedef typename if_c<
      std::is_void<setter_type_>,
      std::nullptr_t,
      setter_type_
    >::type setter_type;

    struct none_assignable{ void operator()(T&, T&){}};
    struct default_assignable{ void operator()(T& a, T& b){a=b;}};

    static void assign(T& a, T& b)
    {
      typedef typename if_<
        (Properties & properties::copy_assignable_does_nothing)
        && !(Properties & properties::force_copy_assignable),
        none_assignable,
        default_assignable
      >::type assignable;
      assignable()(a, b);
    }
  };
}


template <
	properties_t Properties,
	typename T,
	typename Get = use_default,
	typename Set = use_default
>
class class_property
{
public:
	typedef typename if_<
   !!(Properties & properties::by_reference), T&, T>::type base_type;

private:
	typedef aux_::property_traits<Properties, base_type, Get, Set> traits_;

public:
	typedef typename traits_::getter_type getter_type;
	typedef typename traits_::setter_type setter_type;

	friend setter_type;

private:
	base_type value;
	getter_type getter;
	setter_type setter;

public:
	class_property(
    const base_type& x, getter_type g, setter_type s = setter_type())
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
		traits_::assign(value, other.value);
		getter = other.getter;
		setter = other.setter;
		return *this;
	}

	const T& base() const
	{ return value; }

	T& base()
	{ return value; }

private:
	template<typename G>
	auto dispatch_get(G&)
  -> decltype(std::declval<G>()(this->base()));

	template<typename G>
	auto dispatch_get(const G&) const
  -> decltype(std::declval<G>()(this->base()));

	void dispatch_get(std::nullptr_t) const;

public:
	auto get() const -> decltype(this->dispatch_get(this->getter))
	{ return getter(base()); }

	auto get() -> decltype(this->dispatch_get(this->getter))
	{ return getter(base()); }

	template<typename U>
	void set(U&& newvalue)
	{ return setter(*this, std::forward<U>(newvalue)); }

	template<typename U>
	void operator()(U&& newvalue)
	{ return set(newvalue); }

	auto operator()() const -> decltype(this->get())
	{ return get(); }

	auto operator()() -> decltype(this->get())
	{ return get(); }

	template<typename U>
	typename std::enable_if<
		!!(Properties & properties::implicit_cast),
		typename if_<0, U, void>::type
	>::type operator=(U&& newvalue)
	{ set(newvalue); }

	operator typename eval_if<
		!!(Properties & properties::implicit_cast),
		std::result_of<getter_type&(T&)>,
		use<void>
	>::type ()
	{ return get(); }

	operator typename eval_if<
    !!(Properties & properties::implicit_cast),
		std::result_of<const getter_type&(const T&)>,
		use<void>
	>::type () const
	{ return get(); }
};


template <properties_t Properties, typename T, typename Get = use_default>
using readonly_property = class_property<Properties, T, Get, void>;

template <properties_t Properties, typename T, typename Set = use_default>
using writeonly_property = class_property<Properties, T, void, Set>;


template <typename T, typename Get = use_default>
using attr_get = class_property<properties::by_reference, T, Get, void>;

template <typename T, typename Set = use_default>
using attr_set = class_property<properties::by_reference, T, void, Set>;

template <typename T, typename Get = use_default, typename Set = use_default>
using attr_access = class_property<properties::by_reference, T, Get, Set>;


template <typename T, typename Get = use_default>
using attr_read = class_property<properties::attribute, T, Get, void>;

template <typename T, typename Set = use_default>
using attr_write = class_property<properties::attribute, T, void, Set>;

template <typename T, typename Get = use_default, typename Set = use_default>
using attr_rw = class_property<properties::attribute, T, Get, Set>;


#define FALCON_PROPERTY_READ(name, ref)   attr_read   <decltype(ref)> name = ref
#define FALCON_PROPERTY_WRITE(name, ref)  attr_write  <decltype(ref)> name = ref
#define FALCON_PROPERTY_RW(name, ref)     attr_rw     <decltype(ref)> name = ref
#define FALCON_PROPERTY_GET(name, ref)    attr_get    <decltype(ref)> name = ref
#define FALCON_PROPERTY_SET(name, ref)    attr_set    <decltype(ref)> name = ref
#define FALCON_PROPERTY_ACCESS(name, ref) attr_access <decltype(ref)> name = ref

}}

#endif
