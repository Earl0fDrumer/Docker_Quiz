#ifndef SHAPE_DTO_hpp
#define SHAPE_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result : public oatpp::DTO {
  DTO_INIT(Result, DTO /* Extends */)

  DTO_FIELD(String, result);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* SHAPE_DTO_hpp */

