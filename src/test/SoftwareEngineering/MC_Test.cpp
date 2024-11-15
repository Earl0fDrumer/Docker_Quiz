#include "MC_Test.hpp"

#include <iostream>
#include <memory>

#include "../../controller/SoftwareEngineering/SEController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void MC_Test::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Get object mapper component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                  objectMapper);

  /* Add SeleneController endpoints to the router of the test server */
  runner.addController(std::make_shared<SEController>());

  /* Run test */
  runner.run(
      [this, &runner] {
        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::network::ClientConnectionProvider>,
            clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
                clientConnectionProvider);

        /* Create Test API client */
        auto client =
            MyApiTestClient::createShared(requestExecutor, objectMapper);

        /* Call server API */
        auto response = client->getMCQuestion();

        /* Assert that server responds with 200 */
        OATPP_ASSERT(response->getStatusCode() == 200);

        /* Read response body as MessageDto */
        auto message =
            response->readBodyToDto<oatpp::Object<Result_MC>>(objectMapper.get());

        /* Assert that received message is as expected */
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionText == "What is SE?");
        OATPP_ASSERT(message->optionA == "Branch of computer science that deals with the design, development, testing, and maintenance of software applications");
        OATPP_ASSERT(message->optionB == "When you combine different software programs together to engineer a new program");
        OATPP_ASSERT(message->optionC == "Branch of computer science that deals with creating and maintaing the hardware of PCs");
        OATPP_ASSERT(message->optionD == "Branch of computer science that deals with the creation, deletion, and maintance of Serialized Exponents (SE)");

      },
      std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
