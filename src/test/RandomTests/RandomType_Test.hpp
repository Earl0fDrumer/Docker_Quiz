#ifndef RandomType_Test_hpp
#define RandomType_Test_hpp

#include "oatpp-test/UnitTest.hpp"

class RandomType_Test : public oatpp::test::UnitTest {
 public:
    RandomType_Test() : UnitTest("TEST[RandomType_Test]") {}
    void onRun() override;
};

#endif /* RandomType_Test_hpp */
