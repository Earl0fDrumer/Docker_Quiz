#ifndef TF_DTO_hpp
#define TF_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result_TF : public oatpp::DTO {
  DTO_INIT(Result_TF, DTO /* Extends */)

  DTO_FIELD(String, questionTextTF);
  DTO_FIELD(String, trueText);
  DTO_FIELD(String, falseText);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TF_DTO_hpp */
