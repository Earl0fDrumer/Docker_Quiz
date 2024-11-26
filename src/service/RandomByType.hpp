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
        try {
            file >> jsonData;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()));
        }

        // Validate JSON structure
        if (!jsonData.contains("questions")) {
            throw std::runtime_error("Invalid JSON format: Missing 'questions' field");
        }

        for (const auto& item : jsonData["questions"]) {
            Question question(filePath);

            // Common parsing for question text
            if (item.contains("question")) {
                question.setQuestionText(item["question"].get<std::string>());
            }

            // Dynamically handle different question types
            if (item.contains("word_bank")) {
                // Fill in the Blank
                for (const auto& word : item["word_bank"]) {
                    question.addAnswer(word.get<std::string>());
                }
                if (item.contains("correct_answer")) {
                    question.setCorrectAnswer(item["correct_answer"].get<std::string>());
                }
            }
            else if (item.contains("answers")) {
                // Multiple Choice or True/False
                auto answersObj = item["answers"];
                if (answersObj.is_object()) {
                    // Multiple Choice or True/False
                    for (auto& [key, value] : answersObj.items()) {
                        question.addAnswer(value.get<std::string>());
                    }
                    if (item.contains("correct_answer")) {
                        question.setCorrectAnswer(item["correct_answer"].get<std::string>());
                    }
                }
            }
            else if (item.contains("terms") && item.contains("definitions")) {
                // Matching
                auto terms = item["terms"];
                auto definitions = item["definitions"];
                
                for (auto& [key, term] : terms.items()) {
                    question.addAnswer(term.get<std::string>());
                }
                for (auto& [key, definition] : definitions.items()) {
                    question.addAnswer(definition.get<std::string>());
                }
            }

            questions.push_back(question);
        }

        return questions;
    }
};

#endif /* RandomByType_hpp */
