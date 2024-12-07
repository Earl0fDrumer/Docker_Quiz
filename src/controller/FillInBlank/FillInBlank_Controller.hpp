#ifndef FillInBlank_Controller_hpp
#define FillInBlank_Controller_hpp

#include "src/service/FillInBlank/FillInBlank_Question.hpp"
#include "src/dto/FIB_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
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
    try {
      auto dto = Result_FIB::createShared();  // Updated DTO class name
      std::string path = "src/QuestionData/DesignPatterns/FillInBlank.json";

      FillInBlank question(path);

      dto->questionTextFIB = question.getQuestionText();
      dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

      for (const auto& word : question.getWordBank()) {
        dto->wordBank->push_back(word);
      }

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("DPController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    } catch (...) {
      OATPP_LOGE("DPController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }

  // Endpoint for Object-Oriented Design Fill-in-the-Blank question
  ADD_CORS(getOOD_FIBQuestion)
  ENDPOINT("GET", "/OOD/FIB", getOOD_FIBQuestion) {
    try {
      auto dto = Result_FIB::createShared();  // Updated DTO class name
      std::string path = "src/QuestionData/ObjectOrientedDesign/FillInBlank.json";

      FillInBlank question(path);

      dto->questionTextFIB = question.getQuestionText();
      dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

      for (const auto& word : question.getWordBank()) {
        dto->wordBank->push_back(word);
      }

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("OODController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    } catch (...) {
      OATPP_LOGE("OODController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }

  // Endpoint for Software Engineering Fill-in-the-Blank question
  ADD_CORS(getSE_FIBQuestion)
  ENDPOINT("GET", "/SE/FIB", getSE_FIBQuestion) {
    try {
      auto dto = Result_FIB::createShared();  // Updated DTO class name
      std::string path = "src/QuestionData/SoftwareEngineering/FillInBlank.json";

      FillInBlank question(path);

      dto->questionTextFIB = question.getQuestionText();
      dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

      for (const auto& word : question.getWordBank()) {
        dto->wordBank->push_back(word);
      }

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("SEController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    } catch (...) {
      OATPP_LOGE("SEController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }

  // Endpoint for Version Control Fill-in-the-Blank question
  ADD_CORS(getVC_FIBQuestion)
  ENDPOINT("GET", "/VC/FIB", getVC_FIBQuestion) {
    try {
      auto dto = Result_FIB::createShared();  // Updated DTO class name
      std::string path = "src/QuestionData/VersionControl/FillInBlank.json";

      FillInBlank question(path);

      dto->questionTextFIB = question.getQuestionText();
      dto->wordBank = oatpp::Vector<oatpp::String>::createShared();

      for (const auto& word : question.getWordBank()) {
        dto->wordBank->push_back(word);
      }

      return createDtoResponse(Status::CODE_200, dto);
    } catch (const std::exception& e) {
      OATPP_LOGE("VCController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error");
    } catch (...) {
      OATPP_LOGE("VCController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* FillInBlank_Controller_hpp */
