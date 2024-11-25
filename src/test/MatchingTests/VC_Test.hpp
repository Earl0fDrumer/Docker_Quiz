#ifndef VC_MAT_TEST_HPP
#define VC_MAT_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class VC_MAT_Test : public oatpp::test::UnitTest {
 public:
  VC_MAT_Test() : UnitTest("TEST[VC_MAT_Test]") {}
  void onRun() override;
};

#endif // VC_MAT_TEST_HPP
