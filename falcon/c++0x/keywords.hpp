#ifndef FALCON_CPP0X_KEYWORDS_HPP
#define FALCON_CPP0X_KEYWORDS_HPP

#include <falcon/c++0x/warning.hpp>

#if __cplusplus <= 201100L

# include <falcon/type_traits/unspecified_type.hpp>

# define decltype(...) unspecified_type
# define constexpr
# define static_assert(...)
# define nullptr 0

#endif

//nullptr : key word C++0x (encore g++ 4.6)
// constexpr
// class {
// public:
// 	#if __cplusplus > 201100L
// 	template<class T>
// 	operator T*() const
// 	{ return 0; }
// 	template<class C, class T>
// 	operator T C::*() const
// 	{ return 0; }
// 	#endif
// private:
// 	void operator&() const;
// } nullptr = {};

#endif
