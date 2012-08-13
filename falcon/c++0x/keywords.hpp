#ifndef FALCON_CPP0X_KEYWORDS_HPP
#define FALCON_CPP0X_KEYWORDS_HPP

#include <falcon/c++0x/warning.hpp>

#ifndef __GXX_EXPERIMENTAL_CXX0X__

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
// 	#ifdef __GXX_EXPERIMENTAL_CXX0X__
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
