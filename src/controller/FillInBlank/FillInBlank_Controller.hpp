#ifndef FillInBlank_Controller_hpp
#define FillInBlank_Controller_hpp

#include "src/service/FillInBlank/FillInBlank_Question.hpp"
#include "src/dto/FIB_DTOs.hpp"
#include "dto/AnswerSubmission_DTO.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include <memory>

#include OATPP_CODEGEN_BEGIN(ApiController)

class FillInBlank_Controller : public oatpp::web::server::api::ApiController {
 public:
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
           BODY_DTO(Object<AnswerSubmission>, answerDto)) {

    // Convert oatpp::String to std::string using c_str()
    std::string topicStr = std::string(topic->c_str());
    std::string path = "src/QuestionData/" + topicStr + "/FillInBlank.json";

    FillInBlank question(path);
    std::string userAnswer = std::string(answerDto->answer->c_str());
    std::string validationMsg = question.validateAnswer(userAnswer);

    auto resultDto = ValidationResult::createShared();
    if (validationMsg == "Correct!") {
      resultDto->isCorrect = true;
    } else {
      resultDto->isCorrect = false;
      resultDto->correctAnswer = question.getCorrectAnswer().c_str();
    }

    return createDtoResponse(Status::CODE_200, resultDto);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* FillInBlank_Controller_hpp */
