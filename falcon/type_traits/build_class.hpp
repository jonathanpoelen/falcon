#ifndef FALCON_TYPE_TRAITS_BUILD_CLASS_HPP
#define FALCON_TYPE_TRAITS_BUILD_CLASS_HPP

namespace falcon
{

template <template<typename...> class W, typename Pack>
class __build_class;

template <template<typename...> class W
, template<typename...> class Pack
, typename... Elements
>
struct __build_class<W, Pack<Elements...>>
{ typedef W<Elements...> type; };

template <template<typename...> class W, typename Pack>
struct build_class
{ typedef typename __build_class<W, Pack>::type type; };

template <template<typename...> class W, typename... Elements>
struct build_class2
{ typedef W<Elements...> type; };

template <typename T, template<T...> class W, typename Pack>
class __build_class_by_value;

template <typename T
, template<T...> class W
, template<typename...> class Pack
, typename... Elements
>
struct __build_class_by_value<T, W, Pack<Elements...>>
{ typedef W<Elements::value...> type; };

template <typename T, template<T...> class W, typename Pack>
struct build_class_by_value
{ typedef typename __build_class_by_value<T, W, Pack>::type type; };

}

#endif
