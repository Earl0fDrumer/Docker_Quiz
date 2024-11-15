#ifndef VC_Controller_hpp
#define VC_Controller_hpp

#include <memory>

#include "src/service/VersionControl/VC_MC_Question.hpp"  // Service for VC questions
#include "src/dto/VersionControl/VCMC_DTOs.hpp"           // DTOs for VC
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class VCController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  VCController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getMCQuestion)  // Allow cross-domain access
  ENDPOINT("GET", "/VC/MC", getMCQuestion) {
    auto dto = VCResult_MC::createShared();  // Replace with your DTO

    VC_MC_Question question;  // Instance of your question logic class

    // Fetch the question details
    dto->questionText = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();

    // Assign answers to DTO fields
    dto->optionA = Answers[0];
    dto->optionB = Answers[1];
    dto->optionC = Answers[2];
    dto->optionD = Answers[3];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET
};  // End of VCController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* VC_Controller_hpp */
