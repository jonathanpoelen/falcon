#include <test/test.hpp>
#include <falcon/property.hpp>
#include "property.hpp"

void property_test()
{
  using namespace falcon::property;

  class A
  {
    int n = 3;
  public:
    //class_property<properties::attribute, int, falcon::use_default, void> num = n;
    //readonly_property<properties::attribute, int> num = n;
    attr_read<int> read_only_num = n;
    attr_get<int> get_num = n;

    FALCON_PROPERTY_READ(read_only_num2, n);

    void f()
    { ++n; }

    attr_set<int> set_num = n;
    attr_rw<int> rw_num = n;
  };

  CHECK_NOTYPENAME_TYPE(decltype(A::read_only_num), decltype(A::read_only_num2));

  A a;
  CHECK(3 == a.read_only_num());
  CHECK(3 == a.read_only_num);
  CHECK(3 == a.get_num());
  CHECK(3 == a.rw_num);
  CHECK(3 == a.rw_num());
  a.f();
  CHECK(4 == a.read_only_num());
  CHECK(4 == a.read_only_num);
  CHECK(4 == a.get_num());
  CHECK(4 == a.rw_num);
  CHECK(4 == a.rw_num());
  a.set_num(9);
  CHECK(9 == a.read_only_num);
  a.rw_num(8);
  CHECK(8 == a.read_only_num);
  a.rw_num = 5;
  CHECK(5 == a.read_only_num);
}

FALCON_GROUP_TEST_TO_MAIN(property_test)
