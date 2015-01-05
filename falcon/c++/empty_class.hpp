#ifndef FALCON_CPP_EMPTY_CLASS_HPP
#define FALCON_CPP_EMPTY_CLASS_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

#define CPP_EMPTY_CLASS(name) struct name { CPP_CONSTEXPR name()CPP_NOEXCEPT{} }

#endif
