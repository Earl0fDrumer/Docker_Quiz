#ifndef VC_MC_TEST_HPP
#define VC_MC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class VC_MC_Test : public oatpp::test::UnitTest {
 public:
  VC_MC_Test() : UnitTest("TEST[VC_MC_Test]") {}
  void onRun() override;
};

#endif  // VC_MC_TEST_HPP
