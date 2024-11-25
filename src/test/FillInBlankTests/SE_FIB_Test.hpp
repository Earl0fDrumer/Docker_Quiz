#ifndef SE_FIB_Test_hpp
#define SE_FIB_Test_hpp

#include "oatpp-test/UnitTest.hpp"

class SE_FIB_Test : public oatpp::test::UnitTest {
 public:
  SE_FIB_Test() : UnitTest("TEST[Software Engineering FIB]") {}
  void onRun() override;
};

#endif  // SE_FIB_Test_hpp
