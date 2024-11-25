#ifndef TOPICS_hpp
#define TOPICS_hpp

#include "src/service/json.hpp"
#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

class Topics {
 public:  
  Topics() {

    filePath = "src/QuestionData/TopicNames.json";
    readDataFile();

    TopicsList.push_back(jsonFileData["Topics"]["1"]);
    TopicsList.push_back(jsonFileData["Topics"]["2"]);
    TopicsList.push_back(jsonFileData["Topics"]["3"]);
    TopicsList.push_back(jsonFileData["Topics"]["4"]);
  }

  void readDataFile() {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
      throw std::ios_base::failure("Error: Failed to open file: " + filePath);
    }

    inputFile >> jsonFileData;
    inputFile.close();
  }

  std::vector<std::string> getTopicsList() {
    return TopicsList;
  }

 protected:
  std::string filePath;
  json jsonFileData;
  std::vector<std::string> TopicsList;
};

#endif /* TOPICS_hpp */