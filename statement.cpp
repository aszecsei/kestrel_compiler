// statement.cpp -- implementation of parser/compiler for statements

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established

// BNF
// <statement> ::= <do end>
//				|  <if>
//				|  <case>
//				|  <loop>
//				|  <exception handler>
//				|  <raise>
//				|  <procedure call>
//				|  <assignment>
//
// <do end> ::= "do"
// 					<block>
// 				"end"
//
// <if> ::= "if" <expression> [ "then" ]
// 				<block>
// 		  [ "else"
// 				<block> ]
// 		    "end"
//
// <case> ::= "select" <expression> [ "in" ]
// 		  { "case" <case label> { [ "," ] <case label> } ":"
// 				<block> }
// 		  [ "else"
// 				<block> ]
// 			"end"
//
// <case label> ::= <expression> [ ".." <expression> ]
//
// <loop> ::= <while loop>
//		   |  <until loop>
//		   |  <for loop>
//
// <while loop> ::= "while" <expression> [ "do" ]
// 						<block>
// 					"end"
//
// <until loop> ::= "do"
// 						<block>
// 					"until" <expression>
//
// <for loop> ::= "for" <identifier> "in" <type> [ "do" ]
// 					  <block>
// 				  "end"
//
// <exception handler> ::= "catch" <exception list> "in"
// 								<block>
// 						 { "case" <exception list> ":"
// 								<block> }
// 						 [ "else"
// 								<block> ]
// 						   "end"
// <exception list> ::= <reference> { [ "," ] <reference> }
//
// <raise> ::= "raise" <reference>
//
// <procedure call> ::= <reference>
//
// <assignment> ::= <reference> "=" <expression>

#include "statement.h"
#include "expression.h"
#include "block.h"
#include "reference.h"
#include "type.h"
#include "CodeGen.h"

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
		   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
		   )
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
		    | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL ) \
		    )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )

class Case {
public:
	static void compile(Environment *e) {
		lex_advance(); // Move over "select"
		Expression::compile(e);

		if(lex_iskey(get_lex_this(), KEY_IN)) {
			lex_advance(); // Move over "in"
		}

		while(lex_iskey(get_lex_this(), KEY_CASE)) {
			lex_advance(); // Move over "case"

			do {
				if(lex_ispunc(get_lex_this(), PT_COMMA)) {
					lex_advance(); // Move over ","
				}

				Expression::compile(e);
				if(lex_iskey(get_lex_this(), KEY_IN)) {
					lex_advance(); // Move over ".."
					Expression::compile(e);
				}
			} while(!(lex_ispunc(get_lex_this(), PT_SEMI)));

			lex_advance(); // Move over ":"
			Block::compile(e);
		}

		if(lex_iskey(get_lex_this(), KEY_ELSE)) {
			lex_advance(); // Move over "else"
			Block::compile(e);
		}

		lex_advance(); // Move over "end"
	}
};

Statement *Statement::compile(Environment *e) {

	lex_wantinset(START_PUNCS, START_KEYS, START_LEXS, ER_WANT_STATE);
	Statement *newStatement = new Statement();
        Type * t;
	if (get_lex_this().type == KEYWORD) {
		switch (get_lex_this().value) {
			case KEY_DO:
				lex_advance(); // Move over "do"
				Block::compile(e);

				if(lex_iskey(get_lex_this(), KEY_UNTIL)) {
					lex_advance(); // skip over "until"
					// do while loop
					Expression::compile(e);
				} else {
					lex_forcekey(KEY_END); // Move over "end"
				}

				break;
			case KEY_IF:
				lex_advance(); // Move over "if"
				Expression::compile(e);

				if(lex_iskey(get_lex_this(), KEY_THEN)) {
					lex_advance(); // Move over "then"
				}

				Block::compile(e);

				if(lex_iskey(get_lex_this(), KEY_ELSE)) {
					lex_advance(); // Move over "else"
					Block::compile(e);
				}

				lex_forcekey(KEY_END); // Move over "end

				break;
			case KEY_SELECT:
				Case::compile(e);
				break;
			case KEY_WHILE:
				lex_advance(); // Move over "while"
				Expression::compile(e);

				if(lex_iskey(get_lex_this(), KEY_DO)) {
					lex_advance(); // Move over "do"
				}

				Block::compile(e);

				lex_forcekey(KEY_END); // Move over "end"
				break;
			case KEY_FOR:
				lex_advance(); // Move over "for"

				if(get_lex_this().type == IDENT) {
					lex_advance();
				}
				// =BUG= Force lexeme to be an identifier

				lex_forcekey(KEY_IN); // Move over "in

				t = Type::compile(e);

				if(lex_iskey(get_lex_this(), KEY_DO)) {
					lex_advance(); // Move over "do"
				}

				Block::compile(e);
				lex_forcekey(KEY_END); // Move over "end"
				break;
			case KEY_CATCH:
				// =BUG= Catching exceptions not implemented
				break;
			case KEY_RAISE:
				lex_advance(); // move over "raise"
				Reference::compile(e);
				// = BUG= Raising exceptions not implemented
				break;
			default:
				break;
		}
	} else if(get_lex_this().type == IDENT) {
		// =BUG= Temporary custom handling of putstring
		if(strcmp(lex_get(get_lex_this()), "putstring") == 0) {
			Log::Warn(ER_CUSTOM, get_lex_this().line, get_lex_this().char_index, "Temporary workaround for putstring");
			// Generate machine code
			lex_advance(); // Advance over putstring
			lex_advance(); // Advance over (

			// Generate machine code for putstring
			if(strcmp(lex_get(get_lex_next()), "LF") == 0) {
				CodeGen::PutString(get_lex_this().value, true);
				lex_advance(); // Extra advance to advance over LF
			} else {
				CodeGen::PutString(get_lex_this().value, false);
			}
			lex_advance(); // Advance over string

			lex_advance(); // Advance over ,
			lex_advance(); // Advance over output file
			lex_advance(); // Advance over )

			if(lex_ispunc(get_lex_this(), PT_SEMI)) {
				lex_advance(); // Move over ";"
			}

		} else {
			Log::Fatal(ER_CUSTOM, get_lex_this().line, get_lex_this().char_index, "Procedure calls not implemented");
			// =BUG= Procedure calls not implemented
			// =BUG= Assignment statements not implemented
		}
	}

	lex_wantinset(FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_BLOCK);

	return NULL;
}
