// declaration.cpp -- implementation of parser/compiler for declarations

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established

// BNF
// <declaration> ::= <identifier> : [ <private> | <restricted> ] <declarator>
// <declarator> ::= <constant declarator>
//               |  <type declarator>
//               |  <exception declarator>
//               |  <variable declarator>
//               |  <procedure declarator>
//               |  <function declarator>
// <constant declarator> ::= "const" <expression>
//                        |  "final" <expression>
// <type declarator> ::= "type" <type>
//                    |  "type" "-"
// <exception declarator> ::= "exception"
// <variable declarator> ::= "var" <type>
// <procedure declarator> ::= "procedure"
//                            [ <formal parameter list> ]
//                            <body>
// <function declarator> ::=  "function" <type>
//                            [ <formal parameter list> ]
//                            <body>
// <body> ::= <block> "end"
//         |  "-"
//         |  "external"
// <formal parameter list> ::= "(" <formal parameters> ")"
//                          |  "[" <formal parameters> "]"
//                          |  "{" <formal parameters> "}"
// <formal parameters> ::= <parameter> { [ "," ] <parameter> }
// <parameter> ::= <identifier> ":" <parameter declarer>
// <parameter declarer> ::= <type>
//                       |  "var" <type>
//                       |  "final" <type>


#include "declaration.h"
#include "block.h"
#include "expression.h"
#include "lexsupport.h"

// =BUG= code to compile various kinds of declarations might
// =   = go here as local classes, not in the header file
// =   = but if they start getting big and unwieldy, they can each
// =   = be put in ther own files

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS SET32_EMPTY
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
            | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL )         \
            | to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH )          \
            | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR)          		   \
            )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )

Environment *Declaration::compile(Environment *e) {
	// lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_??? );
	// the above is not needed because Block::compile() is the only caller
	// and it only calls this code when it sees <identifier>:

	uint32_t identifier = get_lex_this().value;
	Environment *newEnv;
	lex_advance(); // move over identifier

	lex_advance(); // skip colon

	access_level mType = ACCESS_PUBLIC;

	if(get_lex_this().type == KEYWORD) {
		if(get_lex_this().value == KEY_PRIVATE) {
			mType = ACCESS_PRIVATE;
			lex_advance(); // move over private
		} else if(get_lex_this().value == KEY_RESTRICTED) {
			mType = ACCESS_RESTRICTED;
			lex_advance(); // move over public
		} else if(get_lex_this().value == KEY_CONST) {
			// Constant declaration
			lex_advance(); // move over CONST
			newEnv = e->add(identifier, Expression::compile(e), ATTR_CONST, mType);
		} else if(get_lex_this().value == KEY_FINAL) {
			// Final declaration
			lex_advance(); // move over FINAL
			newEnv = e->add(identifier, Expression::compile(e), ATTR_FINAL, mType);
		} else if(get_lex_this().value == KEY_TYPE) {
			// Type declaration
			lex_advance(); // move over TYPE
			if(get_lex_this().type == PUNCT) {
				if(get_lex_this().value == PT_MINUS) {
					// Forward declaration
					lex_advance(); // move over the minus sign
					newEnv = e->add(identifier, NULL, ATTR_TYPE, mType);
				}
			} else {
				newEnv = e->add(identifier, Type::compile(e), ATTR_TYPE, mType);
			}
		} else if(get_lex_this().value == KEY_EXCEPTION) {
			// Exception declaration
			lex_advance(); // move over exception
			newEnv = e->add(identifier, NULL, ATTR_EXCEPT, mType);
		} else if(get_lex_this().value == KEY_VAR) {
			// Variable declaration
			lex_advance(); // move over var
			newEnv = e->add(identifier, Type::compile(e), ATTR_VAR, mType);
		} else if(get_lex_this().value == KEY_PROCEDURE) {
			// Procedure declaration
			lex_advance(); // move over proc
			newEnv = e->add(identifier, Procedure::compile(e), ATTR_PROC, mType);
		} else if(get_lex_this().value == KEY_FUNCTION) {
			// Function declaration
			lex_advance(); // move over func
			newEnv = e->add(identifier, Function::compile(e), ATTR_FUNC, mType);
		}
	}

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_BLOCK );
        if(newEnv == NULL) {
            Log::Error(ER_NO_TYPE, get_lex_this().line, get_lex_this().char_index);
            // no type found
        }
	return newEnv;
}

Procedure * Procedure::compile(Environment* e) {
    Procedure *newProc = new Procedure();
    newProc->parameters = FormalParameterList::compile(e);
    printf("Defining function with internal environment: ");
    newProc->parameters->internalEnv->print();
    printf("\n");
    newProc->attr = Body::compile(newProc->parameters->internalEnv);
    return newProc;
}

Function * Function::compile(Environment* e) {
    Function * newFunc = new Function();
    newFunc->returnType = Type::compile(e);
    newFunc->parameters = FormalParameterList::compile(e);
    newFunc->attr = Body::compile(newFunc->parameters->internalEnv);
    return newFunc;
}

FormalParameterList * FormalParameterList::compile(Environment* e) {
    FormalParameterList * firstParam = NULL;
    FormalParameterList * newParam = firstParam;
    FormalParameterList * prevParam = newParam;
    if(get_lex_this().type == PUNCT) {
        set32_t parens = to_set32_3(PT_LPAREN,PT_LBRAKT,PT_LBRACE);
        punct_type endParen;
        if(lex_ispuncset(get_lex_this(),parens)) {
            endParen = (punct_type)(get_lex_this().value + 3);
            lex_advance(); // advance over the begin paren
        }else{
            endParen = PT_RPAREN;
            Log::Error(ER_FOUND_BUT_WANT,get_lex_this().line, get_lex_this().char_index, lex_get(get_lex_this()), "(, {, or [");
        }

        while(!lex_ispunc(get_lex_this(), endParen)) {
            if(get_lex_this().type == ENDFILE){
                //prevents an infinite loop if the user does not have an end paren
                break;
            }
            // read in a parameter preceded by an optional comma (unless this is the first)
            if(firstParam != NULL && get_lex_this().type == PUNCT) {
                if(get_lex_this().value == PT_COMMA) {
                        lex_advance(); // move over the comma
                }
            }
            newParam = new FormalParameterList();
            if(firstParam == NULL)
                firstParam = newParam;
            else
                prevParam->nextParam = newParam;

            // Read in the parameter
            newParam->identifier = get_lex_this().value;
            lex_advance(); // move over the identifier
            lex_advance(); // move over the colon
            // Read in the parameter declarer
            if(get_lex_this().type == KEYWORD) {
                if(get_lex_this().value == KEY_VAR) {
                    lex_advance(); // move over "var"
                    newParam->paramType = FORM_VAR;
                    newParam->attr = Type::compile(e);
                    e = e->add(newParam->identifier, newParam->attr, ATTR_VAR, ACCESS_PRIVATE);
                } else if(get_lex_this().value == KEY_FINAL) {
                    lex_advance(); // move over "final"
                    newParam->paramType = FORM_FINAL;
                    newParam->attr = Type::compile(e);
                    e = e->add(newParam->identifier, newParam->attr, ATTR_FINAL, ACCESS_PRIVATE);
                }
            } else {
                // Handle the type
                newParam->paramType = FORM_REF;
                newParam->attr = Type::compile(e);
                e = e->add(newParam->identifier, newParam->attr, ATTR_REF, ACCESS_PRIVATE);
            }

            prevParam = newParam;
        }
        lex_forcepunc(endParen);// move over the end paren
    }

    firstParam->internalEnv = e;
    return firstParam;
}

Body * Body::compile(Environment* e) {
    Body * newBody = new Body();

    if(get_lex_this().type == PUNCT) {
            if(get_lex_this().value == PT_MINUS) {
                    // =BUG= Handle forward declaration
                    lex_advance(); // move over minus sign
            } else {
                Log::Error(ER_INV_TYPE_DEF, get_lex_this().line, get_lex_this().char_index);
            }
    } else if(get_lex_this().type == KEYWORD) {
            if(get_lex_this().value == KEY_EXTERNAL) {
                    // =BUG= Handle external function
                    lex_advance(); // move over "external"
            } else {
                Log::Error(ER_INV_TYPE_DEF, get_lex_this().line, get_lex_this().char_index);
            }
    } else {
            newBody->attr = Block::compile(e);
            // =BUG= make sure the block ends on "end"?
            lex_advance(); // advance over end
    }


    return newBody;
}