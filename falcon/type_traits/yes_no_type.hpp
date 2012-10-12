#ifndef FALCON_TYPE_TRAITS_YES_NO_TYPE_HPP
#define FALCON_TYPE_TRAITS_YES_NO_TYPE_HPP

namespace falcon {

typedef char yes_type;
typedef struct { char a[2]; } no_type;

template <bool>
struct bool_to_yes_no_type
{
	typedef no_type type;
};

template <>
struct bool_to_yes_no_type<true>
{
	typedef yes_type type;
};

template<typename _T>
struct is_yes_type
{
	static const bool value = false;
};

template<>
struct is_yes_type<yes_type>
{
	static const bool value = true;
};

template<typename _T>
struct is_no_type
{
	static const bool value = false;
};

template<>
struct is_no_type<no_type>
{
	static const bool value = true;
};

///\brief value is true if _T is yes_type, oterwise false
template<typename _T>
struct yes_no_type_to_bool : is_yes_type<_T>
{};

}

#endif
