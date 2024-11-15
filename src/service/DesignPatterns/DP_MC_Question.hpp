#ifndef DP_MC_Question_hpp
#define DP_MC_Question_hpp

#include "json.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

class DP_MC_Question {
public:
  DP_MC_Question() {
    readDataFile();

    // Here we load the first question for simplicity
    const auto& firstQuestion = jsonFileData["questions"][0];
    QuestionText = firstQuestion["question"];
    CorrectAnswer = firstQuestion["correct_answer"];
    Answers.push_back(firstQuestion["answers"]["a"]);
    Answers.push_back(firstQuestion["answers"]["b"]);
    Answers.push_back(firstQuestion["answers"]["c"]);
    Answers.push_back(firstQuestion["answers"]["d"]);
  }

  void readDataFile() {
    std::string filePath = "src/QuestionData/DesignPatterns/MultipleChoice.json";
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
      throw std::ios_base::failure("Error: failed to open file: " + filePath);
    }
    inputFile >> jsonFileData;
    inputFile.close();
  }

  std::string getQuestionText() {
    return QuestionText;
  }

  std::vector<std::string> getAnswers() {
    return Answers;
  }

private:
  json jsonFileData;
  std::string QuestionText;
  std::string CorrectAnswer;
  std::vector<std::string> Answers;
};

#endif /* DP_MC_Question_hpp */
