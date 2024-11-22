#ifndef OOD_MC_TEST_HPP
#define OOD_MC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class OOD_MC_Test : public oatpp::test::UnitTest {
 public:
  OOD_MC_Test() : UnitTest("TEST[OOD_MC_Test]") {}
  inline void onRun() override;
};

#endif  // OOD_MC_TEST_HPP
