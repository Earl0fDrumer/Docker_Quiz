#ifndef TF_Controller_hpp
#define TF_Controller_hpp

#include <memory>
#include "src/service/TrueOrFalse/TF_Question.hpp"
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
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  TF_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getDP_TFQuestion)
  ENDPOINT("GET", "/DP/TF", getDP_TFQuestion) {
    auto dto = Result_TF::createShared();

    std::string path = "src/QuestionData/DesignPatterns/TrueFalse.json";
    TrueOrFalse question(path);

    dto->questionTextTF = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->trueText = Answers[0];
    dto->falseText = Answers[1];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET Design Patterns TF

  ADD_CORS(getOOD_TFQuestion)
  ENDPOINT("GET", "/OOD/TF", getOOD_TFQuestion) {
    auto dto = Result_TF::createShared();

    std::string path = "src/QuestionData/ObjectOrientedDesign/TrueFalse.json";
    TrueOrFalse question(path);

    dto->questionTextTF = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->trueText = Answers[0];
    dto->falseText = Answers[1];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET Object-Oriented_Design TF

  ADD_CORS(getSE_TFQuestion)
  ENDPOINT("GET", "/SE/TF", getSE_TFQuestion) {
    auto dto = Result_TF::createShared();

    std::string path = "src/QuestionData/SoftwareEngineering/TrueFalse.json";
    TrueOrFalse question(path);

    dto->questionTextTF = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->trueText = Answers[0];
    dto->falseText = Answers[1];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET Software Engineering TF

  ADD_CORS(getVC_TFQuestion)
  ENDPOINT("GET", "/VC/TF", getVC_TFQuestion) {
    auto dto = Result_TF::createShared();

    std::string path = "src/QuestionData/VersionControl/TrueFalse.json";
    TrueOrFalse question(path);

    dto->questionTextTF = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->trueText = Answers[0];
    dto->falseText = Answers[1];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET Version Control TF
};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* TF_Controller_hpp */
