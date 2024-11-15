#ifndef VC_MC_DTO_hpp
#define VC_MC_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class VCResult_MC : public oatpp::DTO {
  DTO_INIT(VCResult_MC, DTO /* Extends */)

  DTO_FIELD(String, questionText);  // The question text
  DTO_FIELD(String, optionA);       // Option A
  DTO_FIELD(String, optionB);       // Option B
  DTO_FIELD(String, optionC);       // Option C
  DTO_FIELD(String, optionD);       // Option D
};

#include OATPP_CODEGEN_END(DTO)

#endif /* VC_MC_DTO_hpp */
