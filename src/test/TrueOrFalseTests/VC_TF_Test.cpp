#include "VC_TF_Test.hpp"

#include <iostream>
#include <memory>

#include "src/controller/TrueOrFalse/TF_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void VC_TF_Test::onRun() {
  TestComponent component;

  oatpp::test::web::ClientServerTestRunner runner;

  runner.addController(std::make_shared<TF_Controller>());

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

        auto response = client->getVC_TFQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        auto message =
          response->readBodyToDto<oatpp::Object<Result_TF>>(
            objectMapper.get());

        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionText ==
          "Version Control is essential when multiple"
          " people are working on a project");
      },
      std::chrono::minutes(1) /* test timeout */);

  std::this_thread::sleep_for(std::chrono::seconds(1));
}
