#ifndef LIST_TOPICS_TEST_HPP
#define LIST_TOPICS_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class ListTopics_Test : public oatpp::test::UnitTest {
 public:
  ListTopics_Test() : UnitTest("TEST[ListTopics_Test]") {}
  void onRun() override;
};

#endif // LIST_TOPICS_TEST_HPP
