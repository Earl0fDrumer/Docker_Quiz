#ifndef RANDOM_TYPE_TOPIC_TEST_HPP
#define RANDOM_TYPE_TOPIC_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class RandomTypeTopic_Test : public oatpp::test::UnitTest {
 public:
  RandomTypeTopic_Test() : UnitTest("TEST[RandomTypeTopic_Test]") {}
  void onRun() override;
};

#endif // RANDOM_TYPE_TOPIC_TEST_HPP
