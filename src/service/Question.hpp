#ifndef QUESTION_hpp
#define QUESTION_hpp

#include "src/service/json.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

class Question {
public:
  /**
   * Constructor to initialize the question with the file path
   * @param path - Path to the JSON file containing the question data
   */
  Question(const std::string& path) : filePath(path) {}

  /**
   * Reads and parses the data from the JSON file
   */
  void readDataFile() {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
      throw std::ios_base::failure("Error: Failed to open file: " + filePath);
    }

    inputFile >> jsonFileData;
    inputFile.close();
  }

  std::string getQuestionText() const {
    return QuestionText;
  }

  void setQuestionText(const std::string& text) {
    QuestionText = text;
  }

  std::string getCorrectAnswer() const {
    return CorrectAnswer;
  }

  void setCorrectAnswer(const std::string& answer) {
    CorrectAnswer = answer;
  }

  std::vector<std::string> getAnswers() const {
    return Answers;
  }

  void addAnswer(const std::string& answer) {
    Answers.push_back(answer);
  }

protected:
  std::string filePath;        ///< File path to the JSON data
  json jsonFileData;           ///< Parsed JSON data
  std::string QuestionText;    ///< The text of the question
  std::string CorrectAnswer;   ///< The correct answer
  std::vector<std::string> Answers;  ///< List of possible answers
};

#endif /* QUESTION_hpp */
