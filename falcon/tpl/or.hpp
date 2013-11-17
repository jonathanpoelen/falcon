#ifndef FALCON_TPL_OR_HPP
#define FALCON_TPL_OR_HPP

#include <falcon/tpl/integral_test.hpp>

namespace falcon {
namespace tpl {

template<bool a, bool b>
struct __or
{ static const bool value = (a||b); };

template<template<class...> class... Temps>
using or_ = integral_test<bool, __or, Temps...>;

}
}

#endif
