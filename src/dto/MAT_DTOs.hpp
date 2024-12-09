#ifndef MAT_DTO_hpp
#define MAT_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result_MAT : public oatpp::DTO {
  DTO_INIT(Result_MAT, DTO /* Extends */)

  DTO_FIELD(String, topic);
  DTO_FIELD(String, questionTextMAT);

  DTO_FIELD(String, termA);
  DTO_FIELD(String, termB);
  DTO_FIELD(String, termC);
  DTO_FIELD(String, termD);

  DTO_FIELD(String, definitionA);
  DTO_FIELD(String, definitionB);
  DTO_FIELD(String, definitionC);
  DTO_FIELD(String, definitionD);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* MAT_DTO_hpp */
