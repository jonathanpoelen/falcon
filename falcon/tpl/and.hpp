#ifndef FALCON_TPL_AND_HPP
#define FALCON_TPL_AND_HPP

#include <falcon/tpl/integral_test.hpp>

namespace falcon {
namespace tpl {

template<bool a, bool b>
struct __and
{ static const bool value = (a&&b); };

template<template<class...> class... Temps>
using and_ = integral_test<bool, __and, Temps...>;

}
}

#endif
