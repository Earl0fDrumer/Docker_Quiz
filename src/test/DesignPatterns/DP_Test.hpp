#ifndef DP_TEST_HPP
#define DP_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class DP_Test : public oatpp::test::UnitTest {
public:
  DP_Test() : UnitTest("TEST[DP_Test]") {}
  void onRun() override;
};

#endif // DP_TEST_HPP
