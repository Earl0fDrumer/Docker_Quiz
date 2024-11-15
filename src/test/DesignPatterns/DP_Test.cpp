#include "DP_Test.hpp"

#include <iostream>
#include <memory>

#include "../../controller/DesignPatterns/DPController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void DP_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Get object mapper component
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

  // Add DPController endpoints to the router of the test server
  runner.addController(std::make_shared<DPController>());

  // Run test
  runner.run([this, &runner] {
    // Get client connection provider for Api Client
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

    // Create Test API client
    auto client = MyApiTestClient::createShared(
      oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider),
      objectMapper
    );

    // Test 200 Success
    auto response = client->getDPQuestion();
    OATPP_ASSERT(response->getStatusCode() == 200);

    // Read response body as DPResult_MC DTO
    auto message = response->readBodyToDto<oatpp::Object<DPResult_MC>>(objectMapper.get());

    // Assert that received message is as expected
    OATPP_ASSERT(message);
    OATPP_ASSERT(message->questionText == "Which design pattern ensures a class has only one instance and provides a global point of access to it?");
    OATPP_ASSERT(message->optionA == "Factory Pattern");
    OATPP_ASSERT(message->optionB == "Singleton Pattern");
    OATPP_ASSERT(message->optionC == "Observer Pattern");
    OATPP_ASSERT(message->optionD == "Strategy Pattern");
  }, std::chrono::minutes(10));

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
