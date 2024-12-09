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

  /* Test service class methods directly */
  std::string path = "src/QuestionData/VersionControl/MultipleChoice.json";
  MultipleChoice question(path);
  
  // Test getCorrectAnswer
  OATPP_ASSERT(question.getCorrectAnswer() == "a");
  
  // Test validateAnswer with correct answer
  OATPP_ASSERT(question.validateAnswer("a") == "Correct!");
  
  // Test validateAnswer with wrong answer
  OATPP_ASSERT(question.validateAnswer("c") == "Incorrect. The correct answer is: a");

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

        /* Test POST endpoint */
        auto submission = AnswerSubmission::createShared();
        
        // Test correct answer
        submission->answer = "a";
        auto validationResponse = client->validateMCAnswer("VersionControl", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        auto result = validationResponse->readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == true);

        // Test incorrect answer
        submission->answer = "c";
        validationResponse = client->validateMCAnswer("VersionControl", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        result = validationResponse->readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == false);
        OATPP_ASSERT(result->correctAnswer == "a");
      },
      std::chrono::minutes(1) /* test timeout */);

  std::this_thread::sleep_for(std::chrono::seconds(1));
}
