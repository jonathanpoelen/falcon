#ifndef _FALCON_MATH_RAD_HPP
#define _FALCON_MATH_RAD_HPP

#include <cmath>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

CPP_CONSTEXPR float rad(float n)
{
	return n * static_cast<float>(M_PI / 180.);
}

CPP_CONSTEXPR double rad(double n)
{
	return n * (M_PI / 180.);
}

CPP_CONSTEXPR long double rad(long double n)
{
	return n * (M_PIl / 180.);
}

CPP_CONSTEXPR double rad(int n)
{
	return n * (M_PI / 180.);
}

CPP_CONSTEXPR float frad(int n)
{
	return static_cast<float>(static_cast<float>(n) * static_cast<float>(M_PI / 180.));
}

CPP_CONSTEXPR float frad(float n)
{
	return n * static_cast<float>(M_PI / 180.);
}

CPP_CONSTEXPR long double lrad(long double n)
{
	return n * (M_PIl / 180.);
}

CPP_CONSTEXPR long double lrad(int n)
{
	return n * (M_PIl / 180.);
}

}

#endif