#include "OOD_MAT_Test.hpp"

#include <iostream>
#include <memory>
#include <string>
#include "src/controller/Matching/MAT_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void OOD_MAT_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Add MAT_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<MAT_Controller>());

  // Run test
  runner.run(
      [this, &runner] {  // Keep this format, capture `runner`
        // Get client connection provider for Api Client
        OATPP_COMPONENT(std::shared_ptr
          <oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT(std::shared_ptr
          <oatpp::data::mapping::ObjectMapper>, objectMapper);

        // Create http request executor for Api Client
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::
              createShared(clientConnectionProvider);

        // Create Test API client
        auto client = MyApiTestClient::createShared
          (requestExecutor, objectMapper);

        // Call server API
        auto response = client->getOOD_MATQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as DPResult_MAT DTO
        auto message = response->readBodyToDto<oatpp::
          Object<Result_MAT>>(objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextMAT == "What is:");

        OATPP_ASSERT(message->termA == "a Class?");
        OATPP_ASSERT(message->termB == "an Object?");
        OATPP_ASSERT(message->termC == "a Constructor?");
        OATPP_ASSERT(message->termD == "a Method?");

        std::string s = "A special type of function called to create "
        "an object.";
        OATPP_ASSERT(message->definitionA == s);
        s = "A blueprint for creating objects that defines "
        "the properties (attributes) and behaviors (methods) "
        "of those objects.";
        OATPP_ASSERT(message->definitionB == s);
        s = "A procedure that defines the behavior of objects created "
        "from a class.";
        OATPP_ASSERT(message->definitionC == s);
        s = "A unit of data and behavior created from a class, "
        "representing an instance of that class.";
        OATPP_ASSERT(message->definitionD == s);
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
