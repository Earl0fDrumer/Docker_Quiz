#ifndef RandomByTypeController_hpp
#define RandomByTypeController_hpp

#include <memory>
#include <random>
#include <unordered_map>
#include "src/dto/FIB_DTOs.hpp"
#include "src/dto/MAT_DTOs.hpp"
#include "src/dto/MC_DTOs.hpp"
#include "src/dto/TF_DTOs.hpp"
#include "src/service/RandomByType.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class RandomByType_Controller : public oatpp::web::server::api::ApiController {
 public:
  RandomByType_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getRandomByTeam)
  ENDPOINT("GET", "/{team}/random", getRandomByTeam,
           PATH(oatpp::String, team)) {
    try {
      OATPP_LOGI("RandomByType_Controller", "Received request for team: %s", team->c_str());

      // Map team codes to folder names
      std::unordered_map<std::string, std::string> teamFolderMap = {
          {"SE", "SoftwareEngineering"},
          {"DP", "DesignPatterns"},
          {"VC", "VersionControl"},
          {"OOP", "ObjectOrientedDesign"}};

      // Convert oatpp::String to std::string for easier handling
      std::string teamStr = team->c_str();

      // Validate the team
      auto it = teamFolderMap.find(teamStr);
      if (it == teamFolderMap.end()) {
        OATPP_LOGE("RandomByType_Controller", "Invalid team: %s", teamStr.c_str());
        return createResponse(Status::CODE_400, "Invalid team. Use SE, DP, VC, or OOP.");
      }

      std::string teamFolder = it->second;
      OATPP_LOGI("RandomByType_Controller", "Mapped team to folder: %s", teamFolder.c_str());

      // List of question type filenames
      std::vector<std::string> questionFiles = {"MultipleChoice.json", "TrueFalse.json", "FillInBlank.json", "Matching.json"};

      // Thread-local random generator with deterministic seed
      thread_local std::mt19937 gen(static_cast<unsigned long>(std::time(nullptr)));
      std::uniform_int_distribution<> typeDist(0, questionFiles.size() - 1);
      std::string selectedFile = questionFiles[typeDist(gen)];
      OATPP_LOGI("RandomByType_Controller", "Selected question file: %s", selectedFile.c_str());

      // Construct file path dynamically
      std::string filePath = "src/QuestionData/" + teamFolder + "/" + selectedFile;
      OATPP_LOGI("RandomByType_Controller", "Constructed file path: %s", filePath.c_str());

      // Load questions from the file
      RandomByType loader(filePath);
      auto questions = loader.loadQuestions();

      if (questions.empty()) {
        OATPP_LOGE("RandomByType_Controller", "No questions found in file: %s", filePath.c_str());
        return createResponse(Status::CODE_404, "No questions found.");
      }
      OATPP_LOGI("RandomByType_Controller", "Loaded %lu questions from file: %s", questions.size(), filePath.c_str());

      // Select the first question
      auto selectedQuestion = questions[0];
      OATPP_LOGI("RandomByType_Controller", "Selected the first question from file.");

      // Dynamically generate DTO based on the question file
      if (selectedFile == "FillInBlank.json") {
        auto dto = Result_FIB::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->wordBank = oatpp::Vector<oatpp::String>::createShared();
        for (const auto& word : selectedQuestion.getAnswers()) {
          dto->wordBank->push_back(word.c_str());
        }
        OATPP_LOGI("RandomByType_Controller", "Returning FillInBlank DTO.");
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "MultipleChoice.json") {
        auto dto = Result_MC::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->optionA = selectedQuestion.getAnswers()[0].c_str();
        dto->optionB = selectedQuestion.getAnswers()[1].c_str();
        dto->optionC = selectedQuestion.getAnswers()[2].c_str();
        dto->optionD = selectedQuestion.getAnswers()[3].c_str();
        OATPP_LOGI("RandomByType_Controller", "Returning MultipleChoice DTO.");
        return createDtoResponse(Status::CODE_200, dto);

      } else if (selectedFile == "TrueFalse.json") {
        auto dto = Result_TF::createShared();
        dto->questionText = selectedQuestion.getQuestionText();
        dto->trueText = selectedQuestion.getAnswers()[0].c_str();
        dto->falseText = selectedQuestion.getAnswers()[1].c_str();
        OATPP_LOGI("RandomByType_Controller", "Returning TrueFalse DTO.");
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
        OATPP_LOGI("RandomByType_Controller", "Returning Matching DTO.");
        return createDtoResponse(Status::CODE_200, dto);
      }

      OATPP_LOGE("RandomByType_Controller", "Unknown question type for file: %s", selectedFile.c_str());
      return createResponse(Status::CODE_400, "Unknown question type");

    } catch (const std::exception& e) {
      OATPP_LOGE("RandomByType_Controller", "Exception occurred: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error.");
    } catch (...) {
      OATPP_LOGE("RandomByType_Controller", "Unknown error occurred.");
      return createResponse(Status::CODE_500, "Internal Server Error.");
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* RandomByTypeController_hpp */

