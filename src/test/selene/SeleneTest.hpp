#ifndef SeleneTest_hpp
#define SeleneTest_hpp

#include "oatpp-test/UnitTest.hpp"

class SeleneTest : public oatpp::test::UnitTest {
 public:
  SeleneTest() : UnitTest("TEST[Selene]") {}
  void onRun() override;
};

#endif  // SeleneTest_hpp
