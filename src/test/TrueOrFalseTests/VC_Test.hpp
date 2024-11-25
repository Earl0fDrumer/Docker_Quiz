#ifndef VC_TF_TEST_HPP
#define VC_TF_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class VC_TF_Test : public oatpp::test::UnitTest {
 public:
  VC_TF_Test() : UnitTest("TEST[VC_TF_Test]") {}
  void onRun() override;
};

#endif  // VC_TF_TEST_HPP
