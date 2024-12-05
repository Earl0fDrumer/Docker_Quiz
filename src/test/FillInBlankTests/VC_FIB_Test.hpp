#ifndef VC_FIB_Test_hpp
#define VC_FIB_Test_hpp

#include "oatpp-test/UnitTest.hpp"

class VC_FIB_Test : public oatpp::test::UnitTest {
 public:
  VC_FIB_Test() : UnitTest("TEST[VC_FIB_Test]") {}
  void onRun() override;
};

#endif  // VC_FIB_Test_hpp
