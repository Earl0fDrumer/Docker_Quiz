#ifndef RandomByType_hpp
#define RandomByType_hpp

#include <string>
#include <vector>
#include "src/service/json.hpp"
#include "src/service/Question.hpp"
#include <fstream>  
#include <stdexcept>

class RandomByType {
private:
  std::string filePath;

public:
  /**
   * Constructor
   * @param filePath - Path to the JSON file containing questions
   */
  RandomByType(const std::string& filePath) : filePath(filePath) {}

  /**
   * Load questions from the JSON file.
   * @return A vector of Question objects
   */
  std::vector<Question> loadQuestions() {
    std::vector<Question> questions;
    std::ifstream file(filePath);

    // Validate file opening
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file: " + filePath);
    }

    nlohmann::json jsonData;
    file >> jsonData;

    // Validate JSON structure
    if (!jsonData.contains("questions")) {
      throw std::runtime_error("Invalid JSON format: Missing 'questions' field");
    }

    for (const auto& item : jsonData["questions"]) {
      Question question(filePath);  // Create a Question object for the current question
      question.readDataFile();      // Parse the question data from the file

      // Populate fields dynamically
      if (item.contains("question")) {
        question.setQuestionText(item["question"].get<std::string>());
      }
      if (item.contains("correct_answer")) {
        question.setCorrectAnswer(item["correct_answer"].get<std::string>());
      }
      if (item.contains("word_bank")) {
        for (const auto& word : item["word_bank"]) {
          question.addAnswer(word.get<std::string>());
        }
      }
      if (item.contains("options")) {
        for (const auto& option : item["options"]) {
          question.addAnswer(option.get<std::string>());
        }
      }
      if (item.contains("terms")) {
        for (const auto& term : item["terms"]) {
          question.addAnswer(term.get<std::string>());
        }
      }
      if (item.contains("definitions")) {
        for (const auto& definition : item["definitions"]) {
          question.addAnswer(definition.get<std::string>());
        }
      }

      questions.push_back(question);
    }

    return questions;
  }
};

#endif /* RandomByType_hpp */
