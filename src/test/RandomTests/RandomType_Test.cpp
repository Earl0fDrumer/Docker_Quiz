#include "RandomType_Test.hpp"

#include <iostream>
#include <memory>

// Include necessary headers
#include "src/controller/RandomController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void RandomType_Test::onRun() {
  // Register test components
  TestComponent component;

  // Create client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // Add Random_Controller endpoints to the router of the test server
  runner.addController(std::make_shared<Random_Controller>());

  // Run the test
  runner.run(
      [this, &runner] {
        // Get client connection provider for API client
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        // Get object mapper component
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        // Create HTTP request executor for API client
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        // Create test API client
        auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

        // Test cases for getRandomByTopic with each question type for specific topics
        const std::vector<std::pair<std::string, std::string>> byTopicTestCases = {
            {"FillInBlank.json", "SE"},
            {"MultipleChoice.json", "DP"},
            {"TrueFalse.json", "VC"},
            {"Matching.json", "OOD"}
        };

        // Test getRandomByTopic for specific question types
        for (const auto& [file, topic] : byTopicTestCases) {
          // Log the test case being executed
          OATPP_LOGD("RandomType_Test", "Testing getRandomByTopic - Topic: %s, File: %s", topic.c_str(), file.c_str());

          // Override randomness for specific file
          RandomRequest::testSelectedFile = file;

          // Call the server API for the specific topic
          auto response = client->getRandomByTopic(topic);
          OATPP_ASSERT(response->getStatusCode() == 200);

          // Read and validate the response body
          auto message = response->readBodyToString();
          OATPP_ASSERT(!message->empty());
        }

        // Reset overrides after getRandomByTopic tests
        RandomRequest::testSelectedFile = "";

        // Test cases for getRandomTopicAndType for all combinations of topic and file
        const std::vector<std::pair<std::string, std::string>> randomTestCases = {
            {"SE", "FillInBlank.json"},
            {"SE", "MultipleChoice.json"},
            {"SE", "TrueFalse.json"},
            {"SE", "Matching.json"},
            {"DP", "FillInBlank.json"},
            {"DP", "MultipleChoice.json"},
            {"DP", "TrueFalse.json"},
            {"DP", "Matching.json"},
            {"VC", "FillInBlank.json"},
            {"VC", "MultipleChoice.json"},
            {"VC", "TrueFalse.json"},
            {"VC", "Matching.json"},
            {"OOD", "FillInBlank.json"},
            {"OOD", "MultipleChoice.json"},
            {"OOD", "TrueFalse.json"},
            {"OOD", "Matching.json"}
        };

        // Test getRandomTopicAndType for all combinations
        for (const auto& [topic, file] : randomTestCases) {
          // Log the test case being executed
          OATPP_LOGD("RandomType_Test", "Testing getRandomTopicAndType - Topic: %s, File: %s", topic.c_str(), file.c_str());

          // Override randomness for specific topic and file
          RandomRequest::testSelectedTopic = topic;
          RandomRequest::testSelectedFile = file;

          // Call the server API
          auto response = client->getRandomTopicAndType();
          OATPP_ASSERT(response->getStatusCode() == 200);

          // Read and validate the response body
          auto message = response->readBodyToString();
          OATPP_ASSERT(!message->empty());
        }

        // Reset overrides after getRandomTopicAndType tests
        RandomRequest::testSelectedTopic = "";
        RandomRequest::testSelectedFile = "";

        // Additional tests for randomness
        OATPP_LOGD("RandomType_Test", "Testing randomness for topics and files");

        // Verify random topic generation
        std::unordered_set<std::string> randomTopics;
        for (int i = 0; i < 5; ++i) {
          std::string randomTopic = RandomRequest::selectRandomTopic();
          OATPP_LOGD("RandomType_Test", "Random Topic %d: %s", i + 1, randomTopic.c_str());
          randomTopics.insert(randomTopic);
        }
        // Ensure multiple unique topics are generated
        OATPP_ASSERT(randomTopics.size() > 1);

        // Verify random file generation
        std::unordered_set<std::string> randomFiles; // To track unique files
        for (int i = 0; i < 5; ++i) {
          std::string randomFile = RandomRequest::selectRandomQuestionFile();
          OATPP_LOGD("RandomType_Test", "Random File %d: %s", i + 1, randomFile.c_str());
          randomFiles.insert(randomFile);
        }
        // Ensure multiple unique files are generated
        OATPP_ASSERT(randomFiles.size() > 1);
      },
      std::chrono::minutes(10) /* test timeout */);

  // Allow time for all server threads to finish
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

