#ifndef RandomByType_hpp
#define RandomByType_hpp

#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include "src/service/json.hpp"
#include "src/service/Question.hpp"

class RandomByType {
 public:
  /**
   * Constructor
   */
  RandomByType(const std::string& teamFolder)
      : teamFolder(teamFolder) {}

  /**
   * Select a random question file and load questions.
   */
  std::vector<Question> getRandomQuestions() {
    // List of question file types
    std::vector<std::string> questionFiles = {"MultipleChoice.json", "TrueFalse.json", "FillInBlank.json", "Matching.json"};

    // Randomly select a question file
    static std::mt19937 gen(static_cast<unsigned long>(std::time(nullptr)));
    std::uniform_int_distribution<> dist(0, questionFiles.size() - 1);
    std::string selectedFile = questionFiles[dist(gen)];

    // Construct the file path
    std::string filePath = "src/QuestionData/" + teamFolder + "/" + selectedFile;

    // Load questions using existing logic
    std::ifstream file(filePath);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file: " + filePath);
    }

    nlohmann::json jsonData;
    file >> jsonData;

    if (!jsonData.contains("questions")) {
      throw std::runtime_error("Invalid JSON format: Missing 'questions' field");
    }

    // Create questions
    std::vector<Question> questions;
    for (const auto& item : jsonData["questions"]) {
      Question question(filePath);

      if (item.contains("question")) {
        question.setQuestionText(item["question"].get<std::string>());
      }
      if (item.contains("correct_answer")) {
        question.setCorrectAnswer(item["correct_answer"].get<std::string>());
      }
      if (item.contains("options")) {
        for (const auto& option : item["options"]) {
          question.addAnswer(option.get<std::string>());
        }
      }
      if (item.contains("word_bank")) {
        for (const auto& word : item["word_bank"]) {
          question.addAnswer(word.get<std::string>());
        }
      }
      questions.push_back(question);
    }

    return questions;
  }

 private:
  std::string teamFolder;
};

#endif /* RandomByType_hpp */
