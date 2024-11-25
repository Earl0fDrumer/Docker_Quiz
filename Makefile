CXX=g++
CXXFLAGS= -std=c++17 -g -fprofile-arcs -ftest-coverage

LINKFLAGS_APP = -loatpp
LINKFLAGS_TEST = $(LINKFLAGS_APP) -loatpp-test

SRC_DIR_SERVER = src/server
SRC_DIR_DTO = src/dto
SRC_DIR_CONTROLLER = src/controller
SRC_DIR_SERVICE_MC_QUESTION = src/service/MultipleChoice
SRC_DIR_SERVICE_FIB_QUESTION = src/service/FillInBlank
SRC_DIR_TESTS = src/test
SRC_DIR_TESTS_Selene = src/test/selene
SRC_DIR_TESTS_MultipleChoice = src/test/MultipleChoiceTests
SRC_DIR_TESTS_FIB = src/test/FillInBlankTests

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint

PROGRAM_SERVER = seleneServer
TEST_SERVER = testServer

.PHONY: all
all: $(PROGRAM_SERVER) coverage docs static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_SERVER) \
	$(COVERAGE_DIR) \
	doxygen/html \
	obj bin \

$(PROGRAM_SERVER): $(SRC_DIR_SERVER)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(OATPP_INCLUDE) \
	$(SRC_DIR_SERVER)/*.cpp \
	$(SRC_DIR_DTO)/*.hpp \
	$(SRC_DIR_SERVICE_MC_QUESTION)/*.hpp \
	$(SRC_DIR_SERVICE_FIB_QUESTION)/*.hpp \
	$(SRC_DIR_CONTROLLER)/*.hpp \
 $(LINKFLAGS_APP)

docker:
	docker build --pull --rm -f "Dockerfile" -t selene:latest "."

start:
	docker compose -f "compose.yml" up -d --build

stop:
	docker compose -f "compose.yml" down

$(TEST_SERVER): $(SRC_DIR_TESTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_SERVER) $(OATPP_INCLUDE) \
	$(SRC_DIR_TESTS_Selene)/*.cpp \
	$(SRC_DIR_TESTS_MultipleChoice)/*.cpp \
	$(SRC_DIR_TESTS_FIB)/*.cpp \
	$(SRC_DIR_TESTS)/*.cpp $(LINKFLAGS_TEST)

static: ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE_MC_QUESTION} ${SRC_DIR_SERVICE_DP_QUESTION} ${TEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE_MC_QUESTION} ${SRC_DIR_SERVICE_DP_QUESTION} ${TEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

style: ${SRC_DIR_SERVICE_MC_QUESTION} ${SRC_DIR_SERVICE_DP_QUESTION} ${SRC_INCLUDE}
	${STYLE_CHECK} src/controller/* src/dto/* src/server/* src/service/*/* src/test/*/* src/test/*.cpp
