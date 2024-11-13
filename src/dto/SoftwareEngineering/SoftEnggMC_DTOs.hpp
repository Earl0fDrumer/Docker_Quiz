#ifndef SOFT_ENGG_MC_DTO_hpp
#define SOFT_ENGG_MC_DTO_hpp

//#include "src/dto/SeleneDTOs.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result_MC : public oatpp::DTO {
  DTO_INIT(Result_MC, DTO /* Extends */)

  // DTO_FIELD(String, result);
  DTO_FIELD(String, questionText);
  DTO_FIELD(String, optionA);
  DTO_FIELD(String, optionB);
  DTO_FIELD(String, optionC);
  DTO_FIELD(String, optionD);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* SOFT_ENGG_MC_DTO_hpp */
