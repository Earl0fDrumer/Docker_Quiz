#ifndef SOFT_ENGG_MC_DTO_hpp
#define SOFT_ENGG_MC_DTO_hpp

//#include "src/dto/SeleneDTOs.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ResultSE_MC : public oatpp::DTO {
  DTO_INIT(ResultSE_MC, DTO /* Extends */)

  // DTO_FIELD(String, result);
  DTO_FIELD(String, questionText);
  DTO_FIELD(String, correctAnswer);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* SOFT_ENGG_MC_DTO_hpp */
