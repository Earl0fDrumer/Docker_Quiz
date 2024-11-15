#ifndef DPController_hpp
#define DPController_hpp

#include <memory>

#include "src/service/DesignPatterns/DP_MC_Question.hpp"
#include "src/dto/DesignPatterns/DP_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class DPController : public oatpp::web::server::api::ApiController {
public:
  DPController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getMCQuestion) // Allow cross-domain requests
  ENDPOINT("GET", "/DP/MC", getMCQuestion) {
    try {
      auto dto = DPResult_MC::createShared();
      DP_MC_Question question;

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
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* DPController_hpp */
