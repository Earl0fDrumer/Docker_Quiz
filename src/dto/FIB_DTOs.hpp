#ifndef FIB_DTO_hpp
#define FIB_DTO_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result_FIB : public oatpp::DTO {
  DTO_INIT(Result_FIB, DTO /* Extends */)

  DTO_FIELD(String, questionTextFIB);  ///< The question text with blanks
  DTO_FIELD(Vector<String>::ObjectWrapper, wordBank); ///< The word bank
};

#include OATPP_CODEGEN_END(DTO)

#endif /* FIB_DTO_hpp */
