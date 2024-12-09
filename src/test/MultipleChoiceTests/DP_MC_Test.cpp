#include "DP_MC_Test.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "src/controller/MultipleChoice/MC_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void DP_MC_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  /* Test service class methods directly */
  std::string path = "src/QuestionData/DesignPatterns/MultipleChoice.json";
  MultipleChoice question(path);

  // Test getCorrectAnswer
  OATPP_ASSERT(question.getCorrectAnswer() == "b");

  // Test validateAnswer with correct answer
  OATPP_ASSERT(question.validateAnswer("b") == "Correct!");

  // Test validateAnswer with wrong answer
  OATPP_ASSERT(question.validateAnswer("a") ==
    "Incorrect. The correct answer is: b");

  // Add MC_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<MC_Controller>());

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
        auto response = client->getDP_MCQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as DPResult_MC DTO
        auto message =
          response->readBodyToDto<oatpp::Object<Result_MC>>(
            objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextMC ==
         "Which design pattern ensures a class has only one"
         " instance and provides a global point of access to it?");
        OATPP_ASSERT(message->optionA == "Factory Pattern");
        OATPP_ASSERT(message->optionB == "Singleton Pattern");
        OATPP_ASSERT(message->optionC == "Observer Pattern");
        OATPP_ASSERT(message->optionD == "Strategy Pattern");

        /* Test POST endpoint */
        auto submission = AnswerSubmission::createShared();

        // Test correct answer
        submission->answer = "b";
        auto validationResponse = client->
          validateMCAnswer("DesignPatterns", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        auto result = validationResponse->readBodyToDto
          <oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == true);

        // Test incorrect answer
        submission->answer = "a";
        validationResponse = client->
          validateMCAnswer("DesignPatterns", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        result = validationResponse->readBodyToDto
          <oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == false);
        OATPP_ASSERT(result->correctAnswer == "b");
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
