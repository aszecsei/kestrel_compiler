/*
 * Tester
 *
 * By default, all tests are ran. Add flags to run specific tests. Ex. -lexer to run lexer tests
 * In order to add more tests, see the main method example for testLexer
 */

#include "tester.h"
#include "testLexer.h"
#include "testSymbolTable.h"
#include "testStringPool.h"
#include "testStatement.h"
#include "testExpression.h"
#include "testlinklst.h"
#include "testCodeGen.h"

using std::cout;

void TestGroup::AddTest(TestCase test) {
	test.testNumber = (int) tests.size() + 1;
	this->tests.push_back(test);
}

void TestGroup::RunTests() {
	Tester::Header(this->name, (int) this->tests.size());

	for (unsigned long i = 0; i < tests.size(); ++i) {
		this->RunTest(&tests.at(i));
	}

	cout << "\t--------------------------------" << std::endl;
	Tester::Summary(this->name, (int) this->tests.size(), this->failureCount, "\t");
}

void TestGroup::RunTest(TestCase *t) {
	try {
		if(this->setup != NULL) {
			this->setup();
		}
		t->callback(t);
		if(this->teardown != NULL) {
			this->teardown();
		}
	}
	catch (const std::runtime_error &re) {
		t->passed = false;
		t->reason = std::string("Runtime error: ") + re.what();
	}
	catch (const std::exception &ex) {
		t->passed = false;
		t->reason = std::string("Exception occurred: ") + ex.what();
	}
	catch (...) {
		t->passed = false;
		t->reason = std::string("Unknown error occurred.");
	}

	if (t->passed) {
		cout << ANSI_COLOR_GREEN;
		cout << "\t✔ " << t->testNumber << "/" << this->tests.size() << ": " << t->name;
	} else {
		cout << ANSI_COLOR_RED;
		cout << "\t✘ " << t->testNumber << "/" << this->tests.size() << ": " << t->name << ": " << t->reason;
		this->failureCount++;
	}

	cout << ANSI_COLOR_RESET << std::endl;
}


void Tester::RunTests() {
	Tester::Header(this->name, this->testCount);

	TEST_DIVIDER;

	for (unsigned long i = 0; i < this->groups.size(); ++i) {
		this->groups.at(i).RunTests();
		this->failureCount += this->groups.at(i).failureCount;
	}

	TEST_DIVIDER;

	Tester::Summary(this->name, this->testCount, this->failureCount, "");
}

void Tester::AddGroup(TestGroup *tg) {
	this->groups.push_back(*tg);
	this->testCount += tg->tests.size();
}

void Tester::Header(string name, int testCount) {
	cout << ANSI_BOLD << name << " (" << testCount << " tests)" << ANSI_BOLD_RESET << std::endl;
}

void Tester::Summary(string name, int testCount, int failureCount, string indentation) {
	if (failureCount > 0) {
		cout << ANSI_COLOR_RED << indentation << "Failed";
	} else {
		cout << ANSI_COLOR_GREEN << indentation << "Passed";
	}
	cout << " (" << ((double) (testCount - failureCount) / (double) testCount) * 100 << "%)";
	cout << ANSI_COLOR_RESET << ANSI_BOLD_RESET << std::endl;

	cout << indentation << "Total: " << testCount;
	cout << ", Passed: " << testCount - failureCount;
	cout << ", Failed: " << failureCount << std::endl << std::endl;
}


bool flagExists(const char *argv[], const char *flag) {
	int i = 0;
	while (argv[i] != NULL) {
		if (strstr(flag, argv[i]) != NULL) {
			return true;
		}
		i++;
	}

	return false;
}

int main(const int argc, const char *argv[]) {
	LogHandler::programName = "Tester";
	LogHandler::verbosity = Log::NONE;

	Tester t = Tester("Run All Tests");
	bool testAll = false;

	// If no options passed in, test everything
	if (argc <= 1) testAll = true;


	// Add handlers that add tests to run and specify a flag here
	if (testAll || flagExists(argv, "-lexer")) buildLexerTests(&t);
	if (testAll || flagExists(argv, "-symboltable")) buildSymbolTableTests(&t);
	if (testAll || flagExists(argv, "-stringpool")) buildStringPoolTests(&t);
	if (testAll || flagExists(argv, "-statements")) buildStatementTests(&t);
	if (testAll || flagExists(argv, "-expressions")) buildExpressionTests(&t);
	if (testAll || flagExists(argv, "-linklst")) buildLinklstTests(&t);
	if (testAll || flagExists(argv, "-codegen")) buildCodeGenTests(&t);


	t.RunTests();
}