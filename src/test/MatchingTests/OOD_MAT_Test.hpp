#ifndef OOD_MAT_TEST_HPP
#define OOD_MAT_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class OOD_MAT_Test : public oatpp::test::UnitTest {
 public:
  OOD_MAT_Test() : UnitTest("TEST[OOD_MAT_Test]") {}
  void onRun() override;
};

#endif // OOD_MAT_TEST_HPP
