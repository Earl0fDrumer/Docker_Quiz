#ifndef Topics_Controller_hpp
#define Topics_Controller_hpp

#include <memory>

#include "src/service/Topics.hpp"
#include "src/dto/TopicsDTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class TopicsController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  TopicsController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

  ADD_CORS(getTopics)  // Needed to allow for cross domain access
  ENDPOINT("GET", "/topics", getTopics) {
    auto dto = Result_TOPIC::createShared();

    Topics topic = Topics();
    std::vector<std::string> TopicsList = topic.getTopicsList();

    dto->topic1 = TopicsList[0];
    dto->topic2 = TopicsList[1];
    dto->topic3 = TopicsList[2];
    dto->topic4 = TopicsList[3];
    return createDtoResponse(Status::CODE_200, dto);
  }  // GET
};  // End of TopicsController

#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* Topics_Controller_hpp */
