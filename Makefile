CXX=g++
CXXFLAGS= -std=c++17 -g -fprofile-arcs -ftest-coverage

OATPP_INCLUDE_LIB = /usr/local/include/oatpp-1.3.0/oatpp
OATPP_INCLUDE = -I src -I $(OATPP_INCLUDE_LIB) -I .

LINKFLAGS_LOCAL = -L /usr/local/lib/oatpp-1.3.0
LINKFLAGS_APP = -loatpp
LINKFLAGS_TEST = $(LINKFLAGS_APP) -loatpp-test

SRC_DIR = src
SRC_DIR_SERVER = src/server
SRC_DIR_DTO = src/dto
SRC_DIR_CONTROLLER = src/controller
SRC_DIR_SERVICE_MC_QUESTION = src/service/MultipleChoice
SRC_DIR_SERVICE_TF_QUESTION = src/service/TrueOrFalse
SRC_DIR_SERVICE_MAT_QUESTION = src/service/Matching
SRC_DIR_SERVICE_FIB_QUESTION = src/service/FillInBlank
SRC_DIR_SERVICE_RANDOM_BY_TYPE = src/service

SRC_DIR_TESTS = src/test
SRC_DIR_TESTS_Selene = src/test/selene
SRC_DIR_TESTS_MultipleChoice = src/test/MultipleChoiceTests
SRC_DIR_TESTS_TrueOrFalse = src/test/TrueOrFalseTests
SRC_DIR_TESTS_Matching = src/test/MatchingTests
SRC_DIR_TESTS_FIB = src/test/FillInBlankTests
SRC_DIR_TESTS_TOPICS = src/test/ListTopicsTest
SRC_DIR_TESTS_RAND = src/test/RandomTests

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
	$(TEST_SERVER) \
	$(COVERAGE_DIR) \
	doxygen/html \
	obj bin \

$(PROGRAM_SERVER): $(SRC_DIR_SERVER)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(OATPP_INCLUDE) \
	$(SRC_DIR_SERVER)/*.cpp \
	$(SRC_DIR_DTO)/*.hpp \
	$(SRC_DIR_SERVICE_MC_QUESTION)/*.hpp \
	$(SRC_DIR_SERVICE_TF_QUESTION)/*.hpp \
	$(SRC_DIR_SERVICE_MAT_QUESTION)/*.hpp \
	$(SRC_DIR_SERVICE_FIB_QUESTION)/*.hpp \
	$(SRC_DIR_SERVICE_RANDOM_BY_TYPE)/*.hpp \
	$(SRC_DIR_CONTROLLER)/*.hpp \
	$(LINKFLAGS_APP) $(LINKFLAGS_LOCAL)

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
	$(SRC_DIR_TESTS_TrueOrFalse)/*.cpp \
	$(SRC_DIR_TESTS_Matching)/*.cpp \
	$(SRC_DIR_TESTS_FIB)/*.cpp \
	$(SRC_DIR_TESTS_TOPICS)/*.cpp \
	$(SRC_DIR_TESTS_RAND)/*.cpp \
	$(SRC_DIR_TESTS)/*.cpp $(LINKFLAGS_TEST) $(LINKFLAGS_LOCAL)

static: ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE_MC_QUESTION} ${SRC_DIR_SERVICE_DP_QUESTION} ${TEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE_MC_QUESTION} ${SRC_DIR_SERVICE_DP_QUESTION} ${TEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

style: ${SRC_DIR_SERVICE_MC_QUESTION} ${SRC_DIR_SERVICE_DP_QUESTION} ${SRC_INCLUDE}
	${STYLE_CHECK} src/controller/* src/dto/* src/server/* src/service/*/* src/test/*/* src/test/*.cpp
	
# To perform the code coverage checks
.PHONY: coverage
coverage: ${TEST_SERVER}
	./${TEST_SERVER}
	# Determine code coverage
	${LCOV} --capture --gcov-tool ${GCOV} --directory . --output-file \
	${COVERAGE_RESULTS} --rc lcov_branch_coverage=1
	# Only show code coverage for the source code files (not library files)
	${LCOV} --extract ${COVERAGE_RESULTS} */*/*/${SRC_DIR}/* -o ${COVERAGE_RESULTS}
	#Generate the HTML reports
	genhtml ${COVERAGE_RESULTS} --output-directory ${COVERAGE_DIR}
	#Remove all of the generated files from gcov
	make clean-temp
