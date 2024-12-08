#ifndef FillInBlank_Controller_hpp
#define FillInBlank_Controller_hpp

#include "src/service/FillInBlank/FillInBlank_Question.hpp"
#include "src/dto/FIB_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "dto/AnswerSubmission_DTO.hpp"
#include <memory>

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class FillInBlank_Controller : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  FillInBlank_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  // Endpoint for Design Patterns Fill-in-the-Blank question
  ADD_CORS(getDP_FIBQuestion)
  ENDPOINT("GET", "/DP/FIB", getDP_FIBQuestion) {
    auto dto = Result_FIB::createShared();
    std::string path = "src/QuestionData/DesignPatterns/FillInBlank.json";

    FillInBlank question(path);

    dto->questionTextFIB = question.getQuestionText();
    dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

    for (const auto& word : question.getWordBank()) {
      dto->wordBank->push_back(word);
    }

    return createDtoResponse(Status::CODE_200, dto);
  }

  // Endpoint for Object-Oriented Design Fill-in-the-Blank question
  ADD_CORS(getOOD_FIBQuestion)
  ENDPOINT("GET", "/OOD/FIB", getOOD_FIBQuestion) {
    auto dto = Result_FIB::createShared();
    std::string path = "src/QuestionData/ObjectOrientedDesign/FillInBlank.json";

    FillInBlank question(path);

    dto->questionTextFIB = question.getQuestionText();
    dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

    for (const auto& word : question.getWordBank()) {
      dto->wordBank->push_back(word);
    }

    return createDtoResponse(Status::CODE_200, dto);
  }

  // Endpoint for Software Engineering Fill-in-the-Blank question
  ADD_CORS(getSE_FIBQuestion)
  ENDPOINT("GET", "/SE/FIB", getSE_FIBQuestion) {
    auto dto = Result_FIB::createShared();
    std::string path = "src/QuestionData/SoftwareEngineering/FillInBlank.json";

    FillInBlank question(path);

    dto->questionTextFIB = question.getQuestionText();
    dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

    for (const auto& word : question.getWordBank()) {
      dto->wordBank->push_back(word);
    }

    return createDtoResponse(Status::CODE_200, dto);
  }

  // Endpoint for Version Control Fill-in-the-Blank question
  ADD_CORS(getVC_FIBQuestion)
  ENDPOINT("GET", "/VC/FIB", getVC_FIBQuestion) {
    auto dto = Result_FIB::createShared();
    std::string path = "src/QuestionData/VersionControl/FillInBlank.json";

    FillInBlank question(path);

    dto->questionTextFIB = question.getQuestionText();
    dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

    for (const auto& word : question.getWordBank()) {
      dto->wordBank->push_back(word);
    }

    return createDtoResponse(Status::CODE_200, dto);
  }

  // ===========================
  // NEW POST ENDPOINT FOR VALIDATION
  // ===========================

  ADD_CORS(validateFIBAnswer)
  ENDPOINT("POST", "/{topic}/FIB/validate", validateFIBAnswer,
           PATH(String, topic),
           BODY_DTO(AnswerSubmission::ObjectWrapper, answerDto)) {

    try {
      std::string path = "src/QuestionData/" + topic->std_str() + "/FillInBlank.json";
      FillInBlank question(path);

      auto resultDto = ValidationResult::createShared();
      std::string validationMsg = question.validateAnswer(answerDto->answer->std_str());

      if (validationMsg == "Correct!") {
        resultDto->isCorrect = true;
      } else {
        resultDto->isCorrect = false;
        // getCorrectAnswer() must exist in FillInBlank_Question.hpp
        resultDto->correctAnswer = question.getCorrectAnswer().c_str();
      }

      return createDtoResponse(Status::CODE_200, resultDto);
    } catch (...) {
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }

};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* FillInBlank_Controller_hpp */
