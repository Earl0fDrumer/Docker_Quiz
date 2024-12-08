#ifndef RandomRequest_hpp
#define RandomRequest_hpp

#include <string>
#include <vector>
#include <random>
#include <unordered_map>
#include "src/service/json.hpp"
#include "src/service/Question.hpp"
#include <fstream>
#include <stdexcept>

class RandomRequest {
private:
    std::string topicFolder;

public:
    // Static variables for overriding randomness during testing
    static std::string testSelectedFile;  // Override for file selection
    static std::string testSelectedTopic; // Override for topic selection

    // Constructor to set the topic folder
    RandomRequest(const std::string& topicFolder) : topicFolder(topicFolder) {}

    // Map topic codes to folder names
    static std::string mapTopicToFolder(const std::string& topicCode) {
        static const std::unordered_map<std::string, std::string> topicFolderMap = {
            {"SE", "SoftwareEngineering"},
            {"DP", "DesignPatterns"},
            {"VC", "VersionControl"},
            {"OOD", "ObjectOrientedDesign"}
        };

        auto it = topicFolderMap.find(topicCode);
        if (it != topicFolderMap.end()) {
            return it->second;
        }
        throw std::invalid_argument("Invalid topic code");
    }

    // Select a random topic folder
    static std::string selectRandomTopic() {
        // Use override if set
        if (!testSelectedTopic.empty()) {
            return mapTopicToFolder(testSelectedTopic);
        }

        static const std::vector<std::string> topics = {
            "SoftwareEngineering",
            "DesignPatterns",
            "VersionControl",
            "ObjectOrientedDesign"
        };

        // Generate a random topic
        thread_local std::mt19937 gen(static_cast<unsigned long>(std::time(nullptr)));
        std::uniform_int_distribution<> dist(0, topics.size() - 1);
        return topics[dist(gen)];
    }

    // Select a random question file
    static std::string selectRandomQuestionFile() {
        // Use override if set
        if (!testSelectedFile.empty()) {
            return testSelectedFile;
        }

        static const std::vector<std::string> questionFiles = {
            "MultipleChoice.json", "TrueFalse.json", "FillInBlank.json", "Matching.json"
        };

        // Generate a random file
        thread_local std::mt19937 gen(static_cast<unsigned long>(std::time(nullptr)));
        std::uniform_int_distribution<> dist(0, questionFiles.size() - 1);
        return questionFiles[dist(gen)];
    }

    // Load questions from a file
    std::vector<Question> loadQuestions(const std::string& filePath) const {
        std::vector<Question> questions;
        std::ifstream file(filePath);

        // Check if the file can be opened
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        nlohmann::json jsonData;
        file >> jsonData;

        // Validate the JSON structure
        if (!jsonData.contains("questions")) {
            throw std::runtime_error("Invalid JSON format: Missing 'questions' field");
        }

        for (const auto& item : jsonData["questions"]) {
            Question question(filePath);

            // Parse the question text
            if (item.contains("question")) {
                question.setQuestionText(item["question"].get<std::string>());
            }

            // Parse Fill-in-the-Blank questions
            if (item.contains("word_bank")) {
                for (const auto& word : item["word_bank"]) {
                    question.addAnswer(word.get<std::string>());
                }
            } 
            // Parse True/False and Multiple Choice questions
            else if (item.contains("answers")) {
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
            } 
            // Parse Matching questions
            else if (item.contains("terms") && item.contains("definitions")) {
                for (const auto& term : item["terms"]) {
                    question.addAnswer(term.get<std::string>());
                }
                for (const auto& definition : item["definitions"]) {
                    question.addAnswer(definition.get<std::string>());
                }
            }

            // Parse the correct answer (if applicable)
            if (item.contains("correct_answer")) {
                question.setCorrectAnswer(item["correct_answer"].get<std::string>());
            }

            // Add the parsed question to the list
            questions.push_back(question);
        }

        return questions; // Return the list of questions
    }
};

// Initialize static variables
std::string RandomRequest::testSelectedFile = "";
std::string RandomRequest::testSelectedTopic = "";

#endif /* RandomRequest_hpp */
