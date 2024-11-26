#ifndef RandomByTypeController_hpp
#define RandomByTypeController_hpp

#include <memory>
#include <unordered_map>
#include "src/service/RandomByType.hpp"
#include "src/dto/FIB_DTOs.hpp"
#include "src/dto/MC_DTOs.hpp"
#include "src/dto/TF_DTOs.hpp"
#include "src/dto/MAT_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
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

      std::string teamStr = team->c_str();
      auto it = teamFolderMap.find(teamStr);
      if (it == teamFolderMap.end()) {
        return createResponse(Status::CODE_400, "Invalid team. Use SE, DP, VC, or OOP.");
      }

      RandomByType randomByType(it->second);
      auto questions = randomByType.getRandomQuestions();

      if (questions.empty()) {
        return createResponse(Status::CODE_404, "No questions found.");
      }

      auto selectedQuestion = questions[0];

      // Generate DTO based on question type (simplified example for FillInBlank)
      auto dto = Result_FIB::createShared();
      dto->questionText = selectedQuestion.getQuestionText();
      dto->wordBank = oatpp::Vector<oatpp::String>::createShared();
      for (const auto& word : selectedQuestion.getAnswers()) {
        dto->wordBank->push_back(word.c_str());
      }
      return createDtoResponse(Status::CODE_200, dto);

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
