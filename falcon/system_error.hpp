#ifndef FALCON_SYSTEM_ERROR_HPP
#define FALCON_SYSTEM_ERROR_HPP

#if __cplusplus >= 201103L
# include <system_error>
# define FALCON_NAMESPACE_SYSTEM_ERROR std
#else
# include <boost/system/system_error.hpp>
# include <boost/system/error_code.hpp>
# define FALCON_NAMESPACE_SYSTEM_ERROR boost::system
#endif

namespace falcon {

using FALCON_NAMESPACE_SYSTEM_ERROR::error_code;
using FALCON_NAMESPACE_SYSTEM_ERROR::error_code;
using FALCON_NAMESPACE_SYSTEM_ERROR::system_error;
using FALCON_NAMESPACE_SYSTEM_ERROR::system_category;
using FALCON_NAMESPACE_SYSTEM_ERROR::generic_category;

}

#undef FALCON_NAMESPACE_SYSTEM_ERROR

#endif
