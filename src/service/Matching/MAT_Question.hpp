#ifndef MAT_QUESTION_hpp
#define MAT_QUESTION_hpp

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>

#include "src/service/json.hpp"
#include "src/service/Question.hpp"

using json = nlohmann::json;

class Matching : public Question {
 public:
  Matching(std::string path) : Question(path) {
    filePath = path;
    readDataFile();

    std::random_device rd;
    std::mt19937 g(rd());
    QuestionText = jsonFileData["questions"][0]["question"];
    Answers.push_back(jsonFileData["questions"][0]["terms"]["a"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["b"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["c"]);
    Answers.push_back(jsonFileData["questions"][0]["terms"]["d"]);

    std::shuffle(Answers.begin(), Answers.end(), g);

    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["a"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["b"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["c"]);
    Definitions.push_back(jsonFileData["questions"][0]["definitions"]["d"]);

    std::shuffle(Definitions.begin(), Definitions.end(), g);
  }

  std::vector<std::string> getDefinitions() {
    return Definitions;
  }

 private:
  std::vector<std::string> Definitions;
};

#endif /* MAT_QUESTION_hpp */
