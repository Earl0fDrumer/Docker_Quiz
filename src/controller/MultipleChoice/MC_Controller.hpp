#ifndef MC_Controller_hpp
#define MC_Controller_hpp

#include <memory>
#include "src/service/MultipleChoice/MC_Question.hpp"
#include "src/dto/MC_DTOs.hpp"
#include "dto/AnswerSubmission_DTO.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class MC_Controller : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  MC_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getDP_MCQuestion)
  ENDPOINT("GET", "/DP/MC", getDP_MCQuestion) {
    auto dto = Result_MC::createShared();
    std::string path = "src/QuestionData/DesignPatterns/MultipleChoice.json";

    MultipleChoice question(path);
    dto->questionTextMC = question.getQuestionText();
    std::vector<std::string> answers = question.getAnswers();

    if (answers.size() < 4) {
      throw std::runtime_error("Insufficient answers provided in question");
    }

    dto->optionA = answers[0];
    dto->optionB = answers[1];
    dto->optionC = answers[2];
    dto->optionD = answers[3];

    return createDtoResponse(Status::CODE_200, dto);
  }

  ADD_CORS(getOOD_MCQuestion)
  ENDPOINT("GET", "/OOD/MC", getOOD_MCQuestion) {
    auto dto = Result_MC::createShared();
    std::string path = "src/QuestionData/ObjectOrientedDesign/MultipleChoice.json";

    MultipleChoice question(path);
    dto->questionTextMC = question.getQuestionText();
    std::vector<std::string> answers = question.getAnswers();

    if (answers.size() < 4) {
      throw std::runtime_error("Insufficient answers provided in question");
    }

    dto->optionA = answers[0];
    dto->optionB = answers[1];
    dto->optionC = answers[2];
    dto->optionD = answers[3];

    return createDtoResponse(Status::CODE_200, dto);
  }

  ADD_CORS(getSE_MCQuestion)
  ENDPOINT("GET", "/SE/MC", getSE_MCQuestion) {
    auto dto = Result_MC::createShared();
    std::string path = "src/QuestionData/SoftwareEngineering/MultipleChoice.json";

    MultipleChoice question(path);
    dto->questionTextMC = question.getQuestionText();
    std::vector<std::string> answers = question.getAnswers();

    if (answers.size() < 4) {
      throw std::runtime_error("Insufficient answers provided in question");
    }

    dto->optionA = answers[0];
    dto->optionB = answers[1];
    dto->optionC = answers[2];
    dto->optionD = answers[3];

    return createDtoResponse(Status::CODE_200, dto);
  }

  ADD_CORS(getVC_MCQuestion)
  ENDPOINT("GET", "/VC/MC", getVC_MCQuestion) {
    auto dto = Result_MC::createShared();
    std::string path = "src/QuestionData/VersionControl/MultipleChoice.json";

    MultipleChoice question(path);
    dto->questionTextMC = question.getQuestionText();
    std::vector<std::string> answers = question.getAnswers();

    if (answers.size() < 4) {
      throw std::runtime_error("Insufficient answers provided in question");
    }

    dto->optionA = answers[0];
    dto->optionB = answers[1];
    dto->optionC = answers[2];
    dto->optionD = answers[3];

    return createDtoResponse(Status::CODE_200, dto);
  }

  // NEW POST Endpoint for MC Validation
  ADD_CORS(validateMCAnswer)
  ENDPOINT("POST", "/{topic}/MC/validate", validateMCAnswer,
           PATH(String, topic),
           BODY_DTO(Object<AnswerSubmission>, answerDto)) {

    // Convert oatpp::String to std::string using c_str()
    std::string topicStr = std::string(topic->c_str());
    std::string path = "src/QuestionData/" + topicStr + "/MultipleChoice.json";

    try {
      MultipleChoice question(path);
      std::string userAnswer = std::string(answerDto->answer->c_str());
      std::string validationMsg = question.validateAnswer(userAnswer);

      auto resultDto = ValidationResult::createShared();
      if (validationMsg == "Correct!") {
        resultDto->isCorrect = true;
      } else {
        resultDto->isCorrect = false;
        // Return correct answer key (e.g., "b")
        resultDto->correctAnswer = question.getCorrectAnswer().c_str();
      }

      return createDtoResponse(Status::CODE_200, resultDto);
    } catch (const std::exception &e) {
      OATPP_LOGE("validateMCAnswer", "Exception: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }

};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* MC_Controller_hpp */
