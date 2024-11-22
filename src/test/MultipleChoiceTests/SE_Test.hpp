#ifndef SE_MC_TEST_HPP
#define SE_MC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class SE_MC_Test : public oatpp::test::UnitTest {
 public:
  SE_MC_Test() : UnitTest("TEST[SE_MC_Test]") {}
  inline void onRun() override;
};

#endif  // SE_MC_TEST_HPP
