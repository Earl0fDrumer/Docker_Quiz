#ifndef OOD_Controller_hpp
#define OOD_Controller_hpp

#include <memory>

#include "src/service/MC_Question.hpp"
#include "src/dto/SeleneDTOs.hpp"
#include "src/dto/MC_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class OOD_Controller : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  OOD_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getMCQuestion)  // Needed to allow for cross domain access
  ENDPOINT("GET", "/OOD/MC", getMCQuestion) {

    auto obj_dto = Result_MC::createShared();
    std::string path = "src/QuestionData/ObjectOrientedDesign/MultipleChoice.json";
    
    MultipleChoice2 question = MultipleChoice2(path);

    obj_dto->questionText = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    obj_dto->optionA = Answers[0];
    obj_dto->optionB = Answers[1];
    obj_dto->optionC = Answers[2];
    obj_dto->optionD = Answers[3];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET

  ADD_CORS(getDP_MCQuestion)
  ENDPOINT("GET", "/DP/MC", getDP_MCQuestion) {
    try {
      auto dto = Result_MC::createShared();
      std::string path = "src/QuestionData/DesignPatterns/MultipleChoice.json";
      MultipleChoice2 question = MultipleChoice2(path);

      dto->questionText = question.getQuestionText();
      std::vector<std::string> Answers = question.getAnswers();

      if (Answers.size() < 4) {
        throw std::runtime_error("Insufficient answers provided in question");
      }

      dto->optionA = Answers[0];
      dto->optionB = Answers[1];
      dto->optionC = Answers[2];
      dto->optionD = Answers[3];

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("DPController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    } catch (...) {
      OATPP_LOGE("DPController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }

};  // End of SEController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* OOD_Controller_hpp */
