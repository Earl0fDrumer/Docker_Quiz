#ifndef QUESTION_HPP
#define QUESTION_HPP

#include "src/service/json.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

class Question {
public:
    /**
     * Constructor to initialize the question with the file path
     * @param path - Path to the JSON file containing the question data
     */
    Question(const std::string& path) : filePath(path) {
        QuestionText = "";
        CorrectAnswer = "";
    }

    /**
     * Reads and parses the data from the JSON file
     */
    void readDataFile() {
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            throw std::runtime_error("Error: Failed to open file: " + filePath);
        }

        try {
            inputFile >> jsonFileData;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()));
        }
        
        inputFile.close();
    }

    // Getters
    std::string getQuestionText() const {
        return QuestionText;
    }

    std::string getCorrectAnswer() const {
        return CorrectAnswer;
    }

    std::vector<std::string> getAnswers() const {
        return Answers;
    }

    // Setters
    void setQuestionText(const std::string& text) {
        QuestionText = text;
    }

    void setCorrectAnswer(const std::string& answer) {
        CorrectAnswer = answer;
    }

    void addAnswer(const std::string& answer) {
        Answers.push_back(answer);
    }

    virtual ~Question() = default;

protected:
    std::string filePath;
    nlohmann::json jsonFileData;
    std::string QuestionText;
    std::string CorrectAnswer;
    std::vector<std::string> Answers;
};

#endif /* QUESTION_HPP */