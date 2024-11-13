#include "src/service/SoftwareEngineering/json.hpp"

#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

class MultipleChoice {
    public:
     MultipleChoice() {
        readDataFile();

        QuestionText = jsonFileData["questions"][0]["question"];
        Answers.push_back(jsonFileData["questions"][0]["answers"]["a"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["b"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["c"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["d"]);
     }
      
      int readDataFile() {
        std::string filePath = "src/QuestionData/SoftwareEngineering/MultipleChoice.json";

        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            return 1;
        }

        inputFile >> jsonFileData;

        inputFile.close();
      }

      std::string getQuestionText() {
        return QuestionText;
     }

      std::string getCorrectAnswer() {
        return CorrectAnswer;
     }

     std::vector<std::string> getAnswers() {
      return Answers;
     }

     private:
      json jsonFileData;
      std::string QuestionText;
      std::string CorrectAnswer;
      std::vector<std::string> Answers;
};
