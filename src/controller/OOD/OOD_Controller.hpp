#ifndef OOD_Controller_hpp
#define OOD_Controller_hpp

#include <memory>

#include "src/service/MC_Question.hpp"
#include "src/dto/SeleneDTOs.hpp"
#include "src/dto/MC_DTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class OOD_Controller : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  OOD_Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getMCQuestion2)  // Needed to allow for cross domain access
  ENDPOINT("GET", "/OOD/MC", getMCQuestion2) {

    auto obj_dto = Result_MC2::createShared();
    //MultipleChoice question;
    std::string path = "src/QuestionData/ObjectOrientedDesign/MultipleChoice.json";
    
    auto obj_question = new MultipleChoice2(path);

    obj_dto->questionText = obj_question->getQuestionText();
    std::vector<std::string> Answers = obj_question->getAnswers();
    obj_dto->optionA = Answers[0];
    obj_dto->optionB = Answers[1];
    obj_dto->optionC = Answers[2];
    obj_dto->optionD = Answers[3];

    return createDtoResponse(Status::CODE_200, obj_dto);
  }  // GET

};  // End of SEController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* OOD_Controller_hpp */
