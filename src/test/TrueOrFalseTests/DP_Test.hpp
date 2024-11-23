#ifndef DP_TF_TEST_HPP
#define DP_TF_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class DP_TF_Test : public oatpp::test::UnitTest {
public:
  DP_TF_Test() : UnitTest("TEST[DP_TF_Test]") {}
  inline void onRun() override;
};

#endif // DP_TF_TEST_HPP
