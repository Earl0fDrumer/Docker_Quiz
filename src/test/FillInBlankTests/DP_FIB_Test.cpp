#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "DP_FIB_Test.hpp"

#include "../../controller/FillInBlank/FillInBlank_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"


void DP_FIB_Test::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Get object mapper component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::
  ObjectMapper>, objectMapper);

  /* Add FillInBlank_Controller endpoints to the router of the test server */
  runner.addController(std::make_shared<FillInBlank_Controller>());

    /* Test service class methods directly */
  std::string path = "src/QuestionData/DesignPatterns/FillInBlank.json";
  FillInBlank question(path);
  OATPP_ASSERT(question.getCorrectAnswer() == "Singleton");
  OATPP_ASSERT(question.validateAnswer("Singleton") == "Correct!");
  OATPP_ASSERT(question.validateAnswer("Factory") == "Incorrect. The correct answer is: Singleton");

  /* Run the test */
  runner.run(
      [this, &runner]() {
        /* Get client connection provider for API client */
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::
        ClientConnectionProvider>, clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::
        ObjectMapper>, objectMapper);

        /* Create HTTP request executor for API client */
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::
            createShared(clientConnectionProvider);

        /* Create Test API client */
        auto client =
            MyApiTestClient::createShared(requestExecutor, objectMapper);

        /* Test the Design Patterns Fill-In-The-Blank question */
        OATPP_LOGI("DP_FIB_Test", "Testing Design Patterns FIB...");

        /* Send request to the endpoint */
        auto response = client->getDP_FIBQuestion();

        /* Assert that the server responds with a 200 status code */
        OATPP_ASSERT(response->getStatusCode() == 200);

        /* Read response body as Result_FIB DTO */
        auto question = response->readBodyToDto<oatpp::
        Object<Result_FIB>>(objectMapper.get());

        /* Assert that the question DTO is not null */
        OATPP_ASSERT(question);

        /* Assert the question text */
        OATPP_ASSERT(question->questionTextFIB == "The ________ pattern"
        " ensures a class has only one instance and provides a"
        " global point of access to it.");

        /* Assert the size of the word bank */
        OATPP_ASSERT(question->wordBank->size() == 6);

        /* List of expected words */
        std::vector<std::string> expectedWords = {
            "Singleton", "Factory", "Adapter", "Observer",
            "Builder", "Decorator"};

        /* Check that each expected word is in the word bank */
        for (const auto& expectedWord : expectedWords) {
          bool found = false;
          if (question->wordBank && question->wordBank.get()) {
            for (const auto& word : *(question->wordBank.get())) {
              if (word == expectedWord.c_str()) {
                found = true;
                break;
              }
            }
          }
          OATPP_ASSERT(found);  // Assert that the word was found
        }
        /* Test answer validation - correct case */
        auto submission = AnswerSubmission::createShared();
        submission->answer = "Singleton";
        auto validationResponse = client->validateFIBAnswer("DesignPatterns", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        auto result = validationResponse->readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == true);

        /* Test answer validation - incorrect case */
        submission->answer = "Factory";
        validationResponse = client->validateFIBAnswer("DesignPatterns", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        result = validationResponse->readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == false);
        OATPP_ASSERT(result->correctAnswer == "Singleton");
      },
      std::chrono::minutes(1) /* test timeout */);

  /* Wait for server threads to finish */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
