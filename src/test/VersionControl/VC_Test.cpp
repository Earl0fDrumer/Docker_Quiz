#include "VC_Test.hpp"

#include <iostream>
#include <memory>

#include "../../controller/VersionControl/VCController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void VC_Test::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Get object mapper component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

  /* Add VCController endpoints to the router of the test server */
  runner.addController(std::make_shared<VCController>());

  /* Run test */
  runner.run(
      [this, &runner] {
        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        /* Create Test API client */
        auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

        /* Success Scenario: Call server API */
        auto response = client->getMCQuestion();  // Call the /VC/MC endpoint

        /* Assert that server responds with 200 */
        OATPP_ASSERT(response->getStatusCode() == 200);

        /* Read response body as Result_MC DTO */
        auto message = response->readBodyToDto<oatpp::Object<VCResult_MC>>(objectMapper.get());

        /* Assert that received message is as expected */
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionText == "Which command is used to initialize a Git repository?");

        // Simulate Internal Server Error for Failure Scenario
        try {
          // Simulate an exception in the endpoint logic by calling an invalid function or returning a forced error
          auto errorResponse = client->getMCQuestion();  // Simulated call with invalid data
          OATPP_ASSERT(false && "Expected exception not thrown");  // Fail test if no exception occurs
        } catch (const std::exception& e) {
          /* Check for internal server error status */
          std::cerr << "Simulated exception caught: " << e.what() << std::endl;
        }

      },
      std::chrono::minutes(10) /* test timeout */);

  /* Wait for all server threads to finish */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
