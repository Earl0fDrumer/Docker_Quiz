#ifndef MC_TEST_HPP
#define MC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class MC_Test : public oatpp::test::UnitTest {
 public:
  MC_Test() : UnitTest("TEST[MC_Test]") {}
  void onRun() override;
};

#endif  // MC_TEST_HPP
