
#include "VC_MAT_Test.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/controller/Matching/MAT_Controller.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void VC_MAT_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Add MAT_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<MAT_Controller>());

    /* Test service class methods directly */
  std::string path = "src/QuestionData/VersionControl/Matching.json";
  Matching question(path);

    // Test valid answer
  std::vector<std::string> correctAnswers = {"c", "a", "d", "b"};
  OATPP_ASSERT(question.validateAllAnswers(correctAnswers) == true);

  // Test wrong size answer
  std::vector<std::string> wrongSizeAnswers = {"c", "a", "d"};
  OATPP_ASSERT(question.validateAllAnswers(wrongSizeAnswers) == false);

  // Test wrong answer
  std::vector<std::string> wrongAnswers = {"a", "b", "c", "d"};
  OATPP_ASSERT(question.validateAllAnswers(wrongAnswers) == false);

  // Run test
  runner.run(
      [this, &runner] {
        // Get client connection provider for Api Client
        OATPP_COMPONENT
        (std::shared_ptr<oatpp::network::ClientConnectionProvider>,
                        clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT
        (std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);

        // Create HTTP request executor for API client
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::
                                createShared(clientConnectionProvider);

        // Create Test API client
        auto client = MyApiTestClient::createShared
        (requestExecutor, objectMapper);

        // Call server API
        auto response = client->getVC_MATQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Read response body as DPResult_MAT DTO
        auto message = response->
        readBodyToDto<oatpp::Object<Result_MAT>>(
                          objectMapper.get());

        // Assert that received message is as expected
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->questionTextMAT == "What is:");

        // Match terms
        OATPP_ASSERT(message->termA == "a Commit?");
        OATPP_ASSERT(message->termB == "a Branch?");
        OATPP_ASSERT(message->termC == "a Merge Request?");
        OATPP_ASSERT(message->termD == "a Pull Request ?");

        // Match definitions (order: ["a", "b", "c", "d"])
        std::string s;

        s = "A record of changes made to the files in the repository. It "
            "includes a snapshot of the changes, a message describing the"
            " update, and metadata like the author and timestamp.";
        OATPP_ASSERT(message->definitionA == s);

        s = "A separate line of development in a version control system. It "
            "allows developers to work on features, fixes, or experiments "
            "independently from the main codebase.";
        OATPP_ASSERT(message->definitionB == s);

        s = "The process of integrating changes from one"
            " branch into another, usually from "
            "a feature branch back into the main or master branch.";
        OATPP_ASSERT(message->definitionC == s);

        s = "Ask permission to merge changes from one branch into another, "
            "typically from a feature branch into the main branch,"
            " often requiring review before merging.";
        OATPP_ASSERT(message->definitionD == s);

                        /* Test POST endpoint */
        auto submission = MultipleAnswersSubmission::createShared();

        // Test correct answer
        submission->answers = oatpp::Vector<oatpp::String>::createShared();
        submission->answers->push_back("c");
        submission->answers->push_back("a");
        submission->answers->push_back("d");
        submission->answers->push_back("b");

        auto validationResponse = client->
         validateMATAnswer("VersionControl", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        auto result = validationResponse->
          readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == true);

        // Test incorrect answer
        submission->answers->clear();
        submission->answers->push_back("a");
        submission->answers->push_back("b");
        submission->answers->push_back("c");
        submission->answers->push_back("d");

        validationResponse = client->
          validateMATAnswer("VersionControl", submission);
        OATPP_ASSERT(validationResponse->getStatusCode() == 200);
        result = validationResponse->
          readBodyToDto<oatpp::Object<ValidationResult>>(objectMapper.get());
        OATPP_ASSERT(result->isCorrect == false);
      },
      std::chrono::minutes(10) /* test timeout */);

  // Wait for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
