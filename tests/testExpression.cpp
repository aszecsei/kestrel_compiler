//
// Created by Jacob Roschen on 11/1/16.
//

#include "testExpression.h"

void expressionTeardown() {
	LogHandler::errors.clear();
	LogHandler::warnings.clear();
	lex_close();
}

// Comparing
void testExpressionComparingEqual(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/equal.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_EQ);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionComparingNotEqual(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/not_equal.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_NOTEQ);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionComparingGreaterThan(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/greater_than.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_GT);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionComparingGreaterThanEqual(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/greater_than_equal.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_GTE);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionComparingLessThan(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/less_than.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_LT);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionComparingLessThanEqual(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/less_than_equal.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_LTE);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionComparingIn(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/comparing/in.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_IN);
	AssertEquals(t, "Correct LHS Value", ((Value *)ex->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)ex->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)ex->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)ex->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}

// Parens
void testExpressionSingleParen(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/parens/single.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_NULL);
	AssertEquals(t, "Correct Expression Type", ((Value *)ex->attr->attr->attr->attr)->valueType, VAL_EXP);

	Expression *insideExpression = (Expression *)ex->attr->attr->attr->attr->attr;

	AssertEquals(t, "Correct Compare Type", insideExpression->compareType, COMP_EQ);
	AssertEquals(t, "Correct LHS Value", ((Value *)insideExpression->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)insideExpression->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)insideExpression->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)insideExpression->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionDoubleParen(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/parens/double.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Correct Compare Type", ex->compareType, COMP_NULL);
	AssertEquals(t, "Correct Expression Type", ((Value *)ex->attr->attr->attr->attr)->valueType, VAL_EXP);

	Expression *insideExpression = (Expression *)ex->attr->attr->attr->attr->attr;
	Expression *inside2Expression = (Expression *)insideExpression->attr->attr->attr->attr->attr;

	AssertEquals(t, "Correct Compare Type", inside2Expression->compareType, COMP_EQ);
	AssertEquals(t, "Correct LHS Value", ((Value *)inside2Expression->attr->attr->attr->attr)->val, 5);
	AssertEquals(t, "Correct LHS Type", ((Value *)inside2Expression->attr->attr->attr->attr)->type, VAL_NUMBER);
	AssertEquals(t, "Correct RHS Value", ((Value *)inside2Expression->secondComparand->attr->attr->attr)->val, 3);
	AssertEquals(t, "Correct RHS Type", ((Value *)inside2Expression->secondComparand->attr->attr->attr)->type, VAL_NUMBER);
}
void testExpressionSingleParenMissing(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/parens/single_missing.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	// Verify that the correct error was generated
	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Correct error type", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "Correct line number", l.line, 1);
	AssertEquals(t, "Correct got value", l.got, "EOF");
	AssertEquals(t, "Correct wanted value", l.wanted, ")");
}
void testExpressionSingleParenMissingBracket(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/parens/single_missing_bracket.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	// Verify that the correct error was generated
	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Correct error type", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "Correct line number", l.line, 1);
	AssertEquals(t, "Correct got value", l.got, "EOF");
	AssertEquals(t, "Correct wanted value", l.wanted, "]");
}
void testExpressionSingleParenMissingBrace(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/parens/single_missing_brace.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 1);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	// Verify that the correct error was generated
	Log l = LogHandler::errors.at(0);
	AssertEquals(t, "Correct error type", l.error, ER_FOUND_BUT_WANT);
	AssertEquals(t, "Correct line number", l.line, 1);
	AssertEquals(t, "Correct got value", l.got, "EOF");
	AssertEquals(t, "Correct wanted value", l.wanted, "}");
}


//Operators
void testExpressionOperatorsAddition(TestCase *t){
	lex_open((char *) "tests/samples/expressions/Operators/addition.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Add type is Plus", ((Comparand *)(ex->attr))->addType,ADD_PLUS);

}
void testExpressionOperatorsSubtraction(TestCase *t){
	lex_open((char *) "tests/samples/expressions/Operators/subtraction.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Add type is Plus", ((Comparand *)(ex->attr))->addType,ADD_MINUS);

}
void testExpressionOperatorsOr(TestCase *t){
	lex_open((char *) "tests/samples/expressions/Operators/or.k");

	Environment * e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Add type is Plus", ((Comparand *)(ex->attr))->addType,ADD_OR);

}
void testExpressionOperatorsMultiply(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/Operators/multiplication.k");

	Environment *e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Mult type is Mult", ((Term *) (ex->attr->attr))->multType, MULT_TIMES);

}
void testExpressionOperatorsDivide(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/Operators/division.k");

	Environment *e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Mult type is Div", ((Term *) (ex->attr->attr))->multType, MULT_DIV);

}
void testExpressionOperatorsModulo(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/Operators/modulous.k");

	Environment *e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Mult type is Mod", ((Term *) (ex->attr->attr))->multType, MULT_MOD);

}
void testExpressionOperatorsAnd(TestCase *t) {
	lex_open((char *) "tests/samples/expressions/Operators/and.k");

	Environment *e = NULL;
	Expression *ex = Expression::compile(e);

	AssertEquals(t, "Error count", LogHandler::errors.size(), 0);
	AssertEquals(t, "Warning count", LogHandler::warnings.size(), 0);

	AssertEquals(t, "Mult type is And", ((Term *) (ex->attr->attr))->multType, MULT_AND);

}

void buildExpressionTests(Tester *t) {
	TestGroup *tg = new TestGroup("Expressions", NULL, expressionTeardown);

	// Comparing
	tg->AddTest(TestCase("Comparing Equal", testExpressionComparingEqual));
	tg->AddTest(TestCase("Comparing Not Equal", testExpressionComparingNotEqual));
	tg->AddTest(TestCase("Comparing Greater Than", testExpressionComparingGreaterThan));
	tg->AddTest(TestCase("Comparing Greater Than Equal", testExpressionComparingGreaterThanEqual));
	tg->AddTest(TestCase("Comparing Less Than", testExpressionComparingLessThan));
	tg->AddTest(TestCase("Comparing Less Than Equal", testExpressionComparingLessThanEqual));
	tg->AddTest(TestCase("Comparing In", testExpressionComparingIn));

	// Parens
	tg->AddTest(TestCase("Single Paren", testExpressionSingleParen));
	tg->AddTest(TestCase("Double Paren", testExpressionDoubleParen));
	tg->AddTest(TestCase("Single Paren Missing )", testExpressionSingleParenMissing));
	tg->AddTest(TestCase("Single Paren Missing ]", testExpressionSingleParenMissingBracket));
	tg->AddTest(TestCase("Single Paren Missing }", testExpressionSingleParenMissingBrace));

	//Operators
	tg->AddTest(TestCase("Addition Symbol", testExpressionOperatorsAddition));
	tg->AddTest(TestCase("Subtraction Symbol", testExpressionOperatorsSubtraction));
	tg->AddTest(TestCase("Or Symbol", testExpressionOperatorsOr));
	tg->AddTest(TestCase("Multiply Symbol", testExpressionOperatorsMultiply));
	tg->AddTest(TestCase("Divide Symbol", testExpressionOperatorsDivide));
	tg->AddTest(TestCase("Modulo Symbol", testExpressionOperatorsModulo));
	tg->AddTest(TestCase("And Symbol", testExpressionOperatorsAnd));

	t->AddGroup(tg);
}