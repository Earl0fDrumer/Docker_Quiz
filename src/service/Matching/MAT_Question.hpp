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

    std::random_device rd;
    std::mt19937 g(rd());
    QuestionText = jsonFileData["questions"][0]["question"];
    Answers.push_back(jsonFileData["questions"][0]["terms"]["a"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["b"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["c"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["d"]);

    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["c"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["a"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["d"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["b"]);

  }

  std::vector<std::string> getDefinitions() {
    return Definitions;
  }

  // Validate user input and provide feedback
  // Expects a userAnswer vector with a series of letters.
  // Expects an index (this means there is a for loop running 4 times)
  // Returns Correct if the answer matches the correct answer.
  // Returns the correct answer otherwise.
  std::string validateAnswer(const std::string userAnswer[], int index) {
    if (userAnswer[index] != correctAnswerVector[index]) {
      return "Incorrect. The correct answer is: " + correctAnswerVector[index];
    } else {
      return "Correct!";
    }
  }

  bool validateAllAnswers(const std::vector<std::string>& userAnswers) {
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
  std::vector<std::string> correctAnswerVector = {"a", "b", "c", "d"};
};

#endif /* MAT_QUESTION_hpp */
