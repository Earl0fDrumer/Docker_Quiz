#include "RandomTypeTopic_Test.hpp"

#include <iostream>
#include <memory>

#include "src/controller/RandomController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void RandomTypeTopic_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Add MC_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<Random_Controller>());

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
        auto response = client->getRandomByTopic();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as string
        auto message = response->readBodyToString();

        // Assert that received message is not NULL
        OATPP_ASSERT(message);
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
