#ifndef RandomByType_hpp
#define RandomByType_hpp

#include <string>
#include <vector>
#include <random>
#include <unordered_map>
#include "src/service/json.hpp"
#include "src/service/Question.hpp"
#include <fstream>
#include <stdexcept>

class RandomByType {
private:
    std::string topicFolder;

public:
    RandomByType(const std::string& topicFolder) : topicFolder(topicFolder) {}

    // Map topic codes to folder names
    static std::string mapTopicToFolder(const std::string& topicCode) {
        static const std::unordered_map<std::string, std::string> topicFolderMap = {
            {"SE", "SoftwareEngineering"},
            {"DP", "DesignPatterns"},
            {"VC", "VersionControl"},
            {"OOP", "ObjectOrientedDesign"}
        };

        auto it = topicFolderMap.find(topicCode);
        if (it != topicFolderMap.end()) {
            return it->second;
        }
        throw std::invalid_argument("Invalid topic code");
    }

    // Select a random question file
    static std::string selectRandomQuestionFile() {
        static const std::vector<std::string> questionFiles = {
            "MultipleChoice.json", "TrueFalse.json", "FillInBlank.json", "Matching.json"
        };

        thread_local std::mt19937 gen(static_cast<unsigned long>(std::time(nullptr)));
        std::uniform_int_distribution<> dist(0, questionFiles.size() - 1);
        return questionFiles[dist(gen)];
    }

    // Load questions from a file
    std::vector<Question> loadQuestions(const std::string& filePath) const {
        std::vector<Question> questions;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        nlohmann::json jsonData;
        file >> jsonData;

        if (!jsonData.contains("questions")) {
            throw std::runtime_error("Invalid JSON format: Missing 'questions' field");
        }

        for (const auto& item : jsonData["questions"]) {
            Question question(filePath);

            if (item.contains("question")) {
                question.setQuestionText(item["question"].get<std::string>());
            }

            if (item.contains("word_bank")) {
                // Fill-in-the-Blank Question
                for (const auto& word : item["word_bank"]) {
                    question.addAnswer(word.get<std::string>());
                }
            } else if (item.contains("answers")) {
                auto answersObj = item["answers"];

                if (answersObj.size() == 2) {
                    // True/False Question
                    for (auto& [key, value] : answersObj.items()) {
                        question.addAnswer(value.get<std::string>());
                    }
                } else if (answersObj.size() > 2) {
                    // Multiple Choice Question
                    for (auto& [key, value] : answersObj.items()) {
                        question.addAnswer(value.get<std::string>());
                    }
                } else {
                    throw std::runtime_error("Invalid question format: 'answers' must have at least 2 entries.");
                }
            } else if (item.contains("terms") && item.contains("definitions")) {
                // Matching Question
                for (const auto& term : item["terms"]) {
                    question.addAnswer(term.get<std::string>());
                }
                for (const auto& definition : item["definitions"]) {
                    question.addAnswer(definition.get<std::string>());
                }
            }

            if (item.contains("correct_answer")) {
                question.setCorrectAnswer(item["correct_answer"].get<std::string>());
            }

            questions.push_back(question);
        }

        return questions;
    }
};

#endif /* RandomByType_hpp */
