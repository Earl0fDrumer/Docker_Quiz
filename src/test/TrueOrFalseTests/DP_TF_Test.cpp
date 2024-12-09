#include "DP_TF_Test.hpp"

#include <iostream>
#include <memory>

#include "src/controller/TrueOrFalse/TF_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void DP_TF_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  /* Test service class methods */
  std::string path = "src/QuestionData/DesignPatterns/TrueFalse.json";
  TrueOrFalse question(path);
  
  /* Test getCorrectAnswer and validateAnswer */
  OATPP_ASSERT(question.getCorrectAnswer() == "a");
  OATPP_ASSERT(question.validateAnswer("a") == "Correct!");
  OATPP_ASSERT(question.validateAnswer("b") == "Incorrect. The correct answer is: a");

  // Add MC_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<TF_Controller>());

  // Run test
  runner.run(
      [this, &runner] {  // Keep this format, capture `runner`
        // Get client connection provider for Api Client
        OATPP_COMPONENT(
          std::shared_ptr<oatpp::network::ClientConnectionProvider>,
           clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT(
          std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        // Create http request executor for Api Client
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
              clientConnectionProvider);

        // Create Test API client
        auto client =
          MyApiTestClient::createShared(requestExecutor, objectMapper);

        // Call server API
        auto response = client->getDP_TFQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as DPResult_MC DTO
        auto message =
          response->readBodyToDto<oatpp::Object<Result_TF>>(
            objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextTF ==
         "A Design Pattern can help a developer write code more efficiently.");

      /* Test answer validation - correct case */
      auto submission = AnswerSubmission::createShared();
      submission->answer = "a";
      auto validationResponse = client->validateTFAnswer("DesignPatterns", submission);
      OATPP_ASSERT(validationResponse->getStatusCode() == 200);
      auto result = validationResponse->readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
      OATPP_ASSERT(result->isCorrect == true);

      /* Test answer validation - incorrect case */
      submission->answer = "b";
      validationResponse = client->validateTFAnswer("DesignPatterns", submission);
      OATPP_ASSERT(validationResponse->getStatusCode() == 200);
      result = validationResponse->readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
      OATPP_LOGI("Test", "correctAnswer value: '%s'", result->correctAnswer->c_str());
      OATPP_ASSERT(result->isCorrect == false);
      OATPP_ASSERT(result->correctAnswer == "a");
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
