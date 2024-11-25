#ifndef QUESTION_hpp
#define QUESTION_hpp

#include "src/service/json.hpp"
#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

class Question {
 public:  
  Question(std::string path) : filePath(path) {};

  void readDataFile() {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
      throw std::ios_base::failure("Error: Failed to open file: " + filePath);
    }

    inputFile >> jsonFileData;
    inputFile.close();
  }

  std::string getQuestionText() {
    return QuestionText;
  }

  std::string getCorrectAnswer() {
    return CorrectAnswer;
  }

  std::vector<std::string> getAnswers() {
    return Answers;
  }

 protected:
  std::string filePath;
  json jsonFileData;
  std::string QuestionText;
  std::string CorrectAnswer;
  std::vector<std::string> Answers;
};

#endif /* QUESTION_hpp */