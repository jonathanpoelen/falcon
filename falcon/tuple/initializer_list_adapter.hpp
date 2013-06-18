#ifndef FALCON_TUPLE_INITIALIZER_LIST_ADAPTER_HPP
#define FALCON_TUPLE_INITIALIZER_LIST_ADAPTER_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>
#include <initializer_list>
#include <utility>

namespace std {
	template<std::size_t I, typename T>
	T& get(initializer_list<T>& l) noexcept
	{ return l.begin()[I]; }

	template<std::size_t I, typename T>
	constexpr const T& get(const initializer_list<T>& l) noexcept
	{ return l.begin()[I]; }

	template<std::size_t I, typename T>
	struct tuple_element<I, std::initializer_list<T>>
	{ typedef T type; };
}

#endif
