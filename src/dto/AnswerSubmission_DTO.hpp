#ifndef ANSWERSUBMISSION_DTO_HPP
#define ANSWERSUBMISSION_DTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AnswerSubmission : public oatpp::DTO {
  DTO_INIT(AnswerSubmission, DTO)
  DTO_FIELD(String, answer);
};

class ValidationResult : public oatpp::DTO {
  DTO_INIT(ValidationResult, DTO)
  DTO_FIELD(Boolean, isCorrect);
  DTO_FIELD(String, correctAnswer); // Only used if isCorrect = false
};

class MultipleAnswersSubmission : public oatpp::DTO {
  DTO_INIT(MultipleAnswersSubmission, DTO)
  DTO_FIELD(Vector<String>, answers); // A vector of answers (strings)
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ANSWERSUBMISSION_DTO_HPP */
