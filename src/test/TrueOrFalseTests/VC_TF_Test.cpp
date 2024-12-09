#include "VC_TF_Test.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "src/controller/TrueOrFalse/TF_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void VC_TF_Test::onRun() {
  TestComponent component;

  oatpp::test::web::ClientServerTestRunner runner;

  runner.addController(std::make_shared<TF_Controller>());

      /* Test service class methods */
  std::string path =
    "src/QuestionData/VersionControl/TrueFalse.json";
  TrueOrFalse question(path);

  /* Test getCorrectAnswer and validateAnswer */
  OATPP_ASSERT(question.getCorrectAnswer() == "a");
  OATPP_ASSERT(question.validateAnswer("a") == "Correct!");
  OATPP_ASSERT(question.validateAnswer("b") ==
    "Incorrect. The correct answer is: a");

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
        OATPP_ASSERT(message->questionTextTF ==
          "Version Control is essential when multiple"
          " people are working on a project");

        /* Test answer validation - correct case */
        auto submission = AnswerSubmission::createShared();
        submission->answer = "a";
        auto validationResponse = client->
          validateTFAnswer("VersionControl", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        auto result = validationResponse->
          readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == true);

        /* Test answer validation - incorrect case */
        submission->answer = "b";
        validationResponse = client->
          validateTFAnswer("VersionControl", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        result = validationResponse->readBodyToDto
          <oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_LOGI("Test", "correctAnswer value: '%s'",
          result->correctAnswer->c_str());
        OATPP_ASSERT(result->isCorrect == false);
        OATPP_ASSERT(result->correctAnswer == "a");
      },
      std::chrono::minutes(1) /* test timeout */);

  std::this_thread::sleep_for(std::chrono::seconds(1));
}
