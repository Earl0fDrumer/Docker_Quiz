#ifndef TOPIC_DTO_hpp
#define TOPIC_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result_TOPIC : public oatpp::DTO {
  DTO_INIT(Result_TOPIC, DTO /* Extends */)

  DTO_FIELD(String, topic1);
  DTO_FIELD(String, topic2);
  DTO_FIELD(String, topic3);
  DTO_FIELD(String, topic4);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TOPIC_DTO_hpp */
