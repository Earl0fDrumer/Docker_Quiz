#ifndef OOD_FIB_Test_hpp
#define OOD_FIB_Test_hpp

#include "oatpp-test/UnitTest.hpp"

class OOD_FIB_Test : public oatpp::test::UnitTest {
 public:
  OOD_FIB_Test() : UnitTest("TEST[OOD_FIB_Test]") {}
  void onRun() override;
};

#endif  // OOD_FIB_Test_hpp
