#ifndef VC_Controller_hpp
#define VC_Controller_hpp

#include <memory>
#include "src/service/VersionControl/VC_MC_Question.hpp"
#include "src/dto/VersionControl/VCMC_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class VCController : public oatpp::web::server::api::ApiController {
 public:
  VCController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getMCQuestion)  // Allow cross-origin requests
  ENDPOINT("GET", "/VC/MC", getMCQuestion) {
    try {
      auto dto = VCResult_MC::createShared();  // Create DTO instance

      VC_MC_Question question;  // Instantiate the question service class

      // Populate the DTO with question data
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
      OATPP_LOGE("VCController", "Error: %s", e.what());
      return createResponse(Status::CODE_500, "Internal Server Error: " + std::string(e.what()));
    } catch (...) {
      OATPP_LOGE("VCController", "Unknown error occurred");
      return createResponse(Status::CODE_500, "Internal Server Error");
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* VC_Controller_hpp */

