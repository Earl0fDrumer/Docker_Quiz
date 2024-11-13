#ifndef SE_Controller_hpp
#define SE_Controller_hpp

#include <memory>

#include "src/service/SoftwareEngineering/MC_Question.hpp"
//#include "src/dto/SeleneDTOs.hpp"
#include "src/dto/SoftwareEngineering/SoftEnggMC_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class SEController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  SEController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getMCQuestion)  // Needed to allow for cross domain access
  ENDPOINT("GET", "/SE/MC", getMCQuestion) {
    auto dto = Result_MC::createShared();

    MultipleChoice question;

    dto->questionText = question.getQuestionText();
    std::vector<std::string> Answers = question.getAnswers();
    dto->optionA = Answers[0];
    dto->optionB = Answers[1];
    dto->optionC = Answers[2];
    dto->optionD = Answers[3];

    return createDtoResponse(Status::CODE_200, dto);
  }  // GET
};  // End of SEController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* SE_Controller_hpp */
