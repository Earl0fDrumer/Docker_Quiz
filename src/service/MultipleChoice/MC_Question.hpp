#include "src/service/json.hpp"
#include "src/service/Question.hpp"
#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

class MultipleChoice : public Question {
    public:  
      MultipleChoice(std::string path) : Question(path) {
        filePath = path;
        readDataFile();

        QuestionText = jsonFileData["questions"][0]["question"];
        Answers.push_back(jsonFileData["questions"][0]["answers"]["a"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["b"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["c"]);
        Answers.push_back(jsonFileData["questions"][0]["answers"]["d"]);
     }
};

