#ifndef SE_Controller_hpp
#define SE_Controller_hpp

#include <memory>

#include "../service/Question.hpp"
#include "../dto/SeleneDTOs.hpp"
#include "../dto/MultipleChoiceDTOs.hpp"
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
    auto dto = Result::createShared();

    MultipleChoice question;

    dto->questionText = question.getQuestionText();
    dto->correctAnswer = question.getCorrectAnswer();
    return createDtoResponse(Status::CODE_200, dto);
  }  // GET
};  // End of SEController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* SE_Controller_hpp */
