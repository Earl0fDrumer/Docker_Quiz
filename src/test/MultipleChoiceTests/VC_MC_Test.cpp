#include "VC_MC_Test.hpp"

#include <iostream>
#include <memory>

#include "src/controller/MultipleChoice/MC_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void VC_MC_Test::onRun() {
  TestComponent component;

  oatpp::test::web::ClientServerTestRunner runner;

  runner.addController(std::make_shared<MC_Controller>());

  runner.run(
      [this, &runner] {
        OATPP_COMPONENT(
          std::shared_ptr<oatpp::network::ClientConnectionProvider>,
           clientConnectionProvider);

        OATPP_COMPONENT(
          std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
              clientConnectionProvider);

        auto client =
          MyApiTestClient::createShared(requestExecutor, objectMapper);

        auto response = client->getVC_MCQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        auto message =
          response->readBodyToDto<oatpp::Object<Result_MC>>(
           objectMapper.get());

        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextMC ==
          "Which command is used to initialize a Git repository?");

        // Ensure options are correct
        OATPP_ASSERT(message->optionA == "git init");
        OATPP_ASSERT(message->optionB == "git start");
        OATPP_ASSERT(message->optionC == "git begin");
        OATPP_ASSERT(message->optionD == "git create");
      },
      std::chrono::minutes(1) /* test timeout */);

  std::this_thread::sleep_for(std::chrono::seconds(1));
}
