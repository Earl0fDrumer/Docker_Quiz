#include <iostream>

#include "selene/SeleneTest.hpp"
#include "src/test/MultipleChoiceTests/DP_Test.cpp"
#include "src/test/MultipleChoiceTests/DP_Test.hpp"
#include "src/test/MultipleChoiceTests/OOD_Test.cpp"
#include "src/test/MultipleChoiceTests/OOD_Test.hpp"
#include "src/test/MultipleChoiceTests/SE_Test.cpp"
#include "src/test/MultipleChoiceTests/SE_Test.hpp"
#include "src/test/MultipleChoiceTests/VC_Test.cpp"
#include "src/test/MultipleChoiceTests/VC_Test.hpp"
#include "src/test/FillInBlankTests/DP_FIB_Test.cpp"
#include "src/test/FillInBlankTests/DP_FIB_Test.hpp"
#include "src/test/FillInBlankTests/OOD_FIB_Test.cpp"
#include "src/test/FillInBlankTests/OOD_FIB_Test.hpp"
#include "src/test/FillInBlankTests/SE_FIB_Test.cpp"
#include "src/test/FillInBlankTests/SE_FIB_Test.hpp"
#include "src/test/FillInBlankTests/VC_FIB_Test.cpp"
#include "src/test/FillInBlankTests/VC_FIB_Test.hpp"

void runTests() { 
  OATPP_RUN_TEST(SeleneTest); 
  OATPP_RUN_TEST(DP_MC_Test); 
  OATPP_RUN_TEST(OOD_MC_Test); 
  OATPP_RUN_TEST(SE_MC_Test);
  OATPP_RUN_TEST(VC_MC_Test);
  OATPP_RUN_TEST(DP_FIB_TEST);
  OATPP_RUN_TEST(OOD_FIB_TEST);
  OATPP_RUN_TEST(SE_FIB_TEST);
  OATPP_RUN_TEST(VC_FIB_TEST);
}

int main() {
  oatpp::base::Environment::init();

  std::cout << "[INFO] Running all tests..." << std::endl;

  try {
    runTests();
  } catch (const std::exception& e) {
    std::cerr << "[ERROR] Exception while running tests: " << e.what() << std::endl;
  }

  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);

  oatpp::base::Environment::destroy();

  return 0;
}
