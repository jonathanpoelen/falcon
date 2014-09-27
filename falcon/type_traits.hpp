#ifndef FALCON_TYPE_TRAITS_HPP
#define FALCON_TYPE_TRAITS_HPP

#include <falcon/type_traits/add_const_if_reference.hpp>
#include <falcon/type_traits/add_n_pointer.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>
#include <falcon/type_traits/difference.hpp>
#include <falcon/type_traits/dimension.hpp>
#include <falcon/type_traits/disable_if.hpp>
#include <falcon/type_traits/enable_if_not_integral.hpp>
#include <falcon/type_traits/identity.hpp>
#include <falcon/type_traits/ignore.hpp>
#include <falcon/type_traits/invalid_type.hpp>
#include <falcon/type_traits/is_ios.hpp>
#include <falcon/type_traits/is_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/type_traits/is_same.hpp>
#include <falcon/type_traits/normalize_index.hpp>
#include <falcon/type_traits/scalar.hpp>
#include <falcon/type_traits/selector.hpp>
#include <falcon/type_traits/subtype.hpp>
#include <falcon/type_traits/unqualified.hpp>
#include <falcon/type_traits/unspecified_type.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>

#if __cplusplus >= 201103L
# include <falcon/tuple/is_tuple_like.hpp>
# include <falcon/type_traits/build_class.hpp>
# include <falcon/type_traits/and.hpp>
# include <falcon/type_traits/or.hpp>
#endif

#endif
