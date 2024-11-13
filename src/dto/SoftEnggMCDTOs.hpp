#ifndef SOFT_ENGG_MC_DTO_hpp
#define SOFT_ENGG_MC_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result : public oatpp::DTO {
  DTO_INIT(Result, DTO /* Extends */)

  DTO_FIELD(String, questionText);
  DTO_FIELD(String, correctAnswer);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* SOFT_ENGG_MC_DTO_hpp */
