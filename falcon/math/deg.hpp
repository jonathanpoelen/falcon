#ifndef _FALCON_MATH_DEG_HPP
#define _FALCON_MATH_DEG_HPP

#include <cmath>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

CPP_CONSTEXPR float deg(float n)
{
	return n * float(180. / M_PI);
}

CPP_CONSTEXPR double deg(double n)
{
	return n * (180. / M_PI);
}

CPP_CONSTEXPR float fdeg(float n)
{
	return n * float(180. / M_PI);
}

#if __cplusplus >= 201103L
  constexpr long double deg(long double n)
  {
    return n * (M_PIl / 180.l);
  }

  constexpr long double ldeg(long double n)
  {
    return n * (M_PIl / 180.l);
  }
#endif

}

#endif
