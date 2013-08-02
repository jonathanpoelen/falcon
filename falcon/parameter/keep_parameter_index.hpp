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
template<std::size_t Keep = 1>
struct first_parameter_index_tag {};

template<std::size_t Keep = 1>
struct last_parameter_index_tag {};

template<std::size_t Start, std::size_t Len = 1>
struct range_parameter_index_tag {};

template<std::size_t Start, std::size_t Len = 1>
struct ignore_parameter_index_tag {};

template<std::size_t Start, std::size_t Len = -1>
struct reverse_parameter_index_tag {};

struct full_parameter_index_tag {};

struct empty_parameter_index_tag {};

template<typename Indexes>
struct specified_parameter_index_tag {};
//@}

template<typename ParameterIndexTag, std::size_t NmArg>
struct __keep_parameter_index;

template<std::size_t Keep, std::size_t NmArg>
struct __keep_parameter_index<first_parameter_index_tag<Keep>, NmArg>
{
	typedef typename build_parameter_index<
		(Keep > NmArg ? NmArg : Keep)
	>::type __type;
};

template<std::size_t Keep, std::size_t NmArg>
struct __keep_parameter_index<last_parameter_index_tag<Keep>, NmArg>
{
	typedef typename build_range_parameter_index<
		(Keep > NmArg ? 0 : NmArg - Keep),
		NmArg
	>::type __type;
};

template<std::size_t Start, std::size_t Len, std::size_t NmArg>
struct __keep_parameter_index<ignore_parameter_index_tag<Start, Len>, NmArg>
{
	static const std::size_t __start = (Start > NmArg ? NmArg : Start);
	typedef typename parameter_index_cat<
		typename build_parameter_index<__start>::type,
		typename build_range_parameter_index<
			(Start + Len > NmArg ? NmArg : Start + Len),
			NmArg
		>::type
	>::type __type;
};

template<std::size_t Start, std::size_t Len, std::size_t NmArg>
struct __keep_parameter_index<range_parameter_index_tag<Start, Len>, NmArg>
{
	static const std::size_t __start = (Start > NmArg ? NmArg : Start);
	typedef typename build_range_parameter_index<
		__start,
		(__start + Len > NmArg ? NmArg : __start + Len)
	>::type __type;
};

template<std::size_t NmArg>
struct __keep_parameter_index<full_parameter_index_tag, NmArg>
{
	typedef typename build_parameter_index<NmArg>::type __type;
};

template<std::size_t NmArg>
struct __keep_parameter_index<empty_parameter_index_tag, NmArg>
{
	typedef parameter_index<> __type;
};

template<std::size_t NmArg, std::size_t... Indexes>
struct __keep_parameter_index<specified_parameter_index_tag<parameter_index<Indexes...>>, NmArg>
{
	typedef parameter_index<Indexes...> __type;
};

template<std::size_t Start, std::size_t Len, std::size_t NmArg>
struct __keep_parameter_index<reverse_parameter_index_tag<Start, Len>, NmArg>
{
	static const std::size_t __start = (Start > NmArg ? NmArg : Start);
	static const std::size_t __stop = (Len == -1u ? NmArg : (__start + Len > NmArg ? NmArg : __start + Len));
	typedef typename parameter_index_cat<
		typename build_parameter_index<__start>::type,
		typename parameter_index_reverse<
			typename build_range_parameter_index<__start, __stop>::type
		>::type,
		typename build_range_parameter_index<__stop, NmArg>::type
	>::type __type;
};

/**
 * \brief Make type \p parameter_index for \link indexes-tag indexes-tag group \endlink.
 */
template<typename ParameterIndexTag, std::size_t NmArg>
struct keep_parameter_index
{
	typedef typename __keep_parameter_index<ParameterIndexTag, NmArg>::__type type;
};


template<typename ParameterIndexTag>
struct parameter_index_or_tag_to_tag
{
	typedef ParameterIndexTag type;
};

template<std::size_t... Indexes>
struct parameter_index_or_tag_to_tag<parameter_index<Indexes...>>
{
	typedef specified_parameter_index_tag<parameter_index<Indexes...>> type;
};

//@}


namespace parameter {
  template<std::size_t Keep = 1>
  using first_index_tag = first_parameter_index_tag<Keep>;

  template<std::size_t Keep = 1>
  using last_index_tag = last_parameter_index_tag<Keep>;

  template<std::size_t Start, std::size_t Len = 1>
  using range_index_tag = range_parameter_index_tag<Start, Len>;

  template<std::size_t Start, std::size_t Len = 1>
  using ignore_index_tag = ignore_parameter_index_tag<Start, Len>;

  template<std::size_t Start, std::size_t Len = -1>
  using reverse_index_tag = reverse_parameter_index_tag<Start, Len>;

  using full_index_tag = full_parameter_index_tag;

  using empty_index_tag = empty_parameter_index_tag;

  template<typename Indexes>
  using specified_index_tag = specified_parameter_index_tag<Indexes>;

  template<typename ParameterIndexTag, std::size_t NmArg>
  using keep_index = keep_parameter_index<ParameterIndexTag, NmArg>;

  template<typename ParameterIndexTag>
  using index_or_index_tag = parameter_index_or_tag_to_tag<ParameterIndexTag>;
}


}

#endif
