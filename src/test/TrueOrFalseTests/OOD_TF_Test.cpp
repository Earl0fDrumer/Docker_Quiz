#include "OOD_TF_Test.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "../../controller/TrueOrFalse/TF_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void OOD_TF_Test::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Get object mapper component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                  objectMapper);

  /* Add SeleneController endpoints to the router of the test server */
  runner.addController(std::make_shared<TF_Controller>());

  /* Test service class methods */
  std::string path = "src/QuestionData/ObjectOrientedDesign/TrueFalse.json";
  TrueOrFalse question(path);

  /* Test getCorrectAnswer and validateAnswer */
  OATPP_ASSERT(question.getCorrectAnswer() == "b");
  OATPP_ASSERT(question.validateAnswer("b") == "Correct!");
  OATPP_ASSERT(question.validateAnswer("a") ==
    "Incorrect. The correct answer is: b");

  /* Run test */
  runner.run(
      [this, &runner] {
        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::network::ClientConnectionProvider>,
            clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
                clientConnectionProvider);

        /* Create Test API client */
        auto client =
            MyApiTestClient::createShared(requestExecutor, objectMapper);

        /* Call server API */
        auto response = client->getOOD_TFQuestion();

        /* Assert that server responds with 200 */
        OATPP_ASSERT(response->getStatusCode() == 200);

        /* Read response body as MessageDto */
        auto message =
            response->readBodyToDto<oatpp::Object<Result_TF>>(
                objectMapper.get());

        /* Assert that received message is as expected */
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextTF ==
         "SOLID stands for Simple Occular Luxurious"
         " Instantaneous Development");

        /* Test answer validation - correct case */
        auto submission = AnswerSubmission::createShared();
        submission->answer = "b";
        auto validationResponse = client->
            validateTFAnswer("ObjectOrientedDesign", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        auto result = validationResponse->readBodyToDto
            <oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == true);

        /* Test answer validation - incorrect case */
        submission->answer = "a";
        validationResponse = client->
            validateTFAnswer("ObjectOrientedDesign", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        result = validationResponse->readBodyToDto
            <oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_LOGI("Test", "correctAnswer value: '%s'",
            result->correctAnswer->c_str());
        OATPP_ASSERT(result->isCorrect == false);
        OATPP_ASSERT(result->correctAnswer == "b");
      },
      std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
