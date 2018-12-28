
#include "testSymbolTable.h"

struct case_t{
	const char *string;
	symbol_handle symb;
};

struct case_t cases[] = {
		  {"while", STRING_NULL}
		, {"do", STRING_NULL}
		, {"blah...", STRING_NULL}
		, {"kestrel", STRING_NULL}
		, {"how", STRING_NULL}
		, {"For", STRING_NULL}
		, {"throw", STRING_NULL}
		, {"const", STRING_NULL}
		, {"final", STRING_NULL}
		, {"type", STRING_NULL}
		, {"procedure", STRING_NULL}
		, {"extension", STRING_NULL}
		, {"UPPERCASE", STRING_NULL}
		, {"IDENTIFIER", STRING_NULL}
		, {"do", STRING_NULL}
		, {"blah...", STRING_NULL}
		, {"kestrel", STRING_NULL}
		, {"how", STRING_NULL}
		, {"For", STRING_NULL}
		, {"throw", STRING_NULL}
		, {"const", STRING_NULL}
		, {"final", STRING_NULL}
		, {"type", STRING_NULL}
		, {"procedure", STRING_NULL}
		, {"extension", STRING_NULL}
		, {"UPPERCASE", STRING_NULL}
		, {"IDENTIFIER", STRING_NULL}
		, {"do", STRING_NULL}
		, {"blah...", STRING_NULL}
		, {"kestrel", STRING_NULL}
		, {"how", STRING_NULL}
		, {"For", STRING_NULL}
		, {"throw", STRING_NULL}
		, {"const", STRING_NULL}
		, {"final", STRING_NULL}
		, {"type", STRING_NULL}
		, {"procedure", STRING_NULL}
		, {"extension", STRING_NULL}
		, {"UPPERCASE", STRING_NULL}
		, {"IDENTIFIER", STRING_NULL}
}; //a bag(multiset) of cases, the case need to verify the proposition: string1 == string2 => symbol1 == sumbol2

void testSymbolTableOnSymbolAdd(TestCase *t) {
	int num = sizeof(cases) / sizeof(struct case_t);
	symbol_init();
	int i = 0;
	for (; i < num; i ++) {
		cases[i].symb = symbol_add(cases[i].string);
	}

	for (i = 0; i < num; i ++) {
		symbol_handle h = cases[i].symb;
		const char *s = cases[i].string;
		for (int j = 0; j < num; j ++) {
			if (i != j)
			{
				symbol_handle h_prime = cases[j].symb;
				const char *s_prime = cases[j].string;
				bool pass = (0 != strcmp(s, s_prime)
						||	h == h_prime);

				std::ostringstream oss;
				oss << "Case " << 1;
				Assert(t, pass, oss.str());
				//proposition: s == s' => h == h'
			}
		}
	}

	symbol_uninit();
}

void testSymbolTableOnSymbolAppend(TestCase *t) {
	int num = sizeof(cases) / sizeof(struct case_t);

	symbol_init();
	int i = 0;
	for (; i < num; i ++) {
		const char* s = cases[i].string;
		symbol_start(0,0);
		const char* c = s;
		for(; *c != '\0'; c ++)
			symbol_append(*c);
		cases[i].symb = symbol_lookup();
	}

	for (i = 0; i < num; i ++) {
		symbol_handle h = cases[i].symb;
		const char *s = cases[i].string;
		for (int j = 0; j < num; j ++) {
			if (i != j)
			{
				symbol_handle h_prime = cases[j].symb;
				const char *s_prime = cases[j].string;
				bool pass = (0 != strcmp(s, s_prime)
						||	h == h_prime);

				std::ostringstream oss;
				oss << "Case " << 1;
				Assert(t, pass, oss.str());
				//proposition: s == s' => h == h'
			}
		}
	}

	symbol_uninit();
}

void testSymbolTableOnWorkingSenario(TestCase *t) {
	int num = sizeof(cases) / sizeof(struct case_t);

	symbol_init();
	struct case_t* casesAdd = cases;
	int i = 0;
	for (; i < num; i ++) {
		casesAdd[i].symb = symbol_add(casesAdd[i].string);
	}

	struct case_t* casesAppend = (struct case_t* )malloc(num * sizeof(struct case_t));
	memcpy(casesAppend, casesAdd, num*sizeof(struct case_t));
	for (i = 0; i < num; i ++) {
		const char* s = casesAppend[i].string;
		symbol_start(0,0);
		const char* c = s;
		for(; *c != '\0'; c ++)
			symbol_append(*c);
		casesAppend[i].symb = symbol_lookup();
	}

	struct case_t* casesOverall[num * 2];

	for(i = 0; i < num; i ++)
		casesOverall[i] = &casesAdd[i];
	int b = i;
	for( ; i < 2*num; i ++)
		casesOverall[i] = &casesAppend[i - b];

	for (i = 0; i < 2*num; i ++) {
		symbol_handle h = casesOverall[i]->symb;
		const char* s = casesOverall[i]->string;
		for (int j = 0; j < 2*num; j ++) {
			if (i != j)
			{
				symbol_handle h_prime = casesOverall[j]->symb;
				const char* s_prime = casesOverall[j]->string;
				bool pass = (0 != strcmp(s, s_prime)
						||	h == h_prime);

				std::ostringstream oss;
				oss << "Case " << 1 << ":" << j;
				Assert(t, pass, oss.str());
			}
		}

	}

	symbol_uninit();
}

void buildSymbolTableTests(Tester *t) {
	TestGroup* tg = new TestGroup("Symbol Table");

	tg->AddTest(TestCase("On Symbol Add", testSymbolTableOnSymbolAdd));
	tg->AddTest(TestCase("On Symbol Append", testSymbolTableOnSymbolAppend));
	tg->AddTest(TestCase("On Working Scenario", testSymbolTableOnWorkingSenario));

	t->AddGroup(tg);
}