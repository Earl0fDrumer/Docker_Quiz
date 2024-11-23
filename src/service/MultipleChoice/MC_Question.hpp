#ifndef QUESTION_HPP
#define QUESTION_HPP

#include "src/service/Question.hpp"

class MultipleChoice : public Question {
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
};

#endif // QUESTION_HPP