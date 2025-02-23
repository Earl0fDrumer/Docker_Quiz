#ifndef MC_QUESTION_HPP
#define MC_QUESTION_HPP

#include <string>
#include <vector>
#include "src/service/Question.hpp"

class MultipleChoice : public Question {
 private:
  std::vector<std::string> Answers;

 public:
  MultipleChoice(std::string path) : Question(path) {
    filePath = path;
    readDataFile();

    QuestionText = jsonFileData["questions"][0]["question"];
    CorrectAnswer = jsonFileData["questions"][0]["correct_answer"];
    Answers.push_back(jsonFileData["questions"][0]["answers"]["a"]);
    Answers.push_back(jsonFileData["questions"][0]["answers"]["b"]);
    Answers.push_back(jsonFileData["questions"][0]["answers"]["c"]);
    Answers.push_back(jsonFileData["questions"][0]["answers"]["d"]);
  }

  std::vector<std::string> getAnswers() const {
    return Answers;
  }

  std::string getCorrectAnswer() const {
    return CorrectAnswer;
  }

  // Validate user input and provide feedback
  // userAnswer should be "a", "b", "c", or "d"
  std::string validateAnswer(const std::string& userAnswer) {
    if (userAnswer == CorrectAnswer) {
      return "Correct!";
    } else {
      return "Incorrect. The correct answer is: " + CorrectAnswer;
    }
  }
};

#endif // MC_QUESTION_HPP
