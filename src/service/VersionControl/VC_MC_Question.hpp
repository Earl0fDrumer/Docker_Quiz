#ifndef VC_MC_Question_hpp
#define VC_MC_Question_hpp

#include "src/service/VersionControl/json.hpp"  // Include nlohmann json library

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

class VC_MC_Question {
 public:
  VC_MC_Question() {
    readDataFile();

    // Load the first question for simplicity (extend later for multiple questions)
    const auto& firstQuestion = jsonFileData["questions"][0];
    QuestionText = firstQuestion["question"];
    CorrectAnswer = firstQuestion["correct_answer"];
    Answers.push_back(firstQuestion["answers"]["a"]);
    Answers.push_back(firstQuestion["answers"]["b"]);
    Answers.push_back(firstQuestion["answers"]["c"]);
    Answers.push_back(firstQuestion["answers"]["d"]);
  }

  void readDataFile() {
    std::string filePath = "src/QuestionData/VersionControl/MultipleChoice.json";

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
      throw std::ios_base::failure("Error: failed to open file: " + filePath);
    }

    inputFile >> jsonFileData;
    inputFile.close();
  }

  std::string getQuestionText() {
    if (simulateError) {
      throw std::runtime_error("Simulated question retrieval error");
    }
    return QuestionText;
  }

  std::string getCorrectAnswer() {
    return CorrectAnswer;
  }

  std::vector<std::string> getAnswers() {
    return Answers;
  }

  // Simulate error for testing purposes
  void setSimulateError(bool value) {
    simulateError = value;
  }

 private:
  json jsonFileData;
  std::string QuestionText;
  std::string CorrectAnswer;
  std::vector<std::string> Answers;
  bool simulateError = false;  // Default to false, can be toggled for testing
};

#endif /* VC_MC_Question_hpp */
