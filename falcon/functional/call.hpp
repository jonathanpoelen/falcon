#ifndef _FALCON_FUNCTIONAL_CALL_HPP
#define _FALCON_FUNCTIONAL_CALL_HPP

#include <utility>
#include <falcon/parameter/result_pack_of.hpp>
#include <falcon/parameter/pack_element.hpp>

namespace falcon {

template <typename _Function, typename _Indexes, typename... _Args>
struct __call_result_of
{
	typedef typename parameter::result_of<
		_Function,
		typename parameter::elements<
			parameter_pack<_Args&&...>,
			_Indexes
		>::type
	>::type __type;
};

/**
 * \addtogroup call-arguments
 * @{
 */
/**
 * \brief Call \c func with the indexes \c _Indexes for arguments \c args
 *
 * \code
 * call(parameter_index<0,2,0,1>(), f, 1,2,3,4,5);
 * \endcode
 * equivalent to
 * \code
 * f(1,3,1,2);
 * \endcode
 */
template <typename _Function, typename... _Args, std::size_t... _Indexes>
constexpr typename __call_result_of<
	_Function,
	parameter_index<_Indexes...>,
	_Args...
>::__type call(const parameter_index<_Indexes...>&,
			   _Function func, _Args&&... args)
{
	return func(arg<_Indexes>(std::forward<_Args>(args)...)...);
}
//@}

}

#endif
