#ifndef MAT_Controller_hpp
#define MAT_Controller_hpp

#include <memory>

#include "src/service/Matching/MAT_Question.hpp"
#include "src/dto/SeleneDTOs.hpp"
#include "src/dto/MAT_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "src/dto/AnswerSubmission_DTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class MAT_Controller : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  MAT_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getDP_MATQuestion)
  ENDPOINT("GET", "/DP/MAT", getDP_MATQuestion) {

    auto obj_dto = Result_MAT::createShared();
    std::string path = "src/QuestionData/DesignPatterns/Matching.json";
    
    Matching MAT_question = Matching(path);

    obj_dto->questionTextMAT = MAT_question.getQuestionText();
    std::vector<std::string> Answers = MAT_question.getAnswers();
    std::vector<std::string> Definitions = MAT_question.getDefinitions();
    obj_dto->termA = Answers[0];
    obj_dto->termB = Answers[1];
    obj_dto->termC = Answers[2];
    obj_dto->termD = Answers[3];

    obj_dto->definitionA = Definitions[0];
    obj_dto->definitionB = Definitions[1];
    obj_dto->definitionC = Definitions[2];
    obj_dto->definitionD = Definitions[3];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET DesignPatter MAT

  ADD_CORS(getOOD_MATQuestion)
  ENDPOINT("GET", "/OOD/MAT", getOOD_MATQuestion) {

    auto obj_dto = Result_MAT::createShared();
    std::string path = "src/QuestionData/ObjectOrientedDesign/Matching.json";
    
    Matching MAT_question = Matching(path);

    obj_dto->questionTextMAT = MAT_question.getQuestionText();
    std::vector<std::string> Answers = MAT_question.getAnswers();
    std::vector<std::string> Definitions = MAT_question.getDefinitions();
    obj_dto->termA = Answers[0];
    obj_dto->termB = Answers[1];
    obj_dto->termC = Answers[2];
    obj_dto->termD = Answers[3];

    obj_dto->definitionA = Definitions[0];
    obj_dto->definitionB = Definitions[1];
    obj_dto->definitionC = Definitions[2];
    obj_dto->definitionD = Definitions[3];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET Object-Oriented_Design MAT

  ADD_CORS(getVC_MATQuestion)
  ENDPOINT("GET", "/VC/MAT", getVC_MATQuestion) {

    auto obj_dto = Result_MAT::createShared();
    std::string path = "src/QuestionData/VersionControl/Matching.json";
    
    Matching MAT_question = Matching(path);

    obj_dto->questionTextMAT = MAT_question.getQuestionText();
    std::vector<std::string> Answers = MAT_question.getAnswers();
    std::vector<std::string> Definitions = MAT_question.getDefinitions();
    obj_dto->termA = Answers[0];
    obj_dto->termB = Answers[1];
    obj_dto->termC = Answers[2];
    obj_dto->termD = Answers[3];

    obj_dto->definitionA = Definitions[0];
    obj_dto->definitionB = Definitions[1];
    obj_dto->definitionC = Definitions[2];
    obj_dto->definitionD = Definitions[3];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET VersionControl MAT

  ADD_CORS(getSE_MATQuestion)
  ENDPOINT("GET", "/SE/MAT", getSE_MATQuestion) {

    auto obj_dto = Result_MAT::createShared();
    std::string path = "src/QuestionData/SoftwareEngineering/Matching.json";
    
    Matching MAT_question = Matching(path);

    obj_dto->questionTextMAT = MAT_question.getQuestionText();
    std::vector<std::string> Answers = MAT_question.getAnswers();
    std::vector<std::string> Definitions = MAT_question.getDefinitions();
    obj_dto->termA = Answers[0];
    obj_dto->termB = Answers[1];
    obj_dto->termC = Answers[2];
    obj_dto->termD = Answers[3];

    obj_dto->definitionA = Definitions[0];
    obj_dto->definitionB = Definitions[1];
    obj_dto->definitionC = Definitions[2];
    obj_dto->definitionD = Definitions[3];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET SoftwareEngineering MAT

  ADD_CORS(validateMATAnswer)
  ENDPOINT("POST", "/{topic}/MAT/validate", validateMATAnswer,
         PATH(String, topic),
         BODY_DTO(Object<MultipleAnswersSubmission>, answerDto)) {

  std::string topicStr = topic->c_str();
  std::string path = "src/QuestionData/" + topicStr + "/Matching.json";

  Matching MAT_question(path);

  // answerDto->answers is a Vector<String>
  // Convert Vector<String> to std::vector<std::string>
  std::vector<std::string> userAnswers;
  for (auto &ans : *answerDto->answers) {
    userAnswers.push_back(ans->c_str());
  }

  bool isCorrect = MAT_question.validateAllAnswers(userAnswers);

  auto resultDto = ValidationResult::createShared();
  resultDto->isCorrect = isCorrect;

  return createDtoResponse(Status::CODE_200, resultDto);
}

};  // End of Controller

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* MAT_Controller_hpp */
