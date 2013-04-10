#ifndef _FALCON_TYPE_TRAITS_REFERENCE_SELECTOR_HPP
#define _FALCON_TYPE_TRAITS_REFERENCE_SELECTOR_HPP

#if __cplusplus > 201100L
# include <type_traits>
#else
# include <boost/type_traits/is_reference.hpp>
#endif

namespace falcon {

#if __cplusplus > 201100L
template<typename _Unqualified, bool _IsRValue>
struct rvalue_reference_selector
{
	typedef _Unqualified type;
};

template<typename _Unqualified>
struct rvalue_reference_selector<_Unqualified, true>
{
	typedef _Unqualified&& type;
};
#endif

template<typename _Unqualified, bool _IsLValue>
struct lvalue_reference_selector
{
	typedef _Unqualified type;
};

template<typename _Unqualified>
struct lvalue_reference_selector<_Unqualified, true>
{
	typedef _Unqualified& type;
};

namespace reference_type {
enum enum_t {
	lvalue_reference,
#if __cplusplus > 201100L
	rvalue_reference,
#endif
	no_reference
};
}

template<typename _Unqualified, reference_type::enum_t _Ref>
struct reference_selector
	{};

template<typename _Unqualified>
struct reference_selector<_Unqualified, reference_type::lvalue_reference>
{
	typedef _Unqualified& type;
};

#if __cplusplus > 201100L
template<typename _Unqualified>
struct reference_selector<_Unqualified, reference_type::rvalue_reference>
{
	typedef _Unqualified&& type;
};
#endif

template<typename _Unqualified>
struct reference_selector<_Unqualified, reference_type::no_reference>
{
	typedef _Unqualified type;
};

template <typename _T>
struct reference_qualified
{
	static const reference_type::enum_t value =
#if __cplusplus > 201100L
		std::is_rvalue_reference<_T>::value
		? reference_type::rvalue_reference
		: (
			std::is_lvalue_reference<_T>::value
#else
		boost::is_reference<_T>::value_type
#endif
			? reference_type::lvalue_reference
			: reference_type::no_reference
#if __cplusplus > 201100L
		)
#endif
		;
};

template<typename _Qualified, typename _Unqualified, reference_type::enum_t _Ref = reference_qualified<_Qualified>::value>
struct match_reference_selector
{
	typedef typename reference_selector<_Unqualified, _Ref>::type type;
};

}

#endif
