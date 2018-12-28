
#ifndef TESTDECLARATION_H
#define TESTDECLARATION_H

#include "../lexical.h"
#include "tester.h"

void buildLexerTests(Tester *t);

#define AssertLexeme(t, name, got, wanted)																	\
	Assert(t, got.type == wanted.type, name + std::string(" lexeme type is incorrect"));					\
	Assert(t, strcmp(lex_get(got), wanted.value) == 0, name + std::string(" lexeme value is incorrect"));	\
	Assert(t, got.line == wanted.line, name + std::string(" line number is incorrect"));					\
	Assert(t, got.char_index == wanted.char_index, name + std::string(" character index is incorrect"))

#endif // TESTDECLARATION_H
