#include "DP_MAT_Test.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "src/controller/Matching/MAT_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void DP_MAT_Test::onRun() {
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
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, 
                        clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, 
                        objectMapper);

        // Create HTTP request executor for API client
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::
                                createShared(clientConnectionProvider);

        // Create Test API client
        auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

        // Call server API
        auto response = client->getDP_MATQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as DPResult_MAT DTO
        auto message = response->readBodyToDto<oatpp::Object<Result_MAT>>(
                          objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextMAT == "What is:");

        // Match terms
        OATPP_ASSERT(message->termA == "an Abstract Factory?");
        OATPP_ASSERT(message->termB == "a Builder?");
        OATPP_ASSERT(message->termC == "a Factory Method?");
        OATPP_ASSERT(message->termD == "a Singleton?");

        // Match definitions (order: ["a", "b", "c", "d"])
        std::string s;

        s = "a creational design pattern that lets you produce families of "
            "related objects without specifying their concrete classes.";
        OATPP_ASSERT(message->definitionA == s);

        s = "a creational design pattern that lets you construct complex objects "
            "step by step.";
        OATPP_ASSERT(message->definitionB == s);

        s = "a creational design pattern that provides an interface for creating "
            "objects in a superclass, but allows subclasses to alter the type of "
            "objects that will be created.";
        OATPP_ASSERT(message->definitionC == s);

        s = "a creational design pattern that lets you ensure that a class has "
            "only one instance, while providing a global access point to this "
            "instance.";
        OATPP_ASSERT(message->definitionD == s);
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
