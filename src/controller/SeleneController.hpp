#ifndef Controller_hpp
#define Controller_hpp

#include <memory>

#include "../dto/SeleneDTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class SeleneController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  SeleneController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getSelene)  // Needed to allow for cross domain access
  ENDPOINT("GET", "/selene", getSelene) {
    auto dto = Result::createShared();
    dto->result = "Selene";
    return createDtoResponse(Status::CODE_200, dto);
  }  // GET
};  // End of SeleneController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* Controller_hpp */
