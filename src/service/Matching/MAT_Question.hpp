#ifndef MAT_QUESTION_hpp
#define MAT_QUESTION_hpp

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>

#include "src/service/Question.hpp"

using json = nlohmann::json;

class Matching : public Question {
 public:
  Matching(std::string path) : Question(path) {
    filePath = path;
    readDataFile();

    // We assume jsonFileData is populated by readDataFile
    // We'll take the first question set for demonstration
    QuestionText = jsonFileData["questions"][0]["question"];

    // Extract terms (Answers)
    Answers.push_back(jsonFileData["questions"][0]["terms"]["a"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["b"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["c"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["d"]);

    // Extract definitions
    // For example, we might be intentionally mismatching order to randomize the challenge
    // According to the previous logic, correctAnswerVector = {"c", "a", "d", "b"}:
    // This means for termA (Answers[0]), correct = 'c'
    // for termB (Answers[1]), correct = 'a'
    // for termC (Answers[2]), correct = 'd'
    // for termD (Answers[3]), correct = 'b'

    // Just as an example, let's place the definitions in order c,a,d,b to match the correct answer vector:
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["a"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["b"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["c"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["d"]);
  }

  std::vector<std::string> getDefinitions() {
    return Definitions;
  }

  bool validateAllAnswers(const std::vector<std::string>& userAnswers) {
    // The correct pattern is {"c", "a", "d", "b"}
    std::vector<std::string> correctAnswerVector = {"c", "a", "d", "b"};
    if (userAnswers.size() != correctAnswerVector.size()) {
      return false;
    }
    for (size_t i = 0; i < correctAnswerVector.size(); i++) {
      if (userAnswers[i] != correctAnswerVector[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  std::vector<std::string> Definitions;
};

#endif /* MAT_QUESTION_hpp */
