#ifndef VC_TEST_HPP
#define VC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class VC_Test : public oatpp::test::UnitTest {
 public:
  VC_Test() : UnitTest("TEST[VC_Test]") {}
  void onRun() override;
};

#endif  // VC_TEST_HPP
