#ifndef SE_MAT_TEST_HPP
#define SE_MAT_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class SE_MAT_Test : public oatpp::test::UnitTest {
 public:
  SE_MAT_Test() : UnitTest("TEST[SE_MAT_Test]") {}
  void onRun() override;
};

#endif // SE_MAT_TEST_HPP
