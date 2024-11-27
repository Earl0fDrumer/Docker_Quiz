#include "ListTopics_Test.hpp"

#include <iostream>
#include <memory>

#include "src/controller/TopicsController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void ListTopics_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Add MC_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<TopicsController>());

  // Run test
  runner.run(
      [this, &runner] {  // Keep this format, capture `runner`
        // Get client connection provider for Api Client
        OATPP_COMPONENT(
          std::shared_ptr<oatpp::network::ClientConnectionProvider>,
           clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT(
          std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        // Create http request executor for Api Client
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
              clientConnectionProvider);

        // Create Test API client
        auto client =
          MyApiTestClient::createShared(requestExecutor, objectMapper);

        // Call server API
        auto response = client->getTopics();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as Result_TOPIC DTO
        auto message =
          response->readBodyToDto<oatpp::Object<Result_TOPIC>>(
            objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->topic1 == "Design Patterns");
        OATPP_ASSERT(message->topic2 == "Object Oriented Design");
        OATPP_ASSERT(message->topic3 == "Software Engineering");
        OATPP_ASSERT(message->topic4 == "Version Control");
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
