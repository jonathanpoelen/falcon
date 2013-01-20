#ifndef _FALCON_PARAMETER_KEEP_PARAMETER_INDEX_HPP
#define _FALCON_PARAMETER_KEEP_PARAMETER_INDEX_HPP

#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

/**
 * @addtogroup indexes-selector
 *
 * @{
 */

/**
 * @addtogroup indexes-tag
 *
 * @{
 */
template<std::size_t _Keep = 1>
struct first_parameter_index_tag {};

template<std::size_t _Keep = 1>
struct last_parameter_index_tag {};

template<std::size_t _Start, std::size_t _Len = 1>
struct range_parameter_index_tag {};

template<std::size_t _Start, std::size_t _Len = 1>
struct ignore_parameter_index_tag {};

template<std::size_t _Start, std::size_t _Len = -1>
struct reverse_parameter_index_tag {};

struct full_parameter_index_tag {};

struct empty_parameter_index_tag {};

template<typename _Indexes>
struct specified_parameter_index_tag {};
//@}

template<typename _ParameterIndexTag, std::size_t _NmArg>
struct __keep_parameter_index;

template<std::size_t _Keep, std::size_t _NmArg>
struct __keep_parameter_index<first_parameter_index_tag<_Keep>, _NmArg>
{
	typedef typename build_parameter_index<
		(_Keep > _NmArg ? _NmArg : _Keep)
	>::type __type;
};

template<std::size_t _Keep, std::size_t _NmArg>
struct __keep_parameter_index<last_parameter_index_tag<_Keep>, _NmArg>
{
	typedef typename build_range_parameter_index<
		(_Keep > _NmArg ? 0 : _NmArg - _Keep),
		_NmArg
	>::type __type;
};

template<std::size_t _Start, std::size_t _Len, std::size_t _NmArg>
struct __keep_parameter_index<ignore_parameter_index_tag<_Start, _Len>, _NmArg>
{
	static const std::size_t __start = (_Start > _NmArg ? _NmArg : _Start);
	typedef typename parameter_index_cat<
		typename build_parameter_index<__start>::type,
		typename build_range_parameter_index<
			(_Start + _Len > _NmArg ? _NmArg : _Start + _Len),
			_NmArg
		>::type
	>::type __type;
};

template<std::size_t _Start, std::size_t _Len, std::size_t _NmArg>
struct __keep_parameter_index<range_parameter_index_tag<_Start, _Len>, _NmArg>
{
	static const std::size_t __start = (_Start > _NmArg ? _NmArg : _Start);
	typedef typename build_range_parameter_index<
		__start,
		(__start + _Len > _NmArg ? _NmArg : __start + _Len)
	>::type __type;
};

template<std::size_t _NmArg>
struct __keep_parameter_index<full_parameter_index_tag, _NmArg>
{
	typedef typename build_parameter_index<_NmArg>::type __type;
};

template<std::size_t _NmArg>
struct __keep_parameter_index<empty_parameter_index_tag, _NmArg>
{
	typedef parameter_index<> __type;
};

template<std::size_t _NmArg, std::size_t... _Indexes>
struct __keep_parameter_index<specified_parameter_index_tag<parameter_index<_Indexes...>>, _NmArg>
{
	typedef parameter_index<_Indexes...> __type;
};

template<std::size_t _Start, std::size_t _Len, std::size_t _NmArg>
struct __keep_parameter_index<reverse_parameter_index_tag<_Start, _Len>, _NmArg>
{
	static const std::size_t __start = (_Start > _NmArg ? _NmArg : _Start);
	static const std::size_t __stop = (_Len == -1u ? _NmArg : (__start + _Len > _NmArg ? _NmArg : __start + _Len));
	typedef typename parameter_index_cat<
		typename build_parameter_index<__start>::type,
		typename parameter_index_reverse<
			typename build_range_parameter_index<__start, __stop>::type
		>::type,
		typename build_range_parameter_index<__stop, _NmArg>::type
	>::type __type;
};

/**
 * \brief Make type \p parameter_index for \link indexes-tag indexes-tag group \endlink.
 */
template<typename _ParameterIndexTag, std::size_t _NmArg>
struct keep_parameter_index
{
	typedef typename __keep_parameter_index<_ParameterIndexTag, _NmArg>::__type type;
};


template<typename _ParameterIndexTag>
struct parameter_index_or_tag_to_tag
{
	typedef _ParameterIndexTag type;
};

template<std::size_t... _Indexes>
struct parameter_index_or_tag_to_tag<parameter_index<_Indexes...>>
{
	typedef specified_parameter_index_tag<parameter_index<_Indexes...>> type;
};

//@}


}

#endif