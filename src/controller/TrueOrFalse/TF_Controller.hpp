#ifndef TF_Controller_hpp
#define TF_Controller_hpp

#include <memory>

#include "src/service/MultipleChoice/TF_Question.hpp"
#include "src/dto/SeleneDTOs.hpp"
#include "src/dto/TF_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class TF_Controller : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  TF_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}
      
  ADD_CORS(getDP_TFQuestion)
  ENDPOINT("GET", "/DP/TF", getDP_TFQuestion) {
    try {
      auto dto = Result_TF::createShared();
      std::string path = "src/QuestionData/DesignPatterns/MultipleChoice.json";
      MultipleChoice question = MultipleChoice(path);

      dto->questionText = question.getQuestionText();
      
      std::vector<std::string> Answers = question.getAnswers();
      dto->trueText = question.Answers[0];
      dto->falseText = question.Answers[1];

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("DPController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    } catch (...) {
      OATPP_LOGE("DPController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  } // GET Design Patterns TF

  ADD_CORS(getOOD_TFQuestion)
  ENDPOINT("GET", "/OOD/TF", getOOD_TFQuestion) {

    auto obj_dto = Result_TF::createShared();
    std::string path = "src/QuestionData/ObjectOrientedDesign/MultipleChoice.json";
    
    MultipleChoice question = MultipleChoice(path);

    obj_dto->questionText = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->trueText = question.Answers[0];
    dto->falseText = question.Answers[1];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET Object-Oriented_Design TF


  ADD_CORS(getSE_TFQuestion)
  ENDPOINT("GET", "/SE/TF", getSE_TFQuestion) {
    auto dto = Result_TF::createShared();

    std::string path = "src/QuestionData/SoftwareEngineering/MultipleChoice.json";

    MultipleChoice question = MultipleChoice(path);

    dto->questionText = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->trueText = question.Answers[0];
    dto->falseText = question.Answers[1];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET Software Engineering TF

  ADD_CORS(getVC_TFQuestion)
  ENDPOINT("GET", "/VC/TF", getVC_TFQuestion) {
    try {
      auto dto = Result_TF::createShared();  // Create DTO instance
      std::string path = "src/QuestionData/VersionControl/MultipleChoice.json";
        
      MultipleChoice question = MultipleChoice(path);

      // Populate the DTO with question data
      dto->questionText = question.getQuestionText();
      std::vector<std::string> Answers = question.getAnswers();
      dto->trueText = question.Answers[0];
      dto->falseText = question.Answers[1];

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("VCController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error: " + std::string(e.what()));
    } catch (...) {
      OATPP_LOGE("VCController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  } // GET Version Control TF
};  // End of Controller

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* TF_Controller_hpp */