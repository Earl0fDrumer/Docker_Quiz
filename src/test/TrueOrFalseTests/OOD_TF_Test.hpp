#ifndef OOD_TF_TEST_HPP
#define OOD_TF_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class OOD_TF_Test : public oatpp::test::UnitTest {
 public:
  OOD_TF_Test() : UnitTest("TEST[OOD_TF_Test]") {}
  void onRun() override;
};

#endif  // OOD_TF_TEST_HPP
