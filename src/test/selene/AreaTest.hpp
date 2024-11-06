#ifndef AreaTest_hpp
#define AreaTest_hpp

#include "oatpp-test/UnitTest.hpp"

class SeleneTest : public oatpp::test::UnitTest {
 public:
  SeleneTest() : UnitTest("TEST[Selene]") {}
  void onRun() override;
};

#endif  // AreaTest_hpp
