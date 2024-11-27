#ifndef RANDOM_TYPE_TEST_HPP
#define RANDOM_TYPE_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class RandomType_Test : public oatpp::test::UnitTest {
 public:
  RandomType_Test() : UnitTest("TEST[RandomType_Test]") {}
  void onRun() override;
};

#endif // RANDOM_TYPE_TEST_HPP
