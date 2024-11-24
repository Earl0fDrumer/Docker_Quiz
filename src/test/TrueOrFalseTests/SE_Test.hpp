#ifndef SE_TF_TEST_HPP
#define SE_TF_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class SE_TF_Test : public oatpp::test::UnitTest {
 public:
  SE_TF_Test() : UnitTest("TEST[SE_TF_Test]") {}
  inline void onRun() override;
};

#endif  // SE_TF_TEST_HPP
