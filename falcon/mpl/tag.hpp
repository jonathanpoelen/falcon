// #ifndef FALCON_MPL_TAG_HPP
// #define FALCON_MPL_TAG_HPP
//
// #include <falcon/sfinae/has_type.hpp>
// #include <falcon/type_traits/use.hpp>
// #include <falcon/mpl/void.hpp>
// #include <falcon/mpl/if.hpp>
//
// namespace falcon {
// namespace mpl {
//
// namespace aux {
// FALCON_HAS_TYPE_TRAIT_DEF(tag); //TODO helper/tag.hpp
//
// template< typename T > struct tag_impl
// { using type = typename T::tag; };
// }
//
// template<typename T, typename Default = void_>
// struct tag
// {
//   using type = typename if_<
//     aux::has_tag<T>
//   , aux::tag_impl<T>
//   , use<Default>
//   >::type::type;
// };
//
// template<typename T, typename Default = void_>
// using tag_t = typename tag<T, Default>::type;
//
// }
// }
//
// #endif
