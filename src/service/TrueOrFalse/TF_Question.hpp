#include <string>

#include "src/service/Question.hpp"

class TrueOrFalse : public Question {
 public:
  TrueOrFalse(std::string path) : Question(path) {
  filePath = path;
  readDataFile();

  QuestionText = jsonFileData["questions"][0]["question"];
  CorrectAnswer = jsonFileData["questions"][0]["correct_answer"];
  Answers.push_back(jsonFileData["questions"][0]["answers"]["a"]);
  Answers.push_back(jsonFileData["questions"][0]["answers"]["b"]);
  }
};
