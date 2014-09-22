#ifndef FALCON_UTILITY_XOR_SWAP_HPP
#define FALCON_UTILITY_XOR_SWAP_HPP

namespace falcon {

template<typename T>
void xor_swap(T& a, T& b)
{
  a ^= b;
  b ^= a;
  a ^= b;
}

template<typename ForwardIt1, typename ForwardIt2>
void iter_xor_swap(ForwardIt1 a, ForwardIt2 b)
{
  for (; a != b; ++a) {
    xor_swap(a, b);
  }
}

}

#endif
