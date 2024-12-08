#ifndef FILLINBLANK_QUESTION_HPP
#define FILLINBLANK_QUESTION_HPP

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "src/service/Question.hpp"


using json = nlohmann::json;

class FillInBlank : public Question {
 public:
  // Constructor to initialize and read data
  FillInBlank(std::string path) : Question(path) {
    filePath = path;
    readDataFile();

    // Parse question text
    QuestionText = jsonFileData["questions"][0]["question"];

    // Parse correct answer
    CorrectAnswer = jsonFileData["questions"][0]["correct_answer"];

    // Parse word bank
    for (const auto& word : jsonFileData["questions"][0]["word_bank"]) {
      WordBank.push_back(word);
    }
  }

  // Get the word bank for the question
  std::vector<std::string> getWordBank() const {
    return WordBank;
  }

  // Validate user input and provide feedback
  std::string validateAnswer(const std::string& userAnswer) {
    if (std::find(WordBank.begin(), WordBank.end(),
    userAnswer) == WordBank.end()) {
      return "Error: Your answer must be one of the words in the word bank.";
    }

    if (userAnswer == CorrectAnswer) {
      return "Correct!";
    } else {
      return "Incorrect. The correct answer is: " + CorrectAnswer;
    }
  }

 private:
  std::vector<std::string> WordBank;  // Holds the word bank options
};

#endif
