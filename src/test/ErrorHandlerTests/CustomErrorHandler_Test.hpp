#ifndef CustomErrorHandler_Test_hpp
#define CustomErrorHandler_Test_hpp

#include "CustomErrorHandler.hpp"
#include "TestComponent.hpp"
#include "oatpp/test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/component.hpp"
#include "gtest/gtest.h"

class CustomErrorHandler_Test : public oatpp::test::UnitTest {
public:

  CustomErrorHandler_Test()
    : oatpp::test::UnitTest("TEST[CustomErrorHandler_Test]")
  {}

  void onRun() override {

    TestComponent components;

    oatpp::test::web::ClientServerTestRunner runner;

    /* Add components for the server */
    runner.addComponent<TestComponent>();

    runner.run([] {
      /* Create the API client */
      auto client = MyApiTestClient::createShared();

      // Test 404 error
      {
        auto response = client->execute("GET", "/nonexistent", nullptr);
        OATPP_ASSERT(response->getStatusCode() == 404);
        auto body = response->readBodyToString();
        OATPP_ASSERT(body->find("\"status\": 404") != std::string::npos);
        OATPP_ASSERT(body->find("Oops! We couldn't find that page.") != std::string::npos);
      }

      // Test 400 error
      {
        auto response = client->execute("POST", "/endpoint", "{invalid_json}");
        OATPP_ASSERT(response->getStatusCode() == 400);
        auto body = response->readBodyToString();
        OATPP_ASSERT(body->find("\"status\": 400") != std::string::npos);
        OATPP_ASSERT(body->find("Your request seems a bit off.") != std::string::npos);
      }
    });
  }
};

#endif /* CustomErrorHandler_Test_hpp */
