#include <test/test.hpp>
#include <falcon/algorithm/unordered.hpp>
#include "unordered.hpp"
#include <vector>

struct A {
  int i;

  A(int n) :i(n) {}

  A(A &&) = default;
  A&operator = (A &&) = default;
  A(A const &) = delete;
  A&operator = (A const &) = delete;

  operator int () const { return i; }
};

void unordered_test()
{
  std::vector<A> v1;
  std::vector<A> v2;

  for (auto i : {1, 2, 4, 4, 2, 1, 3, 3, 3, 2}) {
    v1.emplace_back(i);
    v2.emplace_back(i);
  }

  auto test = [] (std::vector<A> const & v, std::initializer_list<int> l) {
    CHECK_EQUAL_VALUE(v.size(), l.size());
    auto it = v.begin();
    for (auto i : l) {
      CHECK_EQUAL_VALUE(it->i, i);
      ++it;
    }
  };

  using namespace falcon;

  unordered_erase(v1, v1.begin());
  test(v1, {2, 2, 4, 4, 2, 1, 3, 3, 3}); PASSED();
  unordered_erase(v1, v1.begin() + 3);
  test(v1, {2, 2, 4, 3, 2, 1, 3, 3}); PASSED();
  unordered_erase(v1, v1.end() - 1);
  test(v1, {2, 2, 4, 3, 2, 1, 3}); PASSED();

  v1.erase(unordered_remove(v1.begin(), v1.end(), 2), v1.end());
  test(v1, {3, 1, 4, 3}); PASSED();
  v1.erase(unordered_remove(v1.begin(), v1.end(), 3), v1.end());
  test(v1, {4, 1}); PASSED();
  v1.erase(unordered_remove_if(v1.begin(), v1.end(), [](int){ return 1; })
  , v1.end());
  test(v1, {}); PASSED();

  unordered_erase(v2, v2.begin(), v2.begin()+2);
  test(v2, {3, 2, 4, 4, 2, 1, 3, 3}); PASSED();
  unordered_erase(v2, v2.end()-2, v2.end());
  test(v2, {3, 2, 4, 4, 2, 1}); PASSED();
  unordered_erase(v2, v2.begin()+2, v2.end()-2);
  test(v2, {3, 2, 2, 1});
}

FALCON_TEST_TO_MAIN(unordered_test)
