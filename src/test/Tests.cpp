#include <iostream>

#include "selene/SeleneTest.hpp"

//Multiple Choice Tests
#include "src/test/MultipleChoiceTests/DP_Test.hpp"
#include "src/test/MultipleChoiceTests/OOD_Test.hpp"
#include "src/test/MultipleChoiceTests/SE_Test.hpp"
#include "src/test/MultipleChoiceTests/VC_Test.hpp"

//True or False Tests
#include "src/test/TrueOrFalseTests/DP_Test.hpp"
#include "src/test/TrueOrFalseTests/OOD_Test.hpp"
#include "src/test/TrueOrFalseTests/SE_Test.hpp"
#include "src/test/TrueOrFalseTests/VC_Test.hpp"

//Matching Tests
#include "src/test/MatchingTests/DP_Test.hpp"
#include "src/test/MatchingTests/OOD_Test.hpp"
#include "src/test/MatchingTests/SE_Test.hpp"
#include "src/test/MatchingTests/VC_Test.hpp"

//FIB Tests
#include "src/test/FillInBlankTests/DP_FIB_Test.hpp"
#include "src/test/FillInBlankTests/OOD_FIB_Test.hpp"
#include "src/test/FillInBlankTests/SE_FIB_Test.hpp"
#include "src/test/FillInBlankTests/VC_FIB_Test.hpp"

//List Topics Test
#include "src/test/ListTopicsTest/ListTopics_Test.hpp"

//Random Type and Random Type/Topic Tests
#include "src/test/RandomTests/RandomType_Test.hpp"
#include "src/test/RandomTests/RandomTypeTopic_Test.hpp"

//Error Handler Test
#include "src/test/ErrorHandlerTests/CustomErrorHandler_Test.hpp"

void runTests() {
  OATPP_RUN_TEST(SeleneTest);
  // Multiple Choice Tests
  OATPP_RUN_TEST(DP_MC_Test);
  OATPP_RUN_TEST(OOD_MC_Test);
  OATPP_RUN_TEST(SE_MC_Test);
  OATPP_RUN_TEST(VC_MC_Test);
  //TrueOrFalse Tests
  OATPP_RUN_TEST(DP_TF_Test);
  OATPP_RUN_TEST(OOD_TF_Test);
  OATPP_RUN_TEST(SE_TF_Test);
  OATPP_RUN_TEST(VC_TF_Test);
  //Matching Tests
  OATPP_RUN_TEST(DP_MAT_Test);
  OATPP_RUN_TEST(OOD_MAT_Test); 
  OATPP_RUN_TEST(SE_MAT_Test); 
  OATPP_RUN_TEST(VC_MAT_Test); 
  //FIB Tests
  OATPP_RUN_TEST(DP_FIB_Test);
  OATPP_RUN_TEST(OOD_FIB_Test);
  OATPP_RUN_TEST(SE_FIB_Test);
  OATPP_RUN_TEST(VC_FIB_Test);
  //List Topics Test
  OATPP_RUN_TEST(ListTopics_Test);
  //Random Type and Random Type/Topic Tests
  OATPP_RUN_TEST(RandomType_Test);
  OATPP_RUN_TEST(RandomTypeTopic_Test);
  // Error Handler Test
  OATPP_RUN_TEST(CustomErrorHandler_Test); // Add the Error Handler Test
}

int main() {
  oatpp::base::Environment::init();

  std::cout << "[INFO] Running all tests..." << std::endl;

  try {
    runTests();
  } catch (const std::exception& e) {
    std::cerr << "[ERROR] Exception while running tests: " 
      << e.what() << std::endl;
  }

  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::
    base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::
    Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);

  oatpp::base::Environment::destroy();

  return 0;
}
