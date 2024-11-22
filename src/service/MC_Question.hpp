#include "src/service/json.hpp"
#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

class MultipleChoice2 {
    public:  
      MultipleChoice2(std::string path) {
        filePath = path;
        readDataFile();

        QuestionText = jsonFileData["questions"][0]["question"];
        Answers.push_back(jsonFileData["questions"][0]["answers"]["a"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["b"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["c"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["d"]);
     }
    
      void readDataFile() {
        //std::string filePath = "src/QuestionData/SoftwareEngineering/MultipleChoice.json";

        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            throw std::ios_base::failure("Error: Failed to open file: " + filePath);
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
      std::string filePath;
      json jsonFileData;
      std::string QuestionText;
      std::string CorrectAnswer;
      std::vector<std::string> Answers;
};

