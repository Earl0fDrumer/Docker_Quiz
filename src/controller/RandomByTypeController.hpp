#ifndef RandomByTypeController_hpp
#define RandomByTypeController_hpp

#include <memory>
#include "src/service/RandomByType.hpp"
#include "src/dto/FIB_DTOs.hpp"
#include "src/dto/MAT_DTOs.hpp"
#include "src/dto/MC_DTOs.hpp"
#include "src/dto/TF_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class RandomByType_Controller : public oatpp::web::server::api::ApiController {
 public:
  RandomByType_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getRandomByTopic)
  ENDPOINT("GET", "/{topic}/random", getRandomByTopic,
           PATH(oatpp::String, topic)) {
    try {
      // Map topic to folder
      std::string topicFolder = RandomByType::mapTopicToFolder(topic->c_str());

      // Select random file
      std::string selectedFile = RandomByType::selectRandomQuestionFile();

      // Load questions
      std::string filePath = "src/QuestionData/" + topicFolder + "/" + selectedFile;
      RandomByType loader(topicFolder);
      auto questions = loader.loadQuestions(filePath);

      if (questions.empty()) {
        return createResponse(Status::CODE_404, "No questions found.");
      }

      auto selectedQuestion = questions[0];

      // Generate DTO
      if (selectedFile == "FillInBlank.json") {
        auto dto = Result_FIB::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->wordBank = oatpp::Vector<oatpp::String>::createShared();
        for (const auto& word : selectedQuestion.getAnswers()) {
          dto->wordBank->push_back(word.c_str());
        }
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "MultipleChoice.json") {
        auto dto = Result_MC::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->optionA = selectedQuestion.getAnswers()[0].c_str();
        dto->optionB = selectedQuestion.getAnswers()[1].c_str();
        dto->optionC = selectedQuestion.getAnswers()[2].c_str();
        dto->optionD = selectedQuestion.getAnswers()[3].c_str();
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "TrueFalse.json") {
        auto dto = Result_TF::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->trueText = selectedQuestion.getAnswers()[0].c_str();
        dto->falseText = selectedQuestion.getAnswers()[1].c_str();
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "Matching.json") {
        auto dto = Result_MAT::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->termA = selectedQuestion.getAnswers()[0].c_str();
        dto->termB = selectedQuestion.getAnswers()[1].c_str();
        dto->termC = selectedQuestion.getAnswers()[2].c_str();
        dto->termD = selectedQuestion.getAnswers()[3].c_str();
        dto->definitionA = selectedQuestion.getAnswers()[4].c_str();
        dto->definitionB = selectedQuestion.getAnswers()[5].c_str();
        dto->definitionC = selectedQuestion.getAnswers()[6].c_str();
        dto->definitionD = selectedQuestion.getAnswers()[7].c_str();
        return createDtoResponse(Status::CODE_200, dto);
      }

      return createResponse(Status::CODE_400, "Unknown question type");

    } catch (const std::exception& e) {
      OATPP_LOGE("RandomByType_Controller", "Exception: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error.");
    } catch (...) {
      OATPP_LOGE("RandomByType_Controller", "Unknown error occurred.");
      return createResponse(Status::CODE_500, "Internal Server Error.");
    }
  }

  ADD_CORS(getRandomTopicAndType)
  ENDPOINT("GET", "/random", getRandomTopicAndType) {
    try {
      // Randomize topic
      std::string randomTopicFolder = RandomByType::selectRandomTopic();

      // Randomize question type (file) within the topic
      std::string selectedFile = RandomByType::selectRandomQuestionFile();

      // Load questions from the randomized topic and file
      std::string filePath = "src/QuestionData/" + randomTopicFolder + "/" + selectedFile;
      RandomByType loader(randomTopicFolder);
      auto questions = loader.loadQuestions(filePath);

      if (questions.empty()) {
        return createResponse(Status::CODE_404, "No questions found.");
      }

      auto selectedQuestion = questions[0];

      // Generate DTO based on the question type
      if (selectedFile == "FillInBlank.json") {
        auto dto = Result_FIB::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->wordBank = oatpp::Vector<oatpp::String>::createShared();
        for (const auto& word : selectedQuestion.getAnswers()) {
          dto->wordBank->push_back(word.c_str());
        }
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "MultipleChoice.json") {
        auto dto = Result_MC::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->optionA = selectedQuestion.getAnswers()[0].c_str();
        dto->optionB = selectedQuestion.getAnswers()[1].c_str();
        dto->optionC = selectedQuestion.getAnswers()[2].c_str();
        dto->optionD = selectedQuestion.getAnswers()[3].c_str();
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "TrueFalse.json") {
        auto dto = Result_TF::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->trueText = selectedQuestion.getAnswers()[0].c_str();
        dto->falseText = selectedQuestion.getAnswers()[1].c_str();
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "Matching.json") {
        auto dto = Result_MAT::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->termA = selectedQuestion.getAnswers()[0].c_str();
        dto->termB = selectedQuestion.getAnswers()[1].c_str();
        dto->termC = selectedQuestion.getAnswers()[2].c_str();
        dto->termD = selectedQuestion.getAnswers()[3].c_str();
        dto->definitionA = selectedQuestion.getAnswers()[4].c_str();
        dto->definitionB = selectedQuestion.getAnswers()[5].c_str();
        dto->definitionC = selectedQuestion.getAnswers()[6].c_str();
        dto->definitionD = selectedQuestion.getAnswers()[7].c_str();
        return createDtoResponse(Status::CODE_200, dto);
      }

      return createResponse(Status::CODE_400, "Unknown question type");

    } catch (const std::exception& e) {
      OATPP_LOGE("RandomByType_Controller", "Exception: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error.");
    } catch (...) {
      OATPP_LOGE("RandomByType_Controller", "Unknown error occurred.");
      return createResponse(Status::CODE_500, "Internal Server Error.");
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* RandomByTypeController_hpp */
