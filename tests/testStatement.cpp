//
// Created by Jacob Roschen on 11/1/16.
//

#include "testStatement.h"

void statementTeardown() {
	LogHandler::errors.clear();
	LogHandler::warnings.clear();
	lex_close();
}

void runTest(const char *f) {
	// Initialize everything else
	lex_open((char *) f);

	Environment * e = NULL;
	Statement::compile(e);
}

void testStatementGoodHelper(TestCase *t, const char** files, int numTests) {
	for(int i = 0; i < numTests; i++) {
		runTest(files[i]);

		AssertEquals(t, "Error count in " << files[i], LogHandler::errors.size(), 0);
		AssertEquals(t, "Warning count in " << files[i], LogHandler::warnings.size(), 0);
	}
}

void testStatementIfGood(TestCase *t) {

	const char* files[] = {
			"tests/samples/declarations/if/good_1.k",
			"tests/samples/declarations/if/good_2.k",
			"tests/samples/declarations/if/good_3.k",
			"tests/samples/declarations/if/good_4.k"
	};

	testStatementGoodHelper(t, files, sizeof(files) / sizeof(const char *));
}

void testStatementIfBadMissingExpression(TestCase *t) {
	runTest("tests/samples/declarations/if/bad_1.k");

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);
}

void testStatementIfBadMissingEnd(TestCase *t) {
	runTest("tests/samples/declarations/if/bad_2.k");

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Line number", l.line, 4);
	AssertEquals(t, "Error message incorrect", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "End key should be missing", l.wanted, key_get(KEY_END));
}

void testStatementIfElseBadMissingEnd(TestCase *t) {
	runTest("tests/samples/declarations/if/bad_3.k");

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Line number", l.line, 7);
	AssertEquals(t, "Error message incorrect", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "End key should be missing", l.wanted, key_get(KEY_END));
}


void testStatementDoGood(TestCase *t) {
	const char* files[] = {
			"tests/samples/declarations/do/good_1.k"
	};

	testStatementGoodHelper(t, files, sizeof(files) / sizeof(const char *));
}

void testStatementDoBadMissingEnd(TestCase *t) {
	runTest("tests/samples/declarations/do/bad_1.k");

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Line number", l.line, 2);
	AssertEquals(t, "Error message incorrect", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "End key should be missing", l.wanted, key_get(KEY_END));
}


void testStatementWhileGood(TestCase *t) {
	const char* files[] = {
			"tests/samples/declarations/while/good_1.k",
			"tests/samples/declarations/while/good_2.k"
	};

	testStatementGoodHelper(t, files, sizeof(files) / sizeof(const char *));
}

void testStatementWhileBadMissingEnd(TestCase *t) {
	runTest("tests/samples/declarations/while/bad_1.k");

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Line number", l.line, 2);
	AssertEquals(t, "Error message incorrect", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "End key should be missing", l.wanted, key_get(KEY_END));
}


void testStatementUntilGood(TestCase *t) {
	const char* files[] = {
			"tests/samples/declarations/until/good_1.k"
	};

	testStatementGoodHelper(t, files, sizeof(files) / sizeof(const char *));
}

void testStatementUntilBadMissingUntil(TestCase *t) {
	runTest("tests/samples/declarations/until/bad_1.k");

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Line number", l.line, 2);
	AssertEquals(t, "Error message incorrect", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "End key should be missing", l.wanted, key_get(KEY_END));
}


void buildStatementTests(Tester *t) {
	TestGroup* tg = new TestGroup("Statements", NULL, statementTeardown);

	// If
	tg->AddTest(TestCase("Good if Statements", testStatementIfGood));
	// =BUG= The follow test case should fail. An empty expression currently compiles without error
	// tg->AddTest(TestCase("Bad if Statement Missing Expression", testStatementIfBadMissingExpression));
	tg->AddTest(TestCase("Bad if Statement Missing End", testStatementIfBadMissingEnd));
	tg->AddTest(TestCase("Bad if else Statement Missing End", testStatementIfElseBadMissingEnd));

	// Do
	tg->AddTest(TestCase("Good do Statements", testStatementDoGood));
	tg->AddTest(TestCase("Bad do Statement Missing End", testStatementDoBadMissingEnd));

	// While
	tg->AddTest(TestCase("Good while Statements", testStatementWhileGood));
	tg->AddTest(TestCase("Bad while Statement Missing End", testStatementWhileBadMissingEnd));

	// Until
	tg->AddTest(TestCase("Good until Statements", testStatementUntilGood));
	tg->AddTest(TestCase("Bad until Statement Missing Until Keyword", testStatementUntilBadMissingUntil));

	t->AddGroup(tg);
}