
#include "testLexer.h"

class MockLexeme {
public:
	MockLexeme(lex_types type, const char* value, int line, int char_index) : type(type), value(value), line(line),
																				char_index(char_index) {}
	lex_types type;
	const char* value;
	int line;
	int char_index;
};

void lexerTeardown() {
    LogHandler::errors.clear();
    LogHandler::warnings.clear();
    lex_close();
}

void testLexerEmptyFile(TestCase *t) {
	char *f = (char *) "tests/samples/empty.k";
	lex_open(f);

	// EOF
	MockLexeme wanted = MockLexeme(ENDFILE, "EOF", 1, 1);
	AssertLexeme(t, "EOF", get_lex_this(), wanted);
}

void testLexerHelloWorld(TestCase *t) {
	char *f = (char *) "tests/samples/hello_world.k";

	lex_open(f);

	// First lexeme 'putchar'
	MockLexeme wanted = MockLexeme(IDENT, "putstring", 1, 1);
	AssertLexeme(t, "putchar", get_lex_this(), wanted);

	// (
	lex_advance();
	wanted = MockLexeme(PUNCT, "(", 1, 10);
	AssertLexeme(t, "Open Paren", get_lex_this(), wanted);

	// "Hello world"
	lex_advance();
	wanted = MockLexeme(STRING, "Hello world", 1, 12);
	AssertLexeme(t, "Hello world string", get_lex_this(), wanted);

	// LF
	lex_advance();
	wanted = MockLexeme(IDENT, "LF", 1, 26);
	AssertLexeme(t, "LF", get_lex_this(), wanted);

	// ,
	lex_advance();
	wanted = MockLexeme(PUNCT, ",", 1, 28);
	AssertLexeme(t, "Comma", get_lex_this(), wanted);

	// output
	lex_advance();
	wanted = MockLexeme(IDENT, "output", 1, 30);
	AssertLexeme(t, "Output", get_lex_this(), wanted);

	// )
	lex_advance();
	wanted = MockLexeme(PUNCT, ")", 1, 37);
	AssertLexeme(t, "End Paren", get_lex_this(), wanted);

	// ;
	lex_advance();
	wanted = MockLexeme(PUNCT, ";", 1, 38);
	AssertLexeme(t, "Semicolon", get_lex_this(), wanted);

	// EOF
	lex_advance();
	wanted = MockLexeme(ENDFILE, "EOF", 1, 39);
	AssertLexeme(t, "EOF", get_lex_this(), wanted);
}

void testLexerForLoop(TestCase *t) {
	char *f = (char *) "tests/samples/for_loop.k";
	lex_open(f);

	// for
	MockLexeme wanted = MockLexeme(KEYWORD, "for", 1, 1);
	AssertLexeme(t, "for keyword", get_lex_this(), wanted);

	// i
	lex_advance();
	wanted = MockLexeme(IDENT, "i", 1, 5);
	AssertLexeme(t, "i variable", get_lex_this(), wanted);

	// in
	lex_advance();
	wanted = MockLexeme(KEYWORD, "in", 1, 7);
	AssertLexeme(t, "in keyword", get_lex_this(), wanted);

	// s.min
	lex_advance();
	wanted = MockLexeme(IDENT, "s", 1, 10);
	AssertLexeme(t, "s variable", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(PUNCT, ".", 1, 11);
	AssertLexeme(t, "property accessor (dot)", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(IDENT, "min", 1, 12);
	AssertLexeme(t, "property value identifier (min)", get_lex_this(), wanted);

	// ..
	lex_advance();
	wanted = MockLexeme(PUNCT, "..", 1, 16);
	AssertLexeme(t, "range (..)", get_lex_this(), wanted);

	// s.max
	lex_advance();
	wanted = MockLexeme(IDENT, "s", 1, 19);
	AssertLexeme(t, "s variable", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(PUNCT, ".", 1, 20);
	AssertLexeme(t, "property accessor (dot)", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(IDENT, "max", 1, 21);
	AssertLexeme(t, "property value identifier (max)", get_lex_this(), wanted);

	// putchar
	lex_advance();
	wanted = MockLexeme(IDENT, "putchar", 2, 5);
	AssertLexeme(t, "putchar identifier", get_lex_this(), wanted);

	// (
	lex_advance();
	wanted = MockLexeme(PUNCT, "(", 2, 12);
	AssertLexeme(t, "Start putchar paren", get_lex_this(), wanted);

	// s(i)
	lex_advance();
	wanted = MockLexeme(IDENT, "s", 2, 14);
	AssertLexeme(t, "s variable", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(PUNCT, "(", 2, 15);
	AssertLexeme(t, "Open array accessor paren", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(IDENT, "i", 2, 16);
	AssertLexeme(t, "Array index i", get_lex_this(), wanted);

	lex_advance();
	wanted = MockLexeme(PUNCT, ")", 2, 17);
	AssertLexeme(t, "Close array accessor paren", get_lex_this(), wanted);

	// ,
	lex_advance();
	wanted = MockLexeme(PUNCT, ",", 2, 18);
	AssertLexeme(t, "Parameter comma separator", get_lex_this(), wanted);

	// output
	lex_advance();
	wanted = MockLexeme(IDENT, "output", 2, 20);
	AssertLexeme(t, "Output file", get_lex_this(), wanted);

	// )
	lex_advance();
	wanted = MockLexeme(PUNCT, ")", 2, 27);
	AssertLexeme(t, "End putchar paren", get_lex_this(), wanted);

	// end
	lex_advance();
	wanted = MockLexeme(KEYWORD, "end", 3, 1);
	AssertLexeme(t, "End loop keyword", get_lex_this(), wanted);

	// EOF
	lex_advance();
	wanted = MockLexeme(ENDFILE, "EOF", 3, 4);
	AssertLexeme(t, "EOF", get_lex_this(), wanted);
}

void buildLexerTests(Tester *t) {
	TestGroup* tg = new TestGroup("Lexer", NULL, lexerTeardown);

	tg->AddTest(TestCase("Empty File", testLexerEmptyFile));
	tg->AddTest(TestCase("Hello World File", testLexerHelloWorld));
	tg->AddTest(TestCase("For Loop File", testLexerForLoop));

	t->AddGroup(tg);
}