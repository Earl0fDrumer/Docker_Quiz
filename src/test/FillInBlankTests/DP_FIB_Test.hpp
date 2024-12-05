#ifndef DP_FIB_Test_hpp
#define DP_FIB_Test_hpp

#include "oatpp-test/UnitTest.hpp"

class DP_FIB_Test : public oatpp::test::UnitTest {
 public:
  DP_FIB_Test() : UnitTest("TEST[DP_FIB_Test") {}
  void onRun() override;
};

#endif  // DP_FIB_Test_hpp
