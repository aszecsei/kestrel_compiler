
#ifndef TESTER_H
#define TESTER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include <sstream>

using std::vector;
using std::string;

class TestCase {
public:
	TestCase(string name, void(*c)(TestCase *t)) : name(name), passed(true), callback(c) {};
	void (*callback)(TestCase *t);
	string name;
	string reason;
	bool passed;
	int testNumber;
};

class TestGroup {
public:
	TestGroup(const string &name, void(*s)() = NULL, void(*t)() = NULL) : name(name), failureCount(0),
																		  setup(s),
																		  teardown(t) {};
	void AddTest(TestCase test);
	void RunTests();
	void RunTest(TestCase *t);
	int failureCount;
	vector<TestCase> tests;
	void (*setup)();
	void (*teardown)();
private:
	string name;
};

class Tester {
public:
	Tester(const string &name) : name(name), failureCount(0), testCount(0) {};
	static void Summary(string name, int testCount, int failureCount, string indentation);
	static void Header(string name, int testCount);
	void RunTests();
	void AddGroup(TestGroup *tg);
	int failureCount;
	int testCount;
private:
	vector<TestGroup> groups;
	string name;
};

#define Assert(t, test, message)    	\
    if (!(test)) {                		\
        t->passed = false;            	\
        t->reason = message;        	\
        return;                    		\
    }

#define AssertEquals(t, name, got, wanted)            	\
    if (got != wanted) {                            	\
        t->passed = false;                            	\
        std::ostringstream final_message;            	\
        final_message << name << ": Expected " << wanted << ", but found " << got << ". ";        \
        final_message << got << " != " << wanted;    	\
        t->reason = final_message.str();            	\
        return;                                    		\
    }

#define TEST_DIVIDER                                    \
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";    	\
    cout << std::endl << std::endl;

#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#define ANSI_BOLD            "\033[1m"
#define ANSI_BOLD_RESET        "\033[0m"

#endif // TESTER_H
