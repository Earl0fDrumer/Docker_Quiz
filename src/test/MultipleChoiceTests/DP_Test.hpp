#ifndef DP_MC_TEST_HPP
#define DP_MC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class DP_MC_Test : public oatpp::test::UnitTest {
 public:
  DP_MC_Test() : UnitTest("TEST[DP_MC_Test]") {}
  void onRun() override;
};

#endif // DP_MC_TEST_HPP
