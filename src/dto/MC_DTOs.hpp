#ifndef MC_DTO_hpp
#define MC_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result_MC2 : public oatpp::DTO {
  DTO_INIT(Result_MC2, DTO /* Extends */)

  DTO_FIELD(String, questionText);
  DTO_FIELD(String, optionA);
  DTO_FIELD(String, optionB);
  DTO_FIELD(String, optionC);
  DTO_FIELD(String, optionD);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* MC_DTO_hpp */
