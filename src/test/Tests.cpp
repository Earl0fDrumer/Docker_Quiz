#include <iostream>

#include "selene/SeleneTest.hpp"
#include "src/test/SoftwareEngineering/MC_Test.hpp"
#include "src/test/VersionControl/VC_Test.hpp"

void runTests() { 
  OATPP_RUN_TEST(SeleneTest); 
  OATPP_RUN_TEST(MC_Test); 
  OATPP_RUN_TEST(VC_Test);
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
