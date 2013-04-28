#ifndef FALCON_FOREACH_H
#define FALCON_FOREACH_H

#include <falcon/c++1x/warning.hpp>

#define __FALCON_FOREACH(P, _It, _Cont)\
	for (auto _It = _Cont.P##begin(), __end_it_cond = _Cont.P##end();\
		_It != __end_it_cond; ++_It)
#define __FALCON_FOREACH_FROM(P, _It, _Cont)\
	for (auto __end_it_cond = _Cont.P##end();\
		_It != __end_it_cond; ++_It)
#define __FALCON_FOREACH_FROM_COPY(P, _It, _Cont, _Begin)\
	for (auto _It = _Begin, __end_it_cond = _Cont.P##end(); _It != __end_it_cond; ++_It)
#define __FALCON_FOREACH_TO(P, _It, _Cont, _End)\
	for (auto _It = _Cont.P##begin(); _It != _End: ++_It)

#if __cplusplus >= 201103L
# define FALCON_FOREACH(_Value, _Cont) for (_Value: _Cont)
# define FALCON_FOREACH_REF(_Value, _Cont) FALCON_FOREACH(auto& _Value, _Cont)
# define FALCON_FOREACH_VAL(_Value, _Cont) FALCON_FOREACH(auto _Value, _Cont)
#else
namespace falcon {
	template <typename _T>
	typename _T::iterator __declval_iterator(_T&);
	template <typename _T>
	typename _T::const_iterator __declval_iterator(const _T&);
}
# define FALCON_FOREACH(_Value, _Cont) for (_Value = *falcon::__declval_iterator(_Cont);0;)
# define FALCON_FOREACH_REF(_Value, _Cont) FALCON_FOREACH(_Value, _Cont)
# define FALCON_FOREACH_VAL(_Value, _Cont) FALCON_FOREACH(_Value, _Cont)
#endif

#define FALCON_FOREACH_IT(_It, _Cont) __FALCON_FOREACH(, _It, _Cont)

#define FALCON_FOREACH_FROM(_It, _Cont) __FALCON_FOREACH_FROM(, _It, _Cont)
#define FALCON_FOREACH_FROM_COPY(_It, _Cont) __FALCON_FOREACH_FROM_COPY(, _It, _Cont)
#define FALCON_FOREACH_TO(_It, _Cont) __FALCON_FOREACH_TO(, _It, _Cont)

#define FALCON_REVERSE_FOREACH(_It, _Cont) __FALCON_FOREACH(r, _It, _Cont)
#define FALCON_REVERSE_FOREACH_FROM(_It, _Cont) __FALCON_FOREACH_FROM(r, _It, _Cont)
#define FALCON_REVERSE_FOREACH_FROM_COPY(_It, _Cont) __FALCON_FOREACH_FROM_COPY(r, _It, _Cont)
#define FALCON_REVERSE_FOREACH_TO(_It, _Cont) __FALCON_FOREACH_TO(r, _It, _Cont)

#define FALCON_CONSTANT_FOREACH(_It, _Cont) __FALCON_FOREACH(c, _It, _Cont)
#define FALCON_CONSTANT_FOREACH_FROM(_It, _Cont) __FALCON_FOREACH_FROM(c, _It, _Cont)
#define FALCON_CONSTANT_FOREACH_FROM_COPY(_It, _Cont) __FALCON_FOREACH_FROM_COPY(c, _It, _Cont)
#define FALCON_CONSTANT_FOREACH_TO(_It, _Cont) __FALCON_FOREACH_TO(c, _It, _Cont)

#define FALCON_CONSTANT_REVERSE_FOREACH(_It, _Cont) __FALCON_FOREACH(cr, _It, _Cont)
#define FALCON_CONSTANT_REVERSE_FOREACH_FROM(_It, _Cont) __FALCON_FOREACH_FROM(cr, _It, _Cont)
#define FALCON_CONSTANT_REVERSE_FOREACH_FROM_COPY(_It, _Cont) __FALCON_FOREACH_FROM_COPY(cr, _It, _Cont)
#define FALCON_CONSTANT_REVERSE_FOREACH_TO(_It, _Cont) __FALCON_FOREACH_TO(cr, _It, _Cont)


#define FALCON_FOR_N(_Var, _Begin, _End) for (auto _Var = _Begin; _Var != _End; ++_Var)
#define FALCON_REVERSE_FOR_N(_Var, _Begin, _End) for (auto _Var = _Begin; _Var != _End; --_Var)

#endif
