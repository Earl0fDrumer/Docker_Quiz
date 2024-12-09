#include "SE_MAT_Test.hpp"

#include <iostream>
#include <memory>
#include <string>
#include "src/controller/Matching/MAT_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void SE_MAT_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Add MAT_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<MAT_Controller>());

  // Run test
  runner.run(
      [this, &runner] {
        // Get client connection provider for Api Client
        OATPP_COMPONENT
        (std::shared_ptr<oatpp::network::ClientConnectionProvider>,
                        clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);

        // Create HTTP request executor for API client
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::
                                createShared(clientConnectionProvider);

        // Create Test API client
        auto client = MyApiTestClient::createShared
        (requestExecutor, objectMapper);

        // Call server API
        auto response = client->getSE_MATQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as DPResult_MAT DTO
        auto message = response->readBodyToDto<oatpp::Object<Result_MAT>>(
                          objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextMAT == "What is:");

        // Match terms
        OATPP_ASSERT(message->termA == "a Waterfall Model?");
        OATPP_ASSERT(message->termB == "Agile Development Model?");
        OATPP_ASSERT(message->termC == "Code and Fix Model?");
        OATPP_ASSERT(message->termD == "Incremental Process Model?");

        // Match definitions (order: ["a", "b", "c", "d"])
        std::string s;

        s = "A traditional software development model where each phase "
            "(requirements, design, implementation, testing, deployment, "
            "and maintenance) is completed sequentially.";
        OATPP_ASSERT(message->definitionA == s);

        s = "A methodology focused on iterative and incremental development, "
            "where requirements and solutions evolve through collaboration "
            "between self-organizing cross-functional teams.";
        OATPP_ASSERT(message->definitionB == s);

        s = "An ad hoc approach to maintaining software. It is a fire-fighting "
            "approach waiting for the problem to occur and then trying"
            " to fix it as quickly as possible.";
        OATPP_ASSERT(message->definitionC == s);

        s = "A simple working system implementing only a few basic features "
            "is built, thereafter many successive iterations/ versions are "
            "implemented and delivered to the customer.";
        OATPP_ASSERT(message->definitionD == s);
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
